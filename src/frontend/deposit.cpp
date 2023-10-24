#include "deposit.h"

#include <QDate>
#include <QMessageBox>

#include "ui_deposit.h"

extern "C" {
#include "../backend/SmartCalc.h"
}

Deposit::Deposit(QWidget *parent) : QWidget(parent), ui(new Ui::Deposit) {
  ui->setupUi(this);

  ui->paym_freq->setCurrentIndex(ui->paym_freq->findText("At the end"));
  ui->month_year->setCurrentIndex(ui->month_year->findText("Months"));

  ui->acc_int->setReadOnly(true);
  ui->tax_amount->setReadOnly(true);
  ui->total->setReadOnly(true);
}

Deposit::~Deposit() { delete ui; }

void Deposit::on_clear_clicked() {
  ui->dep_amount->setText("");
  ui->place_term->setText("");
  ui->int_rate->setText("");
  ui->tax_rate->setText("");
  ui->rep_amo->setText("");
  ui->withd_amo->setText("");

  ui->acc_int->setText("");
  ui->tax_amount->setText("");
  ui->total->setText("");

  ui->month_year->setCurrentIndex(ui->month_year->findText("Months"));
  ui->paym_freq->setCurrentIndex(ui->paym_freq->findText("At the end"));
  ui->repl_freq->setCurrentIndex(ui->repl_freq->findText("None"));
  ui->withdr_freq->setCurrentIndex(ui->withdr_freq->findText("None"));

  ui->capitalisation->setChecked(false);
}

void Deposit::on_calculate_clicked() {
  bool flag1, flag2, flag3, flag4, flag5, flag6;

  double deposit_base = ui->dep_amount->text().toDouble(&flag1);
  int term = ui->place_term->text().toInt(&flag2);
  double int_rate = ui->int_rate->text().toDouble(&flag3);
  double tax_rate = ui->tax_rate->text().toDouble(&flag4);

  int month_year = ui->month_year->currentIndex();
  int paym_freq = ui->paym_freq->currentIndex();

  if (month_year == 1) term *= 12;

  // =================================================== //

  freq repl;
  repl.frq = ui->repl_freq->currentIndex();
  repl.sum = ui->rep_amo->text().toDouble(&flag5);

  freq withdr = {0, 0};
  withdr.frq = ui->withdr_freq->currentIndex();
  withdr.sum = ui->withd_amo->text().toDouble(&flag6);

  if (repl.frq == 0) flag5 = 1;
  if (withdr.frq == 0) flag6 = 1;

  bool flag = flag1 && flag2 && flag3 && flag4 && flag5 && flag6 &&
              deposit_base > 0 && term > 0 && term <= 600 && tax_rate >= 0 &&
              int_rate >= 0.001;

  // =================================================== //

  double acc_interest = 0;
  double tax = 0;
  double total = 0;
  double sum_amount = deposit_base;

  QDate dStart = (QDate::currentDate());
  QDate dEnd = dStart.addMonths(term);

  int during_d = (int)dStart.daysTo(dEnd);

  QDate RepDate = NextRepWithd(dStart, repl.frq);
  QDate WithdDate = NextRepWithd(dStart, withdr.frq);
  QDate PayDate = NextPayDate(dStart, paym_freq);

  if (flag) {
    if (ui->capitalisation->checkState() ==
        Qt::Unchecked) {  // Капитализация выключена
      for (QDate tmp = dStart; tmp <= dEnd; tmp = tmp.addDays(1)) {
        if (tmp == RepDate) {
          char input[500] = {0};
          sprintf(input, "%.8lf+%.8lf", sum_amount, repl.sum);
          smartcalc(input, &sum_amount);
          RepDate = NextRepWithd(RepDate, repl.frq);
        }
        if (tmp == WithdDate) {
          char input[500] = {0};
          sprintf(input, "%.8lf-%.8lf", sum_amount, withdr.sum);
          smartcalc(input, &sum_amount);
          WithdDate = NextRepWithd(WithdDate, withdr.frq);
        }
        if (tmp == PayDate && paym_freq < 6) {
          char input[500] = {0};
          if (paym_freq == 0) {  // Every day
            sprintf(input, "%.8lf+%.8lf*(%.8lf/(100*%d))", acc_interest,
                    sum_amount, int_rate, tmp.daysInYear());
          } else if (paym_freq == 1) {  // Every week
            sprintf(input, "%.8lf+%.8lf*(%.8lf/(100*52))", acc_interest,
                    sum_amount, int_rate);
          } else if (paym_freq == 2) {  // Once a month
            sprintf(input, "%.8lf+%.8lf*(%.8lf/(100*12))", acc_interest,
                    sum_amount, int_rate);
          } else if (paym_freq == 3) {  // Every quarter
            sprintf(input, "%.8lf+%.8lf*(%.8lf/(100*4))", acc_interest,
                    sum_amount, int_rate);
          } else if (paym_freq == 4) {  // Every 6 months
            sprintf(input, "%.8lf+%.8lf*(%.8lf/(100*2))", acc_interest,
                    sum_amount, int_rate);
          } else if (paym_freq == 5) {  // Every year
            sprintf(input, "%.8lf+%.8lf*(%.8lf/100)", acc_interest, sum_amount,
                    int_rate);
          }
          smartcalc(input, &acc_interest);
          PayDate = NextPayDate(PayDate, paym_freq);
        }
      }
      if (paym_freq == 6) {
        char input[500] = {0};
        sprintf(input, "(%.8lf*%.8lf*%d/%d)/100", sum_amount, int_rate,
                (int)during_d, dStart.daysInYear());
        smartcalc(input, &acc_interest);
      }

      char input_tax[250] = {0};
      sprintf(input_tax, "%.8lf*(%.8lf/100)", acc_interest, tax_rate);
      smartcalc(input_tax, &tax);

      char input_total[250] = {0};
      sprintf(input_total, "%.8lf+%.8lf", sum_amount, acc_interest);
      smartcalc(input_total, &total);

    } else {  // Капитализация включена
      double sum_repl = 0;
      double sum_withd = 0;
      for (QDate tmp = dStart; tmp <= dEnd; tmp = tmp.addDays(1)) {
        if (tmp == RepDate) {
          char input[500] = {0};
          sprintf(input, "%.8lf+%.8lf", sum_amount, repl.sum);
          smartcalc(input, &sum_amount);
          RepDate = NextRepWithd(RepDate, repl.frq);

          char rep[200] = {0};
          sprintf(rep, "%.8lf+%.8lf", sum_repl, repl.sum);
          smartcalc(rep, &sum_repl);
        }
        if (tmp == WithdDate) {
          char input[500] = {0};
          sprintf(input, "%.8lf-%.8lf", sum_amount, withdr.sum);
          smartcalc(input, &sum_amount);
          WithdDate = NextRepWithd(WithdDate, withdr.frq);

          char withd[200] = {0};
          sprintf(withd, "%.8lf+%.8lf", sum_withd, withdr.sum);
          smartcalc(withd, &sum_withd);
        }
        if (tmp == PayDate && paym_freq < 6) {
          char input[500] = {0};
          if (paym_freq == 0) {  // Every day
            sprintf(input, "%.8lf+%.8lf*(%.8lf/(100*%d))", sum_amount,
                    sum_amount, int_rate, tmp.daysInYear());
          } else if (paym_freq == 1) {  // Every week
            sprintf(input, "%.8lf+%.8lf*(%.8lf/(100*52))", sum_amount,
                    sum_amount, int_rate);
          } else if (paym_freq == 2) {  // Once a month
            sprintf(input, "%.8lf+%.8lf*(%.8lf/(100*12))", sum_amount,
                    sum_amount, int_rate);
          } else if (paym_freq == 3) {  // Every quarter
            sprintf(input, "%.8lf+%.8lf*(%.8lf/(100*4))", sum_amount,
                    sum_amount, int_rate);
          } else if (paym_freq == 4) {  // Every 6 months
            sprintf(input, "%.8lf+%.8lf*(%.8lf/(100*2))", sum_amount,
                    sum_amount, int_rate);
          } else if (paym_freq == 5) {  // Every year
            sprintf(input, "%.8lf+%.8lf*(%.8lf/100)", sum_amount, sum_amount,
                    int_rate);
          }
          smartcalc(input, &sum_amount);
          PayDate = NextPayDate(PayDate, paym_freq);
        }
      }

      char input[500] = {0};
      sprintf(input, "%.8lf-%.8lf-%.8lf+%.8lf", sum_amount, deposit_base,
              sum_repl, sum_withd);
      smartcalc(input, &acc_interest);

      char input_tax[250] = {0};
      sprintf(input_tax, "(%.8lf)*(%.8lf/100)", acc_interest, tax_rate);
      smartcalc(input_tax, &tax);

      total = sum_amount;
    }
    ui->acc_int->setText(QString::number(acc_interest, 'f', 2));
    ui->tax_amount->setText(QString::number(tax, 'f', 2));
    ui->total->setText(QString::number(total, 'f', 2));
  } else {
    QMessageBox::critical(this, "", "Input error");
  }
}

void Deposit::on_capitalisation_stateChanged(int arg1) {
  if (ui->capitalisation->checkState() == Qt::Unchecked) {
    ui->pay_freq_label->setText(" Payments freq");
    ui->paym_freq->addItem("At the end");
    ui->paym_freq->setCurrentIndex(ui->paym_freq->findText("At the end"));
  } else {
    ui->pay_freq_label->setText(" Capitalisation freq");
    ui->paym_freq->removeItem(ui->paym_freq->findText("At the end"));
    ui->paym_freq->setCurrentIndex(ui->paym_freq->findText("Once a month"));
  }
}

QDate NextRepWithd(QDate now, int period) {
  QDate tmp;
  switch (period) {
    case 1:
      tmp = now.addMonths(1);
      break;
    case 2:
      tmp = now.addMonths(3);
      break;
    case 3:
      tmp = now.addMonths(6);
      break;
    case 4:
      tmp = now.addYears(1);
      break;
    default:
      tmp = now.addYears(101);
      break;
  }
  return tmp;
}

QDate NextPayDate(QDate now, int period) {
  QDate tmp;
  switch (period) {
    case 0:
      tmp = now.addDays(1);
      break;
    case 1:
      tmp = now.addDays(7);
      break;
    case 2:
      tmp = now.addMonths(1);
      break;
    case 3:
      tmp = now.addMonths(3);
      break;
    case 4:
      tmp = now.addMonths(6);
      break;
    case 5:
      tmp = now.addYears(1);
      break;
    default:
      tmp = now.addYears(101);
      break;
  }
  return tmp;
}

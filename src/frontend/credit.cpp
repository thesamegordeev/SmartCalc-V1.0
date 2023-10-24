#include "credit.h"

#include "ui_credit.h"

extern "C" {
#include "../backend/SmartCalc.h"
}

Credit::Credit(QWidget *parent) : QWidget(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
  ui->month_payment->setReadOnly(true);
  ui->accured_inter->setReadOnly(true);
  ui->total_cost->setReadOnly(true);

}

Credit::~Credit() { delete ui; }

void Credit::on_calculate_clicked() {
  bool flag1, flag2, flag3, flag4;

  double loan_sum = ui->loan_amount->text().toDouble(&flag1);
  int loan_term = ui->loan_term->text().toInt(&flag2);
  double int_rate = ui->int_rate->text().toDouble(&flag3);
  int payment_type = ui->payment_type->currentIndex();
  int month_years = ui->month_year->currentIndex();

  if (!flag1 || !flag2 || !flag3 || loan_sum <= 0 || loan_term <= 0 || int_rate < 0.001) {
    QMessageBox::critical(this, "", "Input error");
  } else if (payment_type == 0) {  // Аннуитентный платеж
    if (month_years == 1) {
      loan_term *= 12;
    }

    ui->pay_sch->clear();
    ui->pay_sch->setRowCount(0);
    ui->pay_sch->setColumnCount(0);



    double monthly_payment = 0;
    double overpayment = 0;
    double total = 0;
    int error = 0;
    error += mon_payment_ann(loan_sum, int_rate, loan_term, &monthly_payment);
    error +=
        accured_interest_ann(monthly_payment, loan_sum, loan_term, &overpayment);
    error += total_payout(loan_sum, overpayment, &total);
    if (error == 0) {
      ui->month_payment->setText(QString::number(monthly_payment, 'f', 2));
      ui->accured_inter->setText(QString::number(overpayment, 'f', 2));
      ui->total_cost->setText(QString::number(total, 'f', 2));
    } else {
      QMessageBox::critical(this, "", "Input error");
    }

  } else if (payment_type == 1) {  // Дифф платеж

    if (month_years == 1) {
      loan_term *= 12;
    }

    ui->pay_sch->setRowCount(loan_term);
    ui->pay_sch->setColumnCount(1);  // Номер платежа | Сумма платежа

    double remaining = loan_sum;
    double overpayment = 0;
    double total = 0;
    int error = 0;

    for (int i = 1; i <= loan_term; i++) {
      double payment = 0;
      error += accured_interest_diff(remaining, int_rate, &overpayment);
      error += mon_payment_diff(loan_sum, loan_term, &remaining, int_rate, &payment);
      if (error == 0) {
          QTableWidgetItem *str_num = new QTableWidgetItem(QString::number(payment));
          ui->pay_sch->setItem(i - 1, 0, str_num);
      } else {
          QMessageBox::critical(this, "", "Input error");
      }

    }

    error += total_payout(loan_sum, overpayment, &total);

    if (error == 0) {
    ui->month_payment->setText("->");
    ui->accured_inter->setText(QString::number(overpayment, 'f', 2));
    ui->total_cost->setText(QString::number(total, 'f', 2));
    }
    ui->pay_sch->setHorizontalHeaderLabels(QStringList() << "Payment amount");
    ui->pay_sch->horizontalHeader()->setSectionResizeMode(0,
                                                          QHeaderView::Stretch);
    ui->pay_sch->setColumnWidth(1, 100);
  }
}

void Credit::on_clear_clicked()
{
  // Очистка таблицы
  ui->pay_sch->clear();
  ui->pay_sch->setRowCount(0);
  ui->pay_sch->setColumnCount(0);

  // Очистка полей
  ui->loan_amount->setText("");
  ui->loan_term->setText("");
  ui->int_rate->setText("");

  ui->month_payment->setText("");
  ui->accured_inter->setText("");
  ui->total_cost->setText("");

}


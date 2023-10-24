#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SmartCalc) {
  ui->setupUi(this);

  ui->show_line->setReadOnly(true);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(nums()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(nums()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(nums()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(nums()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(nums()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(nums()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(nums()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(nums()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(nums()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(nums()));

  connect(ui->pushButton_bracket_open, SIGNAL(clicked()), this,
          SLOT(chars_without_extra_brackets()));
  connect(ui->pushButton_bracket_close, SIGNAL(clicked()), this,
          SLOT(chars_without_extra_brackets()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(chars_without_extra_brackets()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this,
          SLOT(chars_without_extra_brackets()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(chars_without_extra_brackets()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(chars_without_extra_brackets()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this,
          SLOT(chars_without_extra_brackets()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(chars_without_extra_brackets()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(chars_without_extra_brackets()));

  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(chars_with_extra_brackets()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(chars_with_extra_brackets()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(chars_with_extra_brackets()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(chars_with_extra_brackets()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(chars_with_extra_brackets()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(chars_with_extra_brackets()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(chars_with_extra_brackets()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(chars_with_extra_brackets()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(chars_with_extra_brackets()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::nums() {
  QPushButton *button = static_cast<QPushButton *>(sender());

  QString input = (ui->show_line->text() + button->text());
  ui->show_line->setText(input);
}

void MainWindow::chars_without_extra_brackets() {
  QPushButton *button = static_cast<QPushButton *>(sender());

  QString input = (ui->show_line->text() + button->text());
  ui->show_line->setText(input);
  ui->pushButton_dot->setDisabled(false);
}

void MainWindow::chars_with_extra_brackets() {
  QPushButton *button = static_cast<QPushButton *>(sender());

  QString input = (ui->show_line->text() + button->text() + "(");
  ui->show_line->setText(input);
  ui->pushButton_dot->setDisabled(false);
}

void MainWindow::on_pushButton_dot_clicked() {
  QString input = (ui->show_line->text() + ".");
  ui->show_line->setText(input);
  ui->pushButton_dot->setDisabled(true);
}

void MainWindow::on_pushButton_clear_clicked() {
  ui->show_line->setText("");
  ui->pushButton_dot->setDisabled(false);
}

void MainWindow::on_pushButton_eq_clicked() {
  QString qstring_input = (ui->show_line->text());
  QByteArray array = qstring_input.toLocal8Bit();
  char *str_input = array.data();

  double num = 0;
  int error_flag = 0;
  if (is_x_in_input(str_input) == 0) {
    error_flag = smartcalc(str_input, &num);
    if (error_flag == 0) {
      qstring_input = QString::number(num);
    } else if (error_flag == 1) {
      QMessageBox::critical(this, "", "Input error.");
      qstring_input = "";
    } else if (error_flag == 2) {
      QMessageBox::critical(this, "", "Division by zero.");
      qstring_input = "";
    } else if (error_flag == 3) {
      QMessageBox::critical(this, "",
                            "The log argument is less than or equal to zero.");
      qstring_input = "";
    } else if (error_flag == 4) {
      QMessageBox::critical(this, "", "The a(func) argument is out of range.");
      qstring_input = "";
    } else if (error_flag == 5) {
      QMessageBox::critical(this, "", "The sqrt argument is less than zero.");
      qstring_input = "";
    } else if (error_flag == 6) {
      QMessageBox::critical(this, "", "The tan argument is out of range.");
      qstring_input = "";
    }
    ui->show_line->setText(qstring_input);
  } else if (validator(str_input, &error_flag) == 0) {
    graph = new Graph;
    graph->setInput(qstring_input);
    graph->setAttribute(Qt::WA_ShowModal, true);
    graph->show();
    graph->setWindowTitle("Graph");
    graph->plotting(-20, 20);
  } else {
    QMessageBox::critical(this, "", "Input error.");
    qstring_input = "";
  }
}

void MainWindow::on_pushButton_Credit_clicked() {
  credit = new Credit;
  credit->setAttribute(Qt::WA_ShowModal, true);
  credit->show();
  credit->setWindowTitle("Credit Calculator");
}

void MainWindow::on_pushButton_Deposit_clicked() {
  deposit = new Deposit;
  deposit->setAttribute(Qt::WA_ShowModal, true);
  deposit->show();
  deposit->setWindowTitle("Deposit Calculator");
}

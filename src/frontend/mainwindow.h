#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// #include <QMessageBox>
// #include <QRect>
#include <QPoint>
#include <QString>

#include "credit.h"
#include "deposit.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class SmartCalc;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::SmartCalc *ui;
  Graph *graph;
  Credit *credit;
  Deposit *deposit;

 private slots:
  void chars_without_extra_brackets();
  void chars_with_extra_brackets();
  void on_pushButton_dot_clicked();
  void nums();
  void on_pushButton_clear_clicked();
  void on_pushButton_eq_clicked();
  void on_pushButton_Credit_clicked();
  void on_pushButton_Deposit_clicked();
};
#endif  // MAINWINDOW_H

#ifndef GRAPH_H
#define GRAPH_H

#include <unistd.h>

#include <QWidget>

#include "qcustomplot.h"

extern "C" {
#include "../backend/SmartCalc.h"
}

namespace Ui {
class Graph;
}

class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

  void setInput(const QString &input);
  void plotting(double x_min, double x_max);

  QString input_from_mw;

 private slots:
  void on_pushButton_change_scale_clicked();
  void default_range();

 private:
  Ui::Graph *ui;
  // QCustomPlot *customPlot;  // Объявляем графическое полотно
  // QCPGraph *graphic;  // Объявляем график
};

#endif  // GRAPH_H

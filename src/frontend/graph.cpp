#include "graph.h"

#include "ui_graph.h"

void Graph::setInput(const QString &input) { ui->Input_line->setText(input); }

Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
  ui->Input_line->setReadOnly(true);
  default_range();
}

Graph::~Graph() { delete ui; }

void Graph::on_pushButton_change_scale_clicked() {
  bool flag1, flag2, flag3, flag4;

  double x_min = ui->lineEdit_xmin->text().toDouble(&flag1);
  double x_max = ui->lineEdit_xmax->text().toDouble(&flag2);
  double y_min = ui->lineEdit_ymin->text().toDouble(&flag3);
  double y_max = ui->lineEdit_ymax->text().toDouble(&flag4);

  if (!flag1 || !flag2 || !flag3 || !flag4) {
    QMessageBox::critical(this, "Input error", "The scale must be an integer.");
    default_range();
  } else if (x_min < x_max && x_min > -2e6 && x_max < 2e6 && y_min < y_max &&
             y_min > -2e6 && y_max < 2e6) {
    ui->widget->xAxis->setRange(x_min, x_max);
    ui->widget->yAxis->setRange(y_min, y_max);
    plotting(x_min, x_max);
  } else {
    QMessageBox::critical(this, "Input error", "Incorrect range.");
    default_range();
  }
}

/**
 * @brief Отрисовывает график функции на области определения или
 * пользовательском промежутке
 * @param x_min Левая граница отрисовки графика
 * @param x_max Правая граница отрисовки графика
 */
void Graph::plotting(double x_min, double x_max) {
  QString qstr_input = (ui->Input_line->text());
  QByteArray array = qstr_input.toLocal8Bit();
  char *input = array.data();

  ui->widget->xAxis->setLabel("X");
  ui->widget->yAxis->setLabel("Y");

  is_x_in_input(input);
  stack_sc *lexemes = input_parser(input);
  stack_sc *polish_notation = dijkstra(lexemes);

  int j = 0;
  double h = 0.01;

  int N = (x_max - x_min) / h;
  QVector<double> x(N), y(N);

  for (int i = 0; i < N; i++) {
    stack_sc *copy_rpn = copy_stack(polish_notation);
    int error_flag = 0;
    double operation_x = x_min + i * h;
    stack_sc *result = calculator(copy_rpn, &error_flag, operation_x);

    if (error_flag == 0 && result) {
      x[j] = operation_x;
      y[j] = pop(&result);
      j++;
    }
  }
  if (j == 0) {
    x.clear();
    y.clear();
  }

  QPen pen;
  pen.setWidth(3);
  pen.setColor(QColor(8, 166, 82, 255));

  ui->widget->addGraph();
  ui->widget->graph(0)->setPen(pen);
  ui->widget->graph(0)->setData(x, y);
  //    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssDisc,2));
  //    ui->widget->graph(0)->setLineStyle(QCPGraph::LineStyle::lsNone);
  ui->widget->replot();
}

/**
 * @brief Устанавливает дефолтные границы отрисовки
 */
void Graph::default_range() {
  ui->lineEdit_xmin->setText("-20");
  ui->lineEdit_xmax->setText("20");
  ui->lineEdit_ymin->setText("-10");
  ui->lineEdit_ymax->setText("10");

  double x_min = ui->lineEdit_xmin->text().toDouble();
  double x_max = ui->lineEdit_xmax->text().toDouble();
  double y_min = ui->lineEdit_ymin->text().toDouble();
  double y_max = ui->lineEdit_ymax->text().toDouble();

  ui->widget->xAxis->setRange(x_min, x_max);
  ui->widget->yAxis->setRange(y_min, y_max);
  ui->widget->replot();
}

#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QLocale::setDefault(QLocale::C);
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowTitle("SmartCalc");
  w.show();
  return a.exec();
}

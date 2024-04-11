#include <QApplication>

#include "contoller.h"
#include "mainwindow.h"
#include "models.h"

int main(int argc, char *argv[]) {
  s21::ModelCalc calc_model;
  s21::Contoller contoller(&calc_model);
  QApplication a(argc, argv);
  MainWindow w(nullptr, &contoller, calc_model.getData());
  w.show();
  return a.exec();
}

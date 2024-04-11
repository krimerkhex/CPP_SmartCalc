#ifndef CREDIT_H
#define CREDIT_H

#include <stdlib.h>

#include <QMessageBox>
#include <QValidator>
#include <QWidget>
#include <iostream>

#include "contoller.h"

namespace Ui {
class credit;
}

class credit : public QWidget {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr,
                  s21::Contoller *in_control = nullptr,
                  QRegularExpressionValidator *val_double_more = nullptr,
                  QRegularExpressionValidator *val_int = nullptr,
                  s21::crdt_data *in_data = nullptr);
  credit(const credit &other) = delete;
  credit(credit &&other) = delete;
  credit &operator=(const credit &other) = delete;
  credit &operator=(credit &&other) = delete;
  ~credit();

 signals:
  void showWindow();  // Сигнал на открытие данного окна
  void deletevald();  // Сигнал на закрытия данного окна

 private slots:

  void inicilization();
  void on_pushButton_clicked();

 private:
  s21::Contoller *control_;
  s21::crdt_data *data_;
  Ui::credit *ui;
};

#endif  // CREDIT_H

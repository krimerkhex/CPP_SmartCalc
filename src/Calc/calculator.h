#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <math.h>

#include <QListWidget>
#include <QMessageBox>
#include <QValidator>
#include <QWidget>
#include <algorithm>
#include <iostream>
#include <typeinfo>

#include "contoller.h"
#include "qcustomplot.h"

namespace Ui {
class calculator;
}

class calculator : public QWidget {
  Q_OBJECT

 public:
  explicit calculator(QWidget *parent = nullptr,
                      s21::Contoller *in_control = nullptr,
                      QRegularExpressionValidator *val_calc = nullptr,
                      QRegularExpressionValidator *val_double = nullptr,
                      s21::clcltr_data *in_data = nullptr);
  calculator(const calculator &other) = delete;
  calculator(calculator &&other) = delete;
  calculator &operator=(const calculator &other) = delete;
  calculator &operator=(calculator &&other) = delete;
  ~calculator();

 signals:
  void showWindow();  // Сигнал на открытие данного окна
  void deletevald();  // Сигнал на закрытия данного окна

 private slots:
  void on_log_but_clicked();
  void on_X_but_clicked();
  void on_alldel_but_clicked();
  void on_ln_but_clicked();
  void on_pow_but_clicked();
  void on_opbrack_but_clicked();
  void on_clbrack_but_clicked();
  void on_sin_but_clicked();
  void on_cos_but_clicked();
  void on_tan_but_clicked();
  void on_sqrt_but_clicked();
  void on_asin_but_clicked();
  void on_acos_but_clicked();
  void on_atan_but_clicked();
  void on_mod_but_clicked();
  void on_dev_but_clicked();
  void on_num7_but_clicked();
  void on_num8_but_clicked();
  void on_num9_but_clicked();
  void on_mult_but_clicked();
  void on_num4_but_clicked();
  void on_num5_but_clicked();
  void on_num6_but_clicked();
  void on_sub_but_clicked();
  void on_num1_but_clicked();
  void on_num2_but_clicked();
  void on_num3_but_clicked();
  void on_add_but_clicked();
  void on_num0_but_clicked();
  void on_dot_but_clicked();
  void on_equally_but_clicked();
  void on_m_ex_but_clicked();
  void on_p_ex_but_clicked();

 private:
  void inicilization();
  void graf();
  void grafSettings(QVector<double> x, QVector<double> y);
  s21::clcltr_data *data_;
  s21::Contoller *control_;
  Ui::calculator *ui;
};

#endif  // CALCULATOR_H

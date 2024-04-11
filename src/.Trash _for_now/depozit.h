#ifndef DEPOZIT_H
#define DEPOZIT_H

#include <QListWidget>
#include <QMessageBox>
#include <QValidator>
#include <QWidget>
#include <iostream>
#include <string>

#include "contoller.h"

namespace Ui {
class depozit;
}

class depozit : public QWidget {
  Q_OBJECT

 public:
  explicit depozit(QWidget *parent = nullptr,
                   s21::Contoller *in_control = nullptr,
                   QRegularExpressionValidator *val_double_more = nullptr,
                   QRegularExpressionValidator *val_int = nullptr,
                   s21::dpzt_data *in_data = nullptr);
  depozit(const depozit &other) = delete;
  depozit(depozit &&other) = delete;
  depozit &operator=(const depozit &other) = delete;
  depozit &operator=(depozit &&other) = delete;
  ~depozit();

 signals:
  void showWindow();  // Сигнал на открытие данного окна
  void deletevald();  // Сигнал на закрытия данного окна

 private slots:
  void inicilization();
  void on_run_clicked();
  void on_add_add_clicked();
  void on_add_sub_clicked();
  void on_add_clear_clicked();
  void on_sub_clear_clicked();

 private:
  s21::list_node &InitNode(int in_add, double in_sum, unsigned in_day,
                           unsigned in_month, unsigned in_year);
  s21::dpzt_data *data_;
  s21::Contoller *control_;
  Ui::depozit *ui;
};

#endif  // DEPOZIT_H

#include "depozit.h"

#include <iostream>

#include "ui_depozit.h"

depozit::depozit(QWidget *parent, s21::Contoller *in_control,
                 QRegularExpressionValidator *val_double_more,
                 QRegularExpressionValidator *val_int, s21::dpzt_data *in_data)
    : QWidget(parent), ui(new Ui::depozit) {
  ui->setupUi(this);
  this->control_ = in_control;
  this->data_ = in_data;
  ui->contribution->setValidator(val_double_more);
  ui->add->setValidator(val_double_more);
  ui->sub->setValidator(val_double_more);
  ui->tax->setValidator(val_int);
  ui->procent->setValidator(val_int);
  ui->time->setValidator(val_int);
}

depozit::~depozit() { delete ui; }

s21::list_node &depozit::InitNode(int in_add, double in_sum, unsigned in_day,
                                  unsigned in_month, unsigned in_year) {
  s21::list_node node;
  node.add = in_add;
  node.sum = in_sum;
  node.time.day = in_day;
  node.time.month = in_month;
  node.time.year = in_year;
  return &node;
}

void depozit::on_add_add_clicked() {
  data_->add_sub_list.push_front(
      InitNode(1, ui->add->text().toDouble(), ui->add_time->date().day(),
               ui->add_time->date().month(), ui->add_time->date().year()));
  ui->add_list->setText(ui->add_list->text() + ui->add->text() + " " +
                        ui->add_time->date().toString() + "\n");
}

void depozit::on_add_sub_clicked() {
  data_->add_sub_list.push_back(
      InitNode(-1, ui->sub->text().toDouble(), ui->sub_time->date().day(),
               ui->sub_time->date().month(), ui->sub_time->date().year()));
  ui->sub_list->setText(ui->sub_list->text() + ui->sub->text() + " " +
                        ui->sub_time->date().toString() + "\n");
}

void depozit::on_add_clear_clicked() {
  ui->add_list->setText("");
  while (data_->add_sub_list.front().add == 1) data_->add_sub_list.pop_front();
}

void depozit::on_sub_clear_clicked() {
  ui->sub_list->setText("");
  while (data_->add_sub_list.back().add == -1) data_->add_sub_list.pop_back();
}

void depozit::inicilization() {
  data->error = 0;
  data->sum = ui->contribution->text().toDouble();
  data->time = ui->time->text().toInt();
  data->procent = ui->procent->text().toDouble();
  data->tax = ui->tax->text().toDouble();
  data->payment_flag = ui->payment_per->currentIndex();
  data->payment_per = ui->payment_flag->currentIndex();
  data->start_time.year = ui->date_open->date().year();
  data->start_time.month = ui->date_open->date().month();
  data->start_time.day = ui->date_open->date().day();
}

void depozit::on_run_clicked() {
  this->inicilization();
  if (!this->control_->start_depz(&data)) {
    ui->sum_end->setText(QString::number(data->sum_end, 'f', 2));
    ui->sum_tax->setText(QString::number(data->sum_tax, 'f', 2));
    ui->sum_procent->setText(QString::number(data->sum_procent, 'f', 2));
  } else {
    QMessageBox::critical(this, "ERROR", "Data valid error");
    ui->contribution->setText("0.0");
    ui->procent->setText("0.0");
    ui->tax->setText("0.0");
    this->on_add_clear_clicked();
    this->on_sub_clear_clicked();
  }
}

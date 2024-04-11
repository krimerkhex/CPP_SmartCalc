#include "credit.h"

#include "ui_credit.h"

credit::credit(QWidget *parent, s21::Contoller *in_control,
               QRegularExpressionValidator *val_double_more,
               QRegularExpressionValidator *val_int, s21::crdt_data *in_data)
    : QWidget(parent), ui(new Ui::credit) {
  ui->setupUi(this);
  this->control_ = in_control;
  this->data_ = in_data;
  ui->sum_credit->setValidator(val_double_more);
  ui->procent->setValidator(val_double_more);
  ui->time->setValidator(val_int);
}

credit::~credit() { delete ui; }

void credit::inicilization() {
  data_->error = 0;
  data_->month = ui->open_date->date().month();
  data_->sum_credit = ui->sum_credit->text().toDouble();
  data_->procent = ui->procent->text().toDouble();
  data_->time = !ui->comboBox_2->currentIndex()
                    ? (int)ui->time->text().toDouble() * 12
                    : (int)ui->time->text().toDouble();
  data_->type = ui->comboBox_3->currentIndex();
}

void credit::on_pushButton_clicked() {
  this->inicilization();
  if (this->control_->start_cred(data_)) {
    ui->all_gived->setText(QString::number(data_->all_gived, 'f', 2));
    ui->gived_more->setText(QString::number(data_->gived_more, 'f', 2));
    ui->sum_per_mouth->clear();
    if (!data_->type)
      ui->sum_per_mouth->setText(
          QString::number(data_->sum_per_month[0], 'f', 2) + "\n");
    else
      for (auto it : data_->sum_per_month)
        ui->sum_per_mouth->setText(ui->sum_per_mouth->toPlainText() +
                                   QString::number(it, 'f', 2) + "\n");
  } else {
    QMessageBox::critical(this, "ERROR", "Data valid error");
    ui->sum_credit->setText("0.0");
    ui->procent->setText("0.0");
    ui->time->setText("0.0");
  }
}

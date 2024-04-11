#include "calculator.h"

#include "ui_calculator.h"

calculator::calculator(QWidget *parent, s21::Contoller *in_control,
                       QRegularExpressionValidator *val_calc,
                       QRegularExpressionValidator *val_double,
                       s21::clcltr_data *in_data)
    : QWidget(parent), ui(new Ui::calculator) {
  ui->setupUi(this);
  this->control_ = in_control;
  this->data_ = in_data;
  ui->formul_field->setValidator(val_calc);
  ui->x_value->setValidator(val_double);
  ui->x_graf_1->setValidator(val_double);
  ui->x_graf_2->setValidator(val_double);
}

calculator::~calculator() { delete ui; }

void calculator::on_log_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "log(");
}

void calculator::on_X_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "x");
}

void calculator::on_alldel_but_clicked() { ui->formul_field->setText(""); }

void calculator::on_ln_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "ln(");
}

void calculator::on_pow_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "^");
}

void calculator::on_opbrack_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "(");
}

void calculator::on_clbrack_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + ")");
}

void calculator::on_sin_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "sin(");
}

void calculator::on_cos_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "cos(");
}

void calculator::on_tan_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "tan(");
}

void calculator::on_sqrt_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "sqrt(");
}

void calculator::on_asin_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "asin(");
}

void calculator::on_acos_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "acos(");
}

void calculator::on_atan_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "atan(");
}

void calculator::on_mod_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "mod");
}

void calculator::on_dev_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "/");
}

void calculator::on_num7_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "7");
}

void calculator::on_num8_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "8");
}

void calculator::on_num9_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "9");
}

void calculator::on_mult_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "*");
}

void calculator::on_num4_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "4");
}

void calculator::on_num5_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "5");
}

void calculator::on_num6_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "6");
}

void calculator::on_sub_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "-");
}

void calculator::on_num1_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "1");
}

void calculator::on_num2_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "2");
}

void calculator::on_num3_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "3");
}

void calculator::on_add_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "+");
}

void calculator::on_num0_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "0");
}

void calculator::on_m_ex_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "e-");
}

void calculator::on_p_ex_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + "e");
}

void calculator::on_dot_but_clicked() {
  ui->formul_field->setText(ui->formul_field->text() + ".");
}

void calculator::inicilization() {
  this->data_->formul = ui->formul_field->text().toStdString();
  this->data_->x_value = ui->x_value->text().toDouble();
  this->data_->error = false;
  this->data_->result = 0.;
}

void calculator::grafSettings(QVector<double> x, QVector<double> y) {
  ui->widget->clearGraphs();
  ui->widget->addGraph();
  ui->widget->yAxis->setRange(*std::min_element(y.begin(), y.end()),
                              *std::max_element(y.begin(), y.end()));
  ui->widget->xAxis->setRange(*std::min_element(x.begin(), x.end()),
                              *std::max_element(x.begin(), x.end()));
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
}

void calculator::graf() {
  if (ui->x_graf_1->text().toDouble() != ui->x_graf_2->text().toDouble()) {
    double x_end =
        (ui->x_graf_1->text().toDouble() < ui->x_graf_2->text().toDouble())
            ? ui->x_graf_2->text().toDouble()
            : ui->x_graf_1->text().toDouble();
    double x_start =
        (ui->x_graf_1->text().toDouble() < ui->x_graf_2->text().toDouble())
            ? ui->x_graf_1->text().toDouble()
            : ui->x_graf_2->text().toDouble();
    QVector<double> x, y;
    for (double i = x_start; i <= x_end && !data_->error; i += 0.1) {
      inicilization();
      data_->x_value = i;
      this->data_ = this->control_->start_calc(this->data_);
      x.push_back(i);
      y.push_back(this->data_->result);
    }
    grafSettings(x, y);
    x.clear();
    y.clear();
  } else {
    QMessageBox::critical(this, "ERROR", "Range value  error!");
  }
}

void calculator::on_equally_but_clicked() {
  this->inicilization();
  this->data_ = this->control_->start_calc(this->data_);
  if (!this->data_->error) {
    QMessageBox::information(this, "Answer",
                             QString::number(this->data_->result, 'g', 7));
    if ((int)ui->formul_field->text().toStdString().find('x') != -1)
      this->graf();
  } else {
    QMessageBox::critical(this, "Error", "Validation error!");
    ui->formul_field->setText("");
    if (ui->x_value->text() != "0.0") ui->x_value->setText("0.0");
  }
}

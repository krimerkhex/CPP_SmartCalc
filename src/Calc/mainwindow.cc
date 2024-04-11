#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, s21::Contoller *in_contoller,
                       s21::clcltr_data *in_clcltr)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  val_double_ = new QRegularExpressionValidator(
      QRegularExpression("[-]?\\d*[.]?\\d*"), 0);
  val_calc_ = new QRegularExpressionValidator(
      QRegularExpression("^([-]?\\d*[.]?\\d*|[+-/"
                         "*^]|mod|[(]|[)]|sin[(]|cos[(]|tan[(]|sqrt[(]|asin[(]|"
                         "acos[(]|atan[(]|log[(]|ln[(]|[x]){0,}$"),
      0);
  calc_window_ = new calculator(this, in_contoller, this->val_calc_,
                                this->val_double_, in_clcltr);
}

MainWindow::~MainWindow() {
  delete calc_window_;
  delete val_double_;
  delete val_calc_;
  delete ui;
}

void MainWindow::on_actionCalculator_triggered() {
  connect(calc_window_, &calculator::showWindow, this, &MainWindow::show);
  ui->statusbar->showMessage("Обычный калькулятор\n");
  setCentralWidget(calc_window_);
}

void MainWindow::on_actionExit_triggered() { QApplication::quit(); }

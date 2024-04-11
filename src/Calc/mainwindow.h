#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "calculator.h"
#include "contoller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr, s21::Contoller *in_contoller = nullptr,
             s21::clcltr_data *in_clcltr = nullptr);
  MainWindow(const MainWindow &other) = delete;
  MainWindow(MainWindow &&other) = delete;
  MainWindow &operator=(const MainWindow &other) = delete;
  MainWindow &operator=(MainWindow &&other) = delete;
  ~MainWindow();

 private slots:
  void on_actionCalculator_triggered();
  void on_actionExit_triggered();

 private:
  Ui::MainWindow *ui;
  QRegularExpressionValidator *val_double_;
  QRegularExpressionValidator *val_calc_;

  // Functional
  calculator *calc_window_;
};

#endif  // MAINWINDOW_H

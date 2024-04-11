#include "contoller.h"

s21::Contoller::Contoller(ModelCalc *in_calc_model)
    : calc_model_(in_calc_model) {}

s21::Contoller::~Contoller() { this->calc_model_ = nullptr; }

s21::clcltr_data *s21::Contoller::start_calc(s21::clcltr_data *temp) const {
  return this->calc_model_->Calculation(temp);
}

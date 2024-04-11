#include "models.h"

s21::ModelCalc::ModelCalc() { this->data_ = new s21::clcltr_data; }

s21::ModelCalc::~ModelCalc() { delete this->data_; }

s21::clcltr_data *s21::ModelCalc::Calculation(s21::clcltr_data *temp) {
  if (!(temp->error = data_->formul.size() >= 255)) {
    this->data_ = std::move(temp);
    queue_.clear();
    stack_.clear();
    this->Parse();
    while (!stack_.empty()) FromStackToQueue();
    Compute();
  }
  return this->data_;
}

bool s21::ModelCalc::NotScob(std::string oper) {
  bool flag = false;
  for (long unsigned i = 0; i < operations_.size() - 2 && !flag; ++i) {
    if (oper == operations_.at(i)) {
      flag = true;
    }
  }
  return flag;
}

void s21::ModelCalc::Parse() {
  int unar = 1;
  std::string oper;
  size_t len = 0;
  std::string formul = std::move(this->data_->formul);
  while (!formul.empty() && !this->data_->error) {
    if (!formul.find_first_of(".0123456789")) {
      tok_.value_ = std::stod(formul, &len);
      this->PushToStrucructs(true, tok_.value_, &formul, len, "num");
      unar = 0;
    } else if (!formul.find('x')) {
      this->PushToStrucructs(true, this->data_->x_value, &formul, 1, "num");
      unar = 0;
    } else if (unar && !formul.find('-')) {
      this->PushToStrucructs(false, 0, &formul, 1, "--");
    } else if (formul[0] == ')') {
      formul.erase(0, 1);
      BracketClosed();
      unar = 0;
    } else if (CheckOperation(&formul, &oper)) {
      if (oper == "^") {
        if (!stack_.empty())
          if (stack_.front().operation_ != "^") Redistribution(oper);
      } else if (NotScob(oper))
        Redistribution(oper);
      PushToStrucructs(false, 0, &formul, oper.size(), oper);
      unar = 1;
    } else if (CheckFunction(&formul, &oper)) {
      Redistribution(oper);
      PushToStrucructs(false, 0, &formul, oper.size(), oper);
      unar = 1;
    } else
      this->data_->error = true;
  }
}

void s21::ModelCalc::PushToStrucructs(bool flag, double value,
                                      std::string *formul, size_t len,
                                      std::string oper) {
  this->tok_.operation_ = std::move(oper);
  this->tok_.value_ = value;
  if (formul != nullptr) formul->erase(0, len);
  flag ? queue_.push_back(tok_) : stack_.push_front(tok_);
}

bool s21::ModelCalc::CheckOperation(std::string *formul, std::string *oper) {
  return Check(formul, oper, operations_);
}

bool s21::ModelCalc::CheckFunction(std::string *formul, std::string *oper) {
  return Check(formul, oper, functions_);
}

bool s21::ModelCalc::Check(std::string *formul, std::string *oper,
                           std::vector<std::string> regular) {
  bool flag = true;
  for (size_t i = 0; i < regular.size() && flag; ++i) {
    if (!formul->find(regular[i])) {
      *oper = regular[i];
      flag = false;
    }
  }
  return !flag;
}

void s21::ModelCalc::Redistribution(std::string oper) {
  if (!stack_.empty()) {
    while (!stack_.empty() &&
           Preority(stack_.front().operation_) >= Preority(oper))
      FromStackToQueue();
  }
}

void s21::ModelCalc::BracketClosed() {
  if (!stack_.empty()) {
    std::string op{};
    double va = 0;
    while (op != "(") {
      op = stack_.front().operation_;
      va = stack_.front().value_;
      stack_.pop_front();
      if (op != "(") PushToStrucructs(true, va, nullptr, 0, op);
    }
    if (op != "(") {
      this->data_->error = true;
    }
  }
}

int s21::ModelCalc::Preority(std::string oper) {
  int preo = -1;
  preo = (oper == "+" || oper == "-" || oper == "--") ? 1 : preo;
  preo = (oper == "*" || oper == "/" || oper == "mod") ? 2 : preo;
  preo = (oper == "^") ? 3 : preo;
  preo = (oper == "sin" || oper == "cos" || oper == "tan" || oper == "asin" ||
          oper == "acos" || oper == "atan" || oper == "sqrt" || oper == "log" ||
          oper == "ln")
             ? 4
             : preo;
  return preo;
}

void s21::ModelCalc::FromStackToQueue() {
  this->tok_.operation_ = stack_.front().operation_;
  this->tok_.value_ = stack_.front().value_;
  queue_.push_back(tok_);
  stack_.pop_front();
}

void s21::ModelCalc::Compute() {
  double (*fun_operators_[6])(double, double) = {
      [](double a, double b) { return a + b; },
      [](double a, double b) { return a - b; },
      [](double a, double b) { return a * b; },
      [](double a, double b) { return a / b; },
      pow,
      fmod};
  double (*fun_functions_[9])(double) = {cos,  sin,  tan,   acos, asin,
                                         atan, sqrt, log10, log};
  double temp = 0.0;
  while (!queue_.empty() && !this->data_->error) {
    if (queue_.front().operation_ == "num") {
      this->PushToStrucructs(false, queue_.front().value_, nullptr, 0,
                             queue_.front().operation_);
    } else if (queue_.front().operation_ == "--") {
      temp = stack_.front().value_;
      stack_.pop_front();
      this->PushToStrucructs(false, 0 - temp, nullptr, 0, "num");
    } else {
      bool flag = true;
      for (int i = 0; i < 6 && stack_.size() >= 2 && flag; ++i) {
        if (queue_.front().operation_ == operations_[i]) {
          flag = false;
          double kostil = stack_.front().value_;
          stack_.pop_front();
          temp = fun_operators_[i](stack_.front().value_, kostil);
          stack_.pop_front();
          this->PushToStrucructs(false, temp, nullptr, 0, "num");
        }
      }
      for (int i = 0; i < 9 && !stack_.empty() && flag; ++i) {
        if (queue_.front().operation_ == functions_[i]) {
          flag = false;
          if (queue_.front().operation_ == "sqrt" && stack_.front().value_ < 0)
            data_->error = true;
          temp = fun_functions_[i](stack_.front().value_);
          stack_.pop_front();
          this->PushToStrucructs(false, temp, nullptr, 0, "num");
        }
      }
    }
    queue_.pop_front();
  }
  data_->result = std::round(stack_.front().value_ * 10000000) / 10000000;
}

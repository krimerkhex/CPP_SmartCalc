#ifndef MODELS_H
#define MODELS_H

#include <cmath>
#include <list>
#include <string>
#include <vector>

namespace s21 {

typedef struct calculator_data {
  std::string formul;
  double x_value;
  double result;
  bool error;
} clcltr_data;

class ModelCalc;
class token {
  friend ModelCalc;

 private:
  std::string operation_;
  double value_ = 0;
};

class ModelCalc {
 public:
  ModelCalc();
  ModelCalc(const ModelCalc &other) = delete;
  ModelCalc(ModelCalc &&other) = delete;
  ModelCalc &operator=(const ModelCalc &other) = delete;
  ModelCalc &operator=(ModelCalc &&other) = delete;
  ~ModelCalc();
  s21::clcltr_data *Calculation(s21::clcltr_data *temp);
  clcltr_data *getData() { return data_; }

 private:
  s21::clcltr_data *data_;
  std::list<token> queue_;
  std::list<token> stack_;
  token tok_;
  std::vector<std::string> functions_ = {"cos",  "sin",  "tan", "acos", "asin",
                                         "atan", "sqrt", "log", "ln"};
  std::vector<std::string> operations_ = {"+", "-",   "*", "/",
                                          "^", "mod", "(", ")"};

  void Parse();
  void PushToStrucructs(bool flag, double value, std::string *formul,
                        size_t len, std::string oper);
  bool CheckOperation(std::string *formul, std::string *oper);
  bool CheckFunction(std::string *formul, std::string *oper);
  bool Check(std::string *formul, std::string *oper,
             std::vector<std::string> regular);
  int Preority(std::string oper);
  void Redistribution(std::string oper);
  bool NotScob(std::string oper);
  void BracketClosed();
  void FromStackToQueue();
  void Compute();
};
}  // namespace s21

#endif  // MODELS_H

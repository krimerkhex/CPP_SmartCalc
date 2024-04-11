#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

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
}  // namespace s21

#endif  // DATA_STRUCT_H

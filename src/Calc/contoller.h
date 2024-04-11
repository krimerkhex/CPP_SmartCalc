#ifndef CONTOLLER_H
#define CONTOLLER_H

#include "models.h"

namespace s21 {

class Contoller {
 public:
  Contoller(ModelCalc* in_calc_model);
  Contoller(const Contoller& other) = delete;
  Contoller(Contoller&& other) = delete;
  Contoller& operator=(const Contoller& other) = delete;
  Contoller& operator=(Contoller&& other) = delete;
  ~Contoller();

  s21::clcltr_data* start_calc(s21::clcltr_data* temp) const;

 private:
  ModelCalc* calc_model_;
};

}  // namespace s21

#endif  // CONTOLLER_H

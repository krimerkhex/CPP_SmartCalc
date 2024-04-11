#include "models.h"

template <typename T>
s21::Model<T>::Model() {
  this->data = nullptr;
  this->error_ = false;
}

template <typename T>
unsigned s21::Model<T>::CountDay(unsigned month) {
  return 28 + ((month + month / 8) % 2) + (2 % month) + (2 * (1 / month));
}

s21::ModelCredit::ModelCredit() : Model() { ; }

bool s21::ModelCredit::Validation(s21::credit_data *in_data) {
  return in_data->sum_credit >= 0 && in_data->procent >= 0 &&
         in_data->time >= 0;
}

bool s21::ModelCredit::Distributio(s21::credit_data *temp) {
  if (!(error_ = this->Validation(temp))) {
    !this->data_->type && !this->error_ ? SimpleProcent() : HardProcent();
  }
  return this->error_;
}

// Ануетент
void s21::ModelCredit::SimpleProcent() {
  double loan_rate = this->data_->procent / 12. / 100.;
  double an_coef = loan_rate *
                   (powl(1 + loan_rate, (double)this->data_->time)) /
                   ((powl(1 + loan_rate, (double)this->data_->time) - 1));
  this->data_->sum_per_month.push_back(
      (an_coef * this->data_->sum_credit / this->data_->time));
  this->data_->gived_more = (this->data_->sum_per_month[0] * this->data_->time);
  this->data_->all_gived =
      fabs(this->data_->sum_credit + this->data_->gived_more);
}

// Дифура
void s21::ModelCredit::HardProcent() {
  double pays = this->data_->sum_credit / this->data_->time;
  for (int i = 0; i < this->data_->time; i++) {
    this->data_->sum_per_month.push_back(
        pays + (this->data_->sum_credit - (pays * i)) * 0.1 / 12);
    this->data_->all_gived += this->data_->sum_per_month[i];
  }
  this->data_->all_gived = fabs(this->data_->all_gived);
  this->data_->gived_more = fabs(this->data_->all_gived - data_->sum_credit);
}

// =================================================

s21::ModelDepozit::ModelDepozit() : Model() { ; }

bool s21::ModelDepozit::Validation(dpzt_data *in_data) {
  if (!in_data->payment_flag) this->data_->error = in_data->tax >= 0;
  return in_data->sum >= 0 && in_data->time >= 0 && in_data->procent >= 0;
}

bool s21::ModelDepozit::Distributio(s21::dpzt_data *temp) {
  if (!(this->data_->error = this->Validation(temp))) {
    !this->data_->payment_flag && !this->data_->error ? SimpleProcent()
                                                      : HardProcent();
  }
  return this->data_->error;
}

void s21::ModelDepozit::CheckContribution(int year, int month, int day) {
  for (auto it : this->data_->add_sub_list) {
    if (year == it.time.year && month == it.time.month && day == it.time.day &&
        !this->data_->error) {
      this->data_->sum += it.sum + it.flag_add;
      if (this->data_->sum <= 0) this->data_->error = true;
    }
  }
}

unsigned s21::ModelDepozit::CountRange(unsigned start_month,
                                       unsigned end_month) {
  auto ret_v = 0;
  for (unsigned l_month = data_->start_time.month;
       (int)l_month <= data_->start_time.month + data_->time; ++l_month) {
    ret_v += this->CountDay(!(l_month % 12) ? 12 : l_month % 12);
  }
  return ret_v;
}

void s21::ModelDepozit::AddingPastTime(time_data *date, unsigned *mouth) {
  (*mouth == 12) ? date->month = 1, date->year++ : date->month++;
}

void s21::ModelDepozit::SimpleProcent() {
  for (unsigned l_month = data_->start_time.month;
       (int)l_month <= data_->start_time.month + data_->time; ++l_month) {
    unsigned m_days = CountDay(l_month);
    for (unsigned l_day = data_->start_time.day; l_day <= m_days; ++l_day) {
      CheckContribution(data_->start_time.year, l_month, l_day);
      data_->sum_procent += data_->sum * data_->procent / 100. / 365.;
      data_->sum_tax += data_->sum_procent / 100. * data_->tax;
    }
    data_->start_time.day = 1;
    AddingPastTime(&data_->start_time, &l_month);
  }
  data_->sum_end = data_->sum + data_->sum_procent - data_->sum_tax;
}

void s21::ModelDepozit::Capital() {  // Карл Маркс одобряет
  this->data_->sum = this->data_->sum_end;
  this->data_->sum_end = 0;
}

void s21::ModelDepozit::Accrual(double period) {
  auto increase = this->data_->sum * (1 + this->data_->procent / period);
  auto temp = increase / this->data_->tax / 100.;
  this->data_->sum_procent += increase;
  this->data_->sum_tax += temp;
  this->data_->sum_end -= temp;
}

void s21::ModelDepozit::HardProcent() {
  int count_days = this->CountRange(this->data_->start_time.month,
                                    data_->start_time.month + data_->time);
  for (unsigned l_month = data_->start_time.month;
       (int)l_month <= data_->start_time.month + data_->time; ++l_month) {
    unsigned m_days = CountDay(l_month);
    for (unsigned l_day = data_->start_time.day; l_day <= m_days; ++l_day) {
      CheckContribution(data_->start_time.year, l_month, l_day);
      if (!this->data_->payment_per) {
        this->Accrual(count_days);
      }
      if (this->data_->payment_flag == 1) this->Capital();
    }
    if (this->data_->payment_per) {
      this->Accrual(this->data_->time);
    }
    if (this->data_->payment_flag == 2) this->Capital();
    data_->start_time.day = 1;
    AddingPastTime(&data_->start_time, &l_month);
  }
}

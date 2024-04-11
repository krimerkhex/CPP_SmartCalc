#include <gtest/gtest.h>

#include "Calc/models.h"

class CalcModelTest : public testing::Test {
 public:
  s21::ModelCalc *model;
  s21::clcltr_data *data;

  void SetUp() {
    model = new s21::ModelCalc();
    data = model->getData();
  }

  void TearDown() { delete model; }
};

TEST_F(CalcModelTest, Test_1) {
  data->formul = "-1+2+3-4+(-5)+6+7-8-9";
  EXPECT_EQ(-9, model->Calculation(data)->result);
}

TEST_F(CalcModelTest, Test_2) {
  data->formul = "9-(-0.30928)*3-4";
  EXPECT_EQ(std::round(5.93), std::round(model->Calculation(data)->result));
}

TEST_F(CalcModelTest, Test_3) {
  data->formul = "(132+sin(asin(sqrt(ln(log(228.11)))))-4*5^6*(123))";
  EXPECT_EQ(std::round(-7687367.07),
            std::round(model->Calculation(data)->result));
}

TEST_F(CalcModelTest, Test_4) {
  data->formul =
      "2*cos(1)+3*sin(2)-4*tan(1)+2*acos(0.32)-3*asin(0.2)+4*atan(2)-4*ln(10)+"
      "7*log(99)/4*x";
  data->x_value = 10;
  EXPECT_EQ(std::round(29.61), std::round(model->Calculation(data)->result));
}

TEST_F(CalcModelTest, Test_5) {
  data->formul =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  EXPECT_EQ(std::round(-30.07), std::round(model->Calculation(data)->result));
}

TEST_F(CalcModelTest, Test_6) {
  data->formul =
      "sin(1)+cos(1)+asin(1)+acos(1)+atan(1)+tan(1)+sqrt(16)+ln(10)+log(10)";
  EXPECT_EQ(std::round(12.598), std::round(model->Calculation(data)->result));
}

TEST_F(CalcModelTest, Test_7) {
  data->formul = "2^2^3*4";
  EXPECT_EQ(1024, model->Calculation(data)->result);
}

TEST_F(CalcModelTest, Test_8) {
  data->formul = "((2*5437mod521*224mod(3+2))*2000/500)mod3";
  EXPECT_EQ(1, model->Calculation(data)->result);
}

TEST_F(CalcModelTest, Test_9) {
  data->formul = "2*x*(2*x+1)+4";
  data->x_value = 3.15;
  EXPECT_EQ(49.99, model->Calculation(data)->result);
}

TEST_F(CalcModelTest, Test_10) {
  data->formul = "1e5";
  EXPECT_EQ(100000, model->Calculation(data)->result);
}

TEST_F(CalcModelTest, Test_11) {
  data->formul = "1e-2";
  EXPECT_EQ(0.01, model->Calculation(data)->result);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

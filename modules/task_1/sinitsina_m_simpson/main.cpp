// Copyright 2020 Sinitsina Maria
#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include<functional>
#include "./simpson.h"

double f1(std::vector<double> vec) {
  double x = vec[0];
  return (1 / (1 + x));
}

double f2(std::vector<double> vec) {
  double x = vec[0];
  return (sin(x * x));
}

double f3(std::vector<double> vec) {
  double x = vec[0];
  return (x / (x * x * x * x + 4));
}

TEST(Multiple_Trapez_Integraion, Test_1_Integral_with_2_dimension_f1) {
  int dimension = 2;
  std::vector<double> x(dimension);
  std::vector<double> y(dimension);
  x = { 0 };
  y = { 1 };
  const int n = 10;

  double result = 0.69315;
  double error = 0.0001;
  ASSERT_NEAR(result, SequentialIntegr(f1, x, y, n), error);
}

TEST(Multiple_Trapez_Integraion, Test_2_Integral_with_2_dimension_f2) {
  int dimension = 2;
  std::vector<double> x(dimension);
  std::vector<double> y(dimension);
  x = { 0 };
  y = { 1.6 };
  const int n = 8;

  double result = 0.846;
  double error = 0.001;
  ASSERT_NEAR(result, SequentialIntegr(f2, x, y, n), error);
}

TEST(Multiple_Trapez_Integraion, Test_3_Integral_with_2_dimension_f3) {
  int dimension = 2;
  std::vector<double> x(dimension);
  std::vector<double> y(dimension);
  x = { 0 };
  y = { 5 };
  const int n = 10;

  double result = 0.3727;
  double error = 0.001;
  ASSERT_NEAR(result, SequentialIntegr(f3, x, y, n), error);
}

TEST(Multiple_Trapez_Integraion, Test_4_Wrong_Data_Negative_in_n) {
  int dimension = 2;
  std::vector<double> x(dimension);
  std::vector<double> y(dimension);
  x = { 2, 1 };
  y = { -5, 6 };
  const int n = -100;
  ASSERT_ANY_THROW(SequentialIntegr(f1, x, y, n));
}

TEST(Multiple_Trapez_Integraion, Test_5_Wrong_Data_Negative_in_size_of_first_coordinate) {
  int dimension = 2;
  std::vector<double> x(dimension);
  std::vector<double> y(dimension);
  x = { 2 };
  y = { -5, 6 };
  const int n = 100;
  ASSERT_ANY_THROW(SequentialIntegr(f1, x, y, n));
}

TEST(Multiple_Trapez_Integraion, Test_6_Wrong_Data_Negative_in_size_of_second_coord) {
  int dimension = 2;
  std::vector<double> x(dimension);
  std::vector<double> y(dimension);
  x = { 2, 10 };
  y = { -5, 6, 13 };
  const int n = 100;
  ASSERT_ANY_THROW(SequentialIntegr(f1, x, y, n));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Copyright 2020 Sinitsina Maria
#include <gtest/gtest.h>
#include <cmath>
#include <vector>
#include<functional>
#include "tbb/tbb.h"
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

double f4(std::vector<double> vec) {
  return (vec[0]);
}

double f5(std::vector<double> vec) {
  double x = vec[0];
  double y = vec[1];
  return (x + 2 * sin(y));
}


TEST(Multiple_Simpson_Integraion_TBB, Test_1_Integral_with_1_dimension_f1) {
  int dim = 1;
  std::vector<double> x(dim);
  std::vector<double> y(dim);
  std::vector<double> lim = {};

  x = { 0 };
  y = { 1 };
  int n = 100;
  double result = 0.69315;
  double error = 1;
  int dimension = 0;

  double res = Simpson_Integr_TBB(f1, x, y, n, dimension, lim);
  ASSERT_NEAR(result, res, error);
}

TEST(Multiple_Simpson_Integraion_TBB, Test_2_Integral_with_1_dimension_f2) {
  int dim = 1;
  std::vector<double> x(dim);
  std::vector<double> y(dim);
  std::vector<double> lim = {};

  x = { 0 };
  y = { 1.6 };
  int n = 100;
  double result = 0.846;
  double error = 1;
  int dimension = 0;

  double res = Simpson_Integr_TBB(f2, x, y, n, dimension, lim);
  ASSERT_NEAR(result, res, error);
}

TEST(Multiple_Simpson_Integraion_TBB, Test_3_Integral_with_1_dimension_f3) {
  int dimension = 1;
  std::vector<double> x(dimension);
  std::vector<double> y(dimension);
  std::vector<double> lim = {};

  x = { 0 };
  y = { 5 };
  const int n = 100;

  double result = 0.3727;
  double error = 1;
  dimension = 0;

  double res = Simpson_Integr_TBB(f3, x, y, n, dimension, lim);
  ASSERT_NEAR(result, res, error);
}

TEST(Multiple_Simpson_Integraion_TBB, Test_4_Integral_with_1_dimension_f4) {
  int dim = 1;
  std::vector<double> x(dim);
  std::vector<double> y(dim);
  std::vector<double> lim = {};

  x = { 0 };
  y = { 1 };
  int n = 100;
  double result = 0.5;
  double error = 1;
  int dimension = 0;

  double res = Simpson_Integr_TBB(f4, x, y, n, dimension, lim);
  EXPECT_NEAR(result, res, error);
}

TEST(Multiple_Simpson_Integraion_TBB, Test_5_Integral_with_1_dimension_f5) {
  int dim = 2;
  std::vector<double> x(dim);
  std::vector<double> y(dim);
  x = { 0, 0 };
  y = { 0.2,  3.14159 };
  std::vector<double> lim = {};

  int dimension = 0;
  int n = 100;
  double result = 0.862832;
  double error = 1;

  double res = Simpson_Integr_TBB(f5, x, y, n, dimension, lim);
  EXPECT_NEAR(result, res, error);
}

TEST(Multiple_Simpson_Integraion_TBB, Test_6_Wrong_Data_Negative_in_n) {
  int dimension = 2;
  std::vector<double> x(dimension);
  std::vector<double> y(dimension);
  std::vector<double> lim = {};

  x = { 2, 1 };
  y = { -5, 6 };
  const int n = -100;

  ASSERT_ANY_THROW(Simpson_Integr_TBB(f4, x, y, n, dimension, lim));
}

TEST(Multiple_Simpson_Integraion_TBB, Test_7_Wrong_Data_Negative_in_size_of_first_coordinat) {
  int dimension = 2;
  std::vector<double> x(dimension);
  std::vector<double> y(dimension);
  std::vector<double> lim = {};

  x = { 2 };
  y = { -5, 6 };
  const int n = 100;

  ASSERT_ANY_THROW(Simpson_Integr_TBB(f4, x, y, n, dimension, lim));
}

TEST(Multiple_Simpson_Integraion_TBB, Test_8_Wrong_Data_Negative_in_size_of_second_coordinat) {
  int dimension = 2;
  std::vector<double> x(dimension);
  std::vector<double> y(dimension);
  std::vector<double> lim = {};

  x = { 2, 10 };
  y = { -5, 6, 13 };
  const int n = 100;

  ASSERT_ANY_THROW(Simpson_Integr_TBB(f4, x, y, n, dimension, lim));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

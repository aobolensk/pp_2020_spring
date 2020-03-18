// Copyright 2020 Vlasov Andrey
#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "./multi_integration_simpson.h"

double f1(std::vector<double> x) {
  return x[0] * x[0];
}

double f2(std::vector<double> x) {
  return 3 * x[0] * x[0] * x[0] + 2 * x[1] * x[1];
}

double f3(std::vector<double> x) {
  return x[0] + x[1] + x[2];
}

double f4(std::vector<double> x) {
  return sin(x[0]) + 2 * x[1] + x[2] * x[2];
}

double f5(std::vector<double> x) {
  return x[0] * x[0] + x[1] * x[1] + x[2] * x[2];
}

TEST(multi_integration_simpson, test1_n_is_negative) {
  double a = 0.0, b = 3.0;
  ASSERT_ANY_THROW(getIntegralSimpsonSequentional(f1, { a }, { b }, -1000));
}

TEST(multi_integration_simpson, test2_multiplicity_is_1) {
  double a = 0.0, b = 3.0;
  double res = getIntegralSimpsonSequentional(f1, { a }, { b }, 1000);
  ASSERT_NEAR(res, 9.0, 1e-5);
}

TEST(multi_integration_simpson, test3_multiplicity_is_2) {
  std::vector<double>a = { 0.0, 2.5 };
  std::vector<double>b = { 1.534, 3.12 };
  double res = getIntegralSimpsonSequentional(f2, a, b, 1000);
  ASSERT_NEAR(res, 17.65544267, 1e-5);
}

TEST(multi_integration_simpson, test4_multiplicity_is_3version_1) {
  std::vector<double>a = { -1.0, -2.0, -3.0 };
  std::vector<double>b = { 1.0, 3.0, 5.0 };
  double res = getIntegralSimpsonSequentional(f3, a, b, 1000);
  ASSERT_NEAR(res, 120.0, 1e-5);
}

TEST(multi_integration_simpson, test5_multiplicity_is_3_version_2) {
  std::vector<double>a = { 0.0, 2.5, 1.234 };
  std::vector<double>b = { 1.534, 3.12, 1.555 };
  double res = getIntegralSimpsonSequentional(f4, a, b, 1000);
  ASSERT_NEAR(res, 2.50377645, 1e-5);
}

TEST(multi_integration_simpson, test6_multiplicity_is_3_version_3) {
  std::vector<double>a = { 0.0, -10.0, 1.0 };
  std::vector<double>b = { 5.0, 10.0, 17.0 };
  double res = getIntegralSimpsonSequentional(f5, a, b, 1000);
  ASSERT_NEAR(res, 230400, 1e-5);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// Copyright 2020 Vlasov Andrey
#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "./multi_integration_simpson.h"

std::function<double(const std::vector<double>&)> f1 = [](const std::vector<double>& x) {
  return x[0] * x[0];
};

std::function<double(const std::vector<double>&)> f2 = [](const std::vector<double>& x) {
  return 3 * x[0] * x[0] * x[0] + 2 * x[1] * x[1];
};

std::function<double(const std::vector<double>&)> f3 = [](const std::vector<double>& x) {
  return x[0] + x[1] + x[2];
};

std::function<double(const std::vector<double>&)> f4 = [](const std::vector<double>& x) {
  return sin(x[0]) + 2 * x[1] + x[2] * x[2];
};

std::function<double(const std::vector<double>&)> f5 = [](const std::vector<double>& x) {
  return x[0] * x[0] + x[1] * x[1] + x[2] * x[2];
};


TEST(Multi_Integration_Simpson_omp, test1_n_is_negative) {
  double a = 0.0, b = 3.0;
  ASSERT_ANY_THROW(getIntegralSimpsonOpenMP(f1, { a }, { b }, -1000));
}

TEST(Multi_Integration_Simpson_omp, test2_multiplicity_is_1) {
  double a = 0.0, b = 3.0;
  double res = getIntegralSimpsonOpenMP(f1, { a }, { b }, 1000);
  ASSERT_NEAR(res, 9.0, 1e-5);
}

TEST(Multi_Integration_Simpson_omp, test3_multiplicity_is_2) {
  std::vector<double>a = { 0.0, 2.5 };
  std::vector<double>b = { 1.534, 3.12 };
  double res = getIntegralSimpsonOpenMP(f2, a, b, 1000);
  ASSERT_NEAR(res, 17.65544267, 1e-5);
}

TEST(Multi_Integration_Simpson_omp, test4_multiplicity_is_3_version_1) {
  std::vector<double>a = { -1.0, -2.0, -3.0 };
  std::vector<double>b = { 1.0, 3.0, 5.0 };
  double res = getIntegralSimpsonOpenMP(f3, a, b, 1000);
  ASSERT_NEAR(res, 120.0, 1e-5);
}

TEST(Multi_Integration_Simpson_omp, test5_multiplicity_is_3_version_2) {
  std::vector<double>a = { 0.0, 2.5, 1.234 };
  std::vector<double>b = { 1.534, 3.12, 1.555 };
  double res = getIntegralSimpsonOpenMP(f4, a, b, 1000);
  ASSERT_NEAR(res, 2.50377645, 1e-5);
}

TEST(Multi_Integration_Simpson_omp, test6_multiplicity_is_3_version_3) {
  std::vector<double>a = { 0.0, -10.0, 1.0 };
  std::vector<double>b = { 5.0, 10.0, 17.0 };
  double res = getIntegralSimpsonOpenMP(f5, a, b, 1000);
  ASSERT_NEAR(res, 230400, 1e-5);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

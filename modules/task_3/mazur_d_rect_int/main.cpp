// Copyright 2020 Mazur Daniil
#include <math.h>
#include <gtest/gtest.h>
#include <tbb/tbb.h>
#include <utility>
#include <vector>
#include <iostream>
#include "../../../modules/task_3/mazur_d_rect_int/rect_int.h"

std::function<double(const std::vector<double>&)> f1 = [](const std::vector<double>& x) {
  return (x[0] * x[0] * x[0] - x[1] * x[1]);
};

std::function<double(const std::vector<double>&)> f2 = [](const std::vector<double>& x) {
  return (cos(x[0]) * cos(x[0]) + x[1] * x[1]);
};

std::function<double(const std::vector<double>&)> f3 = [](const std::vector<double>& x) {
  return (x[2] / (3 * x[0] * x[0] + x[1] * x[1]));
};

std::function<double(const std::vector<double>&)> f4 = [](const std::vector<double>& x) {
  return x[0] * x[0] - 2 * x[1] - cos(x[2]) + 2;
};
std::function<double(const std::vector<double>&)> f5 = [](const std::vector<double>& x) {
  return x[0] * x[0] - sin(x[0]);
};

std::function<double(const std::vector<double>&)> f6 = [](const std::vector<double>& x) {
  return acosh(x[0]) + x[1] * x[1];
};

TEST(RectangleIntegration, Double_Integral_1) {
  std::vector<std::pair<double, double>> a(2);
  a = { {5, 17}, {21, 53}};
  int cuts = 50;
  EXPECT_NEAR(rectIntTbb(f1, a, cuts), 104704, 100);
}

TEST(RectangleIntegration, Double_Integral_2) {
  std::vector<std::pair<double, double>> a(2);
  a = { {5, 20}, {1, 5}};
  int cuts = 50;
  EXPECT_NEAR(rectIntTbb(f2, a, cuts), 652.2891, 20);
}

TEST(RectangleIntegration, Triple_Integral_3) {
  std::vector<std::pair<double, double>> a(3);
  a = { {4, 10}, {15, 20}, {1, 10} };
  int cuts = 50;
  EXPECT_NEAR(rectIntTbb(f3, a, cuts), 3.3218, 1);
}

TEST(RectangleIntegration, Triple_Integral_4) {
  std::vector<std::pair<double, double>> a(3);
  a = { {15, 25}, {30, 45}, {-1, 0.5} };
int cuts = 50;
  EXPECT_NEAR(rectIntTbb(f4, a, cuts), 75251.8655, 200);
}

TEST(RectangleIntegration, Triple_Integral_5) {
  std::vector<std::pair<double, double>> a(1);
  a = { {-32, 134}};
  int cuts = 50;
  EXPECT_NEAR(rectIntTbb(f5, a, cuts), 812956.0353, 200);
}

TEST(RectangleIntegration, Triple_Integral_6) {
  std::vector<std::pair<double, double>> a(2);
  a = { {41, 117}, {-10, 13}};
  int cuts = 50;
  EXPECT_NEAR(rectIntTbb(f6, a, cuts), 89767.3084, 200);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

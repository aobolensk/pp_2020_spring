// Copyright 2020 Mazur Daniil
#include <math.h>
#include <gtest/gtest.h>
#include <utility>
#include <vector>
#include <iostream>
#include "../../../modules/task_1/mazur_d_rect_int/rect_int.h"

double f1(std::vector<double> x) {
  return (x[0] * x[0] * x[0] - x[1] * x[1]);
}

double f2(std::vector<double> x) {
  return (cos(x[0]) * cos(x[0])+ x[1]*x[1]);
}

double f3(std::vector<double> x) {
  return (x[2] / (3 * x[0] * x[0] + x[1] * x[1]));
}

double f4(std::vector<double> x) {
  return x[0] * x[0] - 2 * x[1] - cos(x[2]) + 2;
}

double f5(std::vector<double> x) {
  return x[0] * x[0] - sin(x[0]);
}

double f6(std::vector<double> x) {
  return acosh(x[0]) + x[1] * x[1];
}

TEST(RectangleIntegration, Double_Integral_1) {
  std::vector<std::pair<double, double>> a(2);
  a = { {5, 17}, {21, 53}};
  int cuts = 100;
  EXPECT_NEAR(rectIntSequen(f1, a, cuts), 104704, 50);
}

TEST(RectangleIntegration, Double_Integral_2) {
  std::vector<std::pair<double, double>> a(2);
  a = { {5, 20}, {1, 5}};
  int cuts = 100;
  EXPECT_NEAR(rectIntSequen(f2, a, cuts), 652.2891, 10);
}

TEST(RectangleIntegration, Triple_Integral_3) {
  std::vector<std::pair<double, double>> a(3);
  a = { {4, 10}, {15, 20}, {1, 10} };
  int cuts = 100;
  EXPECT_NEAR(rectIntSequen(f3, a, cuts), 3.3218, 1);
}

TEST(RectangleIntegration, Triple_Integral_4) {
  std::vector<std::pair<double, double>> a(3);
  a = { {15, 25}, {30, 45}, {-1, 0.5} };
  int cuts = 100;
  EXPECT_NEAR(rectIntSequen(f4, a, cuts), 75251.8655, 50);
}

TEST(RectangleIntegration, Triple_Integral_5) {
  std::vector<std::pair<double, double>> a(1);
  a = { {-32, 134}};
  int cuts = 100;
  EXPECT_NEAR(rectIntSequen(f5, a, cuts), 812956.0353, 50);
}

TEST(RectangleIntegration, Triple_Integral_6) {
  std::vector<std::pair<double, double>> a(2);
  a = { {41, 117}, {-10, 13}};
  int cuts = 100;
  EXPECT_NEAR(rectIntSequen(f6, a, cuts), 89767.3084, 50);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

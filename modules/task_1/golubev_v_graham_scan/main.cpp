// Copyright 2020 Golubev Vladislav
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "./golubev_v_graham_scan.h"

TEST(Sequential_graham_scan, Test_lex_min) {
  std::size_t size = 10000;
  std::vector<std::pair<double, double> > v = generate_points(size);
  auto res = v[0];
  std::swap(v[0], v[time(0) % size]);

  auto min = get_lex_min(v);

  ASSERT_EQ(v[min], res);
}

TEST(Sequential_graham_scan, Test_get_determinant) {
  std::pair<double, double> x(0, 5);
  std::pair<double, double> y(-0.33, -0.35);
  std::pair<double, double> z(1.15, 6.17);

  ASSERT_DOUBLE_EQ(get_det(x, y, z), -5.7664);
}
TEST(Sequential_graham_scan, Test_get_zero_determinant) {
  std::pair<double, double> x(0, 5);
  std::pair<double, double> y(-0.33, -0.35);
  std::pair<double, double> z(0, 5);

  ASSERT_DOUBLE_EQ(get_det(x, y, z), 0);
}

TEST(Sequential_graham_scan, Test_polar_sort_small_points) {
  std::vector<std::pair<double, double> > result_sort(5);
  result_sort[0] = std::make_pair(0, 0);
  result_sort[1] = std::make_pair(1, 5);
  result_sort[2] = std::make_pair(2, 4);
  result_sort[3] = std::make_pair(3, 3);
  result_sort[4] = std::make_pair(4, 1);

  std::vector<std::pair<double, double> > result(5);
  result[0] = std::make_pair(0, 0);
  result[1] = std::make_pair(4, 1);
  result[2] = std::make_pair(3, 3);
  result[3] = std::make_pair(2, 4);
  result[4] = std::make_pair(1, 5);

  result_sort = polar_sort(result_sort);

  ASSERT_EQ(result_sort, result);
}

TEST(Sequential_graham_scan, Test_polar_sort_many_points) {
  std::size_t size = 10000;
  std::vector<std::pair<double, double> > result_sort = generate_points(size);

  std::vector<std::pair<double, double> > res(size);
  res[0] = std::make_pair(0, 0);
  for (std::size_t i = 1; i < size; ++i) {
    res[i] = std::make_pair(size - i, 10);
  }

  auto res1 = polar_sort(result_sort);

  ASSERT_EQ(res1, res);
}

TEST(Sequential_graham_scan, Test_polar_sort_with_set_size_15) {
  std::vector<std::pair<double, double> > trash(8);
  std::vector<std::pair<double, double> > res(8);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

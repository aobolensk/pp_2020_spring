// Copyright 2020 Golubev Vladislav
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "./golubev_v_graham_scan.h"

TEST(Sequential_graham_scan, test_polar_sort_small_points) {
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

TEST(Sequential_graham_scan, test_polar_sort_many_points) {
  std::size_t size = 10000;
  std::vector<std::pair<double, double> > result_sort = generate_points(size);

  std::vector<std::pair<double, double> > res(size);
  res[0] = std::make_pair(0, 0);
  for (int i = 1; i < size; ++i) {
    res[i] = std::make_pair(size - i, 10);
  }

  result_sort = polar_sort(result_sort);

  ASSERT_EQ(result_sort, res);
}

TEST(Sequential_graham_scan, Test_3) {
  ASSERT_EQ(1, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

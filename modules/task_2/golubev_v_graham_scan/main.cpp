// Copyright 2020 Golubev Vladislav
#include <gtest/gtest.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <random>
#include <stack>
#include "./golubev_v_graham_scan.h"

TEST(OMP_graham_scan, omp_lex_min) {
  std::size_t size = 10000;
  std::vector<std::pair<double, double> > v = generate_points(size);
  auto res = v[0];
  std::swap(v[0], v[time(0) % size]);

  auto min = omp_get_lex_min(v, 1);

  ASSERT_EQ(v[min], res);
}

TEST(OMP_graham_scan, omp_sort) {
  int size = 10000;
  std::vector<std::pair<double, double> > res = get_rand_set(size);
  std::vector<std::pair<double, double> > check(res);

  mp_sort(res.begin(), res.end(), 2);
  std::sort(check.begin(), check.end(), is_less);

  EXPECT_EQ(res, check);
}

TEST(OMP_graham_scan, omp_graham_scan_with_set_1) {
  auto area = get_test_set_1();
  auto res = omp_graham_scan(area, 2);
  std::vector<std::pair<double, double> > check(res.size());
  check[6] = std::make_pair(2, 6);
  check[5] = std::make_pair(5, 5);
  check[4] = std::make_pair(8, 3);
  check[3] = std::make_pair(7, -2);
  check[2] = std::make_pair(6, -4);
  check[1] = std::make_pair(1, -3);
  check[0] = std::make_pair(0, 0);

  ASSERT_EQ(res, check);
}

TEST(OMP_graham_scan, Test_graham_scan_with_set_2) {
  auto area = get_test_set_2();
  auto res = omp_graham_scan(area);
  std::vector<std::pair<double, double> > check(res.size());
  check[7] = std::make_pair(0, 2);
  check[6] = std::make_pair(2, 5);
  check[5] = std::make_pair(8, 5);
  check[4] = std::make_pair(9, 2);
  check[3] = std::make_pair(9, -4);
  check[2] = std::make_pair(4, -6);
  check[1] = std::make_pair(0, -6);
  check[0] = std::make_pair(-1, 0);

  ASSERT_EQ(res, check);
}

TEST(OMP_graham_scan, Test_graham_scan_with_set_3) {
  std::vector<std::pair<double, double> > area(10);
  for (std::size_t i = 0; i < area.size(); ++i) {
    area[i] = std::make_pair(static_cast<double>(i), static_cast<double>(i));
  }
  std::vector<std::pair<double, double> > check(2);
  check[0] = std::make_pair(0, 0);
  check[1] = std::make_pair(area.size() - 1, area.size() - 1);

  auto res = omp_graham_scan(area);

  ASSERT_EQ(res, check);
}

TEST(OMP_graham_scan, omp_sort_with_time) {
  int size = 20;
  auto area = get_rand_set(size);

  double t3 = omp_get_wtime();
  auto seq_res = omp_graham_scan(area);
  double t4 = omp_get_wtime();
  // std::cout << "seq_scan " << t4 - t3 << std::endl;

  double t1 = omp_get_wtime();
  auto omp_res = omp_graham_scan(area, 8);
  double t2 = omp_get_wtime();
  // std::cout << "omp_scan " << t2 - t1 << std::endl;


  // std::cout << "acceleration " << (t4 - t3) / (t2 - t1) << std::endl;

  EXPECT_EQ(omp_res, seq_res);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

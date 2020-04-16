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

TEST(OMP_graham_scan, Exception_when_number_of_threads_is_zero) {
  auto area = get_rand_set(10);
  ASSERT_ANY_THROW(omp_graham_scan(area.begin(), area.end(), 0));
}

TEST(OMP_graham_scan, Test_OMP_graham_scan_with_set_1) {
  auto area = get_test_set_1();
  auto res = omp_graham_scan(area.begin(), area.end());
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

TEST(OMP_graham_scan, Test_OMP_graham_scan_with_set_2) {
  auto area = get_test_set_2();
  auto res = omp_graham_scan(area.begin(), area.end());
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

TEST(OMP_graham_scan, Test_OMP_graham_scan_with_set_3) {
  std::vector<std::pair<double, double> > area(10);
  for (std::size_t i = 0; i < area.size(); ++i) {
    area[i] = std::make_pair(static_cast<double>(i), static_cast<double>(i));
  }
  std::vector<std::pair<double, double> > check(2);
  check[0] = std::make_pair(0, 0);
  check[1] = std::make_pair(area.size() - 1, area.size() - 1);

  auto res = omp_graham_scan(area.begin(), area.end());

  ASSERT_EQ(res, check);
}

TEST(OMP_graham_scan, Test_OMP_graham_scan_with_big_rand_set) {
  int size = 1000;
  auto area = get_rand_set(size);
  std::vector<std::pair<double, double> > check(size);

  auto res_omp = omp_graham_scan(area.begin(), area.end());
  auto res_std = graham_scan(area.begin(), area.end());

  ASSERT_EQ(res_omp, res_std);
}

/*TEST(OMP_graham_scan, Test_OMP_graham_scan_with_rand_set) {
  int size = 10000000;
  auto area = get_rand_set(size);
  std::vector<std::pair<double, double> > check(size);

  double t1 = omp_get_wtime();
  auto res_omp = omp_graham_scan(area.begin(), area.end());
  double t2 = omp_get_wtime();
  std::cout << "omp_scan " << t2 - t1 << std::endl;

  double t3 = omp_get_wtime();
  auto res_std = graham_scan(area.begin(), area.end());
  double t4 = omp_get_wtime();
  std::cout << "std_scan " << t4 - t3 << std::endl;
  std::cout << "acseleration " << (t4 - t3) / (t2 - t1) << std::endl;

  ASSERT_EQ(res_omp, res_std);
}*/

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

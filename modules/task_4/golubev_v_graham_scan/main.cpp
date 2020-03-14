// Copyright 2020 Golubev Vladislav
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <random>
#include <ctime>
#include "./golubev_v_graham_scan.h"


TEST(std_thread_graham_scan, Exception_when_number_of_threads_is_zero) {
  auto area = get_rand_set(10);
  ASSERT_ANY_THROW(std_thread_graham_scan(area.begin(), area.end(), 0));
}

TEST(std_thread_graham_scan, Test_std_thread_graham_scan_with_set_1) {
  auto area = get_test_set_1();
  auto res = std_thread_graham_scan(area.begin(), area.end());
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

TEST(std_thread_graham_scan, Test_std_thread_graham_scan_with_set_2) {
  auto area = get_test_set_2();
  auto res = std_thread_graham_scan(area.begin(), area.end());
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

TEST(std_thread_graham_scan, Test_std_thread_graham_scan_with_set_3) {
  std::vector<std::pair<double, double> > area(10);
  for (std::size_t i = 0; i < area.size(); ++i) {
    area[i] = std::make_pair(static_cast<double>(i), static_cast<double>(i));
  }
  std::vector<std::pair<double, double> > check(2);
  check[0] = std::make_pair(0, 0);
  check[1] = std::make_pair(area.size() - 1, area.size() - 1);

  auto res = std_thread_graham_scan(area.begin(), area.end());

  ASSERT_EQ(res, check);
}

TEST(std_thread_graham_scan, Test_std_thread_graham_scan_with_big_rand_set) {
  int size = 1000;
  auto area = get_rand_set(size);
  std::vector<std::pair<double, double> > check(size);

  auto res_std_thread = std_thread_graham_scan(area.begin(), area.end());
  auto res_std = graham_scan(area.begin(), area.end());

  ASSERT_EQ(res_std_thread, res_std);
}

/*TEST(std_threads_graham_scan, Test_std_thread_graham_scan_with_big_rand_set) {
  int size = 1000000;
  auto area = get_rand_set(size);

  std::clock_t t1 = clock();
  auto res_std_thread = std_thread_graham_scan(area.begin(), area.end());
  std::clock_t t2 = clock();
  double time1 = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
  std::cout << "std_thread " << time1 << std::endl;

  std::clock_t t3 = clock();
  auto res_std = graham_scan(area.begin(), area.end());
  std::clock_t t4 = clock();
  double time2 = static_cast<double>(t4 - t3) / CLOCKS_PER_SEC;
  std::cout << "std " << time2 << std::endl;
  std::cout << "acseleration " << time2 / time1 << std::endl;

  ASSERT_EQ(res_std_thread, res_std);
}*/

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
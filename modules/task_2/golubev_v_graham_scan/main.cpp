// Copyright 2020 Golubev Vladislav
#include <gtest/gtest.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <random>
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

TEST(OMP_graham_scan, DISABLED_omp_sort_with_time) {
  int size = 10000;
  std::vector<std::pair<double, double> > res = get_rand_set(size);
  std::vector<std::pair<double, double> > check(res);

  double t1 = omp_get_wtime();
  mp_sort(res.begin(), res.end(), 4);
  double t2 = omp_get_wtime();
  std::cout << "omp_sort " << t2 - t1 << std::endl;

  double t3 = omp_get_wtime();
  std::sort(check.begin(), check.end(), is_less);
  double t4 = omp_get_wtime();
  std::cout << "std_sort " << t4 - t3 << std::endl;

  EXPECT_EQ(res, check);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

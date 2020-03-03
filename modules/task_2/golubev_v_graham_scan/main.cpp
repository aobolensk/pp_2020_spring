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



TEST(DISABLED_Sequential_graham_scan, omp_sort) {
  int size = 100000000;
  std::vector<double> res_omp(size);
  std::vector<double> trash(size);
  /*for (int i = 0; i < res_omp.size(); ++i) {
    res_omp[i] = rand();
  }*/
  std::vector<double> res_seq(res_omp);

  double t1 = omp_get_wtime();
  mp_sort(res_omp.begin(), res_omp.end());
  merge(res_omp.begin(), res_omp.begin() + size / 2, res_omp.end());
  double t2 = omp_get_wtime();
  std::cout << "omp_sort " << t2 - t1 << std::endl;

  double t3 = omp_get_wtime();
  std::sort(res_seq.begin(), res_seq.end());
  double t4 = omp_get_wtime();
  std::cout << "std_sort " << t4 - t3 << std::endl;

  EXPECT_EQ(res_omp, trash);
}

TEST(Sequential_graham_scan, Test_merge) {
  int size = 10000000;
  std::mt19937 gen;
  std::vector<double> v(size);
  for (int i = 0; i < v.size(); ++i) {
    v[i] = gen() % 1000;
  }
  std::vector<double> check(v);

  std::sort(check.begin(), check.end());

  std::sort(v.begin(), v.begin() + size / 2);
  std::sort(v.begin() + size / 2, v.end());
  merge(v.begin(), v.begin() + size / 2, v.end());

  EXPECT_EQ(v, check);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

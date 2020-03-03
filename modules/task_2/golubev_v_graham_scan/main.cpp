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



TEST(Sequential_graham_scan, Test_graham_scan_with_big_set) {
  /*int size = 40000000;
  std::vector<double> res_omp(size);
  std::vector<double> trash(size);
  for (int i = 0; i < res_omp.size(); ++i) {
    res_omp[i] = rand();
  }
  std::vector<double> res_seq(res_omp);

  double t1 = omp_get_wtime();
  res_omp = mp_sort(res_omp);
  double t2 = omp_get_wtime();
  std::cout << t2 - t1 << std::endl;

  double t3 = omp_get_wtime();
  std::sort(res_seq.begin(), res_seq.end());
  double t4 = omp_get_wtime();
  std::cout << t4 - t3 << std::endl;

  EXPECT_EQ(res_omp, trash);*/
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Copyright 2020 Koltyushkina Yanina

#include <gtest/gtest.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "./radix_sort.h"

TEST(Radix_Sort_for_Double, Random_Mas_with_Negayive_Size) {
  ASSERT_ANY_THROW(RandMas(-1));
}

TEST(Radix_Sort_for_Double, Random_Mas_with_Low_More_Than_High) {
  ASSERT_ANY_THROW(RandMas(10, 10, 5));
}

TEST(Radix_Sort_for_Double, Radix_Sort_With_One_Elements) {
  omp_set_num_threads(8);
  int len = 1;
  double *mas1 = RandMas(1);
  double *mas2 = new double[1];
  for (int i = 0; i < 1; i++) {
    mas2[i] = mas1[i];
  }
  RadixSortAllParallel(&mas1, len);
  std::sort(mas2, mas2 + len);
  for (int i = 0; i < len; i++) {
    ASSERT_EQ(mas1[i], mas2[i]);
  }
}

TEST(Radix_Sort_for_Double, Radix_Sort_With_Smal_Size_And_Small_Elements) {
  omp_set_num_threads(8);
  int len = 3;
  int low = 2;
  int high = 10;
  double *mas1 = RandMas(len, low, high);
  double *mas2 = new double[len];
  for (int i = 0; i < len; i++) {
    mas2[i] = mas1[i];
  }
  RadixSortAllParallel(&mas1, len);
  std::sort(mas2, mas2 + len);
  for (int i = 0; i < len; i++) {
    ASSERT_EQ(mas1[i], mas2[i]);
  }
}

TEST(Radix_Sort_for_Double, Radix_Sort_With_Medium_Size_And_Small_Elements) {
  omp_set_num_threads(8);
  int len = 30;
  int low = 2;
  int high = 10;
  double *mas1 = RandMas(len, low, high);
  double *mas2 = new double[len];
  for (int i = 0; i < len; i++) {
    mas2[i] = mas1[i];
  }
  RadixSortAllParallel(&mas1, len);
  std::sort(mas2, mas2 + len);
  for (int i = 0; i < len; i++) {
    ASSERT_EQ(mas1[i], mas2[i]);
  }
}

TEST(Radix_Sort_for_Double, Radix_Sort_With_Smal_Size_And_Norm_Range_Elements) {
  omp_set_num_threads(8);
  int len = 10;
  int low = 2;
  int high = 450;
  double *mas1 = RandMas(len, low, high);
  double *mas2 = new double[len];
  for (int i = 0; i < len; i++) {
    mas2[i] = mas1[i];
  }
  RadixSortAllParallel(&mas1, len);
  std::sort(mas2, mas2 + len);
  for (int i = 0; i < len; i++) {
    ASSERT_EQ(mas1[i], mas2[i]);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

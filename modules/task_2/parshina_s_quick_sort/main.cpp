// Copyright 2020 Parshina Sophie
#include <omp.h>
#include <ctime>
#include <cmath>
#include <utility>
#include <algorithm>
#include <random>
#include <vector>
#include <iostream>
#include "gtest/gtest.h"
#include "../../../modules/task_2/parshina_s_quick_sort/quick_sort.h"

#define N 100000
#define THREADS_NUMBER 2
#define TESTS_NUMBER 20

TEST(Hoare_Quick_Sort_OpenMP, Can_Sort_Correctly) {
  double* arr = new double[N];
  Get_Random_Array(arr, N);
  Parallel_Division_Sort(arr, N, THREADS_NUMBER);
  ASSERT_EQ(1, IsSorted(arr, N));
}
TEST(Hoare_Quick_Sort_OpenMP, Can_Sort_Empty_Array) {
  double* arr = new double[N];
  for (int i = 0; i < N; i++) {
    arr[i] = 0;
  }
  Parallel_Division_Sort(arr, N, THREADS_NUMBER);
  double sum_element = 0.0;
  for (int i = 0; i < N; i++) {
    sum_element += arr[i];
  }
  ASSERT_EQ(sum_element, 0);
}
TEST(Hoare_Quick_Sort_OpenMP, Can_Sort_Fully_Double_Array) {
  double* arr = new double[N];
  Get_Random_Array(arr, N);
  for (int i = 0; i < N; i++) {
    arr[i] *= 3.1415926535;
  }
  Parallel_Division_Sort(arr, N, THREADS_NUMBER);
  ASSERT_EQ(1, IsSorted(arr, N));
}
TEST(Hoare_Quick_Sort_OpenMP, Can_Sort_Opposite_Elements) {
  double* arr = new double[N];
  Get_Random_Array(arr, N);
  for (int i = 0; i < N; i+=2) {
    arr[i] = arr[i + 1] * (-1);
  }
  double* arr2 = new double[N];
  Copy_elements(arr, arr2, N);
  Parallel_Division_Sort(arr, N, THREADS_NUMBER);
  qHoareSort(arr2, 0, N - 1);
  ASSERT_EQ((int)std::equal(&arr[0], &arr[N], &arr2[0]), 1);
}
TEST(Hoare_Quick_Sort_OpenMP, Can_Sort_Already_Sorted_Elements) {
  double* arr = new double[N];
  Get_Random_Array(arr, N);
  qHoareSort(arr, 0, N - 1);
  double* arr2 = new double[N];
  Copy_elements(arr, arr2, N);
  Parallel_Division_Sort(arr, N, THREADS_NUMBER);
  ASSERT_EQ((int)std::equal(&arr[0], &arr[N], &arr2[0]), 1);
}
TEST(Hoare_Quick_Sort_OpenMP, Can_Sort_Mixed_Array) {
  double* arr = new double[N];
  Get_Random_Array(arr, N);
  qHoareSort(arr, 0, N - 1);
  double* arr2 = new double[N];
  Copy_elements(arr, arr2, N);
  for (int i = 2; i < N; i += 3) {
    double temp = arr[i - 2];
    arr[i - 2] = arr[i];
    arr[i] = temp;
  }
  Parallel_Division_Sort(arr, N, THREADS_NUMBER);
  ASSERT_EQ((int)std::equal(&arr[0], &arr[N], &arr2[0]), 1);
}
TEST(Hoare_Quick_Sort_OpenMP, DISABLED_Compare_Seq_and_Omp_Average_Time) {
  double seq_summary_time = 0;
  double omp_summary_time = 0;

  std::vector<bool> sorted;
  double* arr = new double[N];
  double* arr2 = new double[N];

  for (int threads = THREADS_NUMBER; threads > 0; --threads) {
    seq_summary_time = 0;
    omp_summary_time = 0;

    for (int i = 0; i < TESTS_NUMBER; ++i) {
      Get_Random_Array(arr, N);
      Copy_elements(arr, arr2, N);

      double t1 = omp_get_wtime();
      qHoareSort(arr2, 0, N - 1);
      double t2 = omp_get_wtime() - t1;
      seq_summary_time += t2;

      double t3 = omp_get_wtime();
      Parallel_Division_Sort(arr, N, threads);
      double t4 = omp_get_wtime() - t3;
      omp_summary_time += t4;

      sorted.push_back(IsSorted(arr, N));
    }
    std::cout << '\n';
    std::cout << "Tests count:" << TESTS_NUMBER << '\n';
    std::cout << "Thread number: " << threads  << '\n';
    std::cout << "Sequential average time: " << (seq_summary_time*1000) / TESTS_NUMBER << " ms \n";
    std::cout << "Parallel average time: " << (omp_summary_time*1000) / TESTS_NUMBER << " ms \n";
  }
  delete[] arr;
  delete[] arr2;

  bool x = true;
  for (auto i : sorted)
    x = x && i;

  ASSERT_EQ(1, x);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

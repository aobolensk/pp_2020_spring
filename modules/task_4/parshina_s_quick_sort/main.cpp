// Copyright 2020 Parshina Sophie
#include <thread>
#include <utility>
#include <random>
#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>
#include <omp.h>
#include "gtest/gtest.h"
#include "../../../modules/task_4/parshina_s_quick_sort/quick_sort.h"

#define N 100000
#define THREADS_NUMBER 4

TEST(Hoare_Quick_Sort_THREADS, Can_Sort_Correctly) {
  double* arr = new double[N];
  Get_Random_Array(arr, N);
  qHoareSortThreads(arr, N, THREADS_NUMBER);
  ASSERT_EQ(1, IsSorted(arr, N));
}
TEST(Hoare_Quick_Sort_THREADS, Can_Sort_Empty_Array) {
  double* arr = new double[N];
  for (int i = 0; i < N; i++) {
    arr[i] = 0;
  }
  qHoareSortThreads(arr, N, THREADS_NUMBER);
  double sum_element = 0.0;
  for (int i = 0; i < N; i++) {
    sum_element += arr[i];
  }
  ASSERT_EQ(sum_element, 0);
}


TEST(Hoare_Quick_Sort_THREADS, Can_Sort_Opposite_Elements) {
  double* arr = new double[N];
  Get_Random_Array(arr, N);
  for (int i = 0; i < N; i+=2) {
    arr[i] = arr[i + 1] * (-1);
  }
  double* arr2 = new double[N];
  Copy_elements(arr, arr2, N);
  qHoareSortThreads(arr, N, THREADS_NUMBER);
  qHoareSort(arr2, 0, N - 1);
  ASSERT_EQ((int)std::equal(&arr[0], &arr[N], &arr2[0]), 1);
}
TEST(Hoare_Quick_Sort_THREADS, Can_Sort_Already_Sorted_Elements) {
  double* arr = new double[N];
  Get_Random_Array(arr, N);
  qHoareSort(arr, 0, N - 1);
  double* arr2 = new double[N];
  Copy_elements(arr, arr2, N);
  qHoareSortThreads(arr, N, THREADS_NUMBER);
  ASSERT_EQ((int)std::equal(&arr[0], &arr[N], &arr2[0]), 1);
}
TEST(Hoare_Quick_Sort_THREADS, Can_Sort_Mixed_Array) {
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
  qHoareSortThreads(arr, N, THREADS_NUMBER);
  ASSERT_EQ((int)std::equal(&arr[0], &arr[N], &arr2[0]), 1);
}

TEST(Hoare_Quick_Sort_THREADS, DISABLED_Compare_Seq_and_Threads_Average_Time) {
  double* arr = new double[N];
  double* arr2 = new double[N];
  std::vector<bool> sorted;

  Get_Random_Array(arr, N);
  Copy_elements(arr, arr2, N);

  auto start = std::chrono::system_clock::now();
  qHoareSort(arr2, 0, N - 1);
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> diff = end - start;
  std::cout << "Sequential time: " << diff.count() << '\n';
  sorted.push_back(IsSorted(arr2, N));

  auto start_par = std::chrono::system_clock::now();
  qHoareSortThreads(arr, N, THREADS_NUMBER);
  auto end_par = std::chrono::system_clock::now();
  std::chrono::duration<double> diff_par = end_par - start_par;
  std::cout <<"Parallel time: " << diff_par.count()<<" s"<<'\n';

  std::cout << "Acceleration = seqtime/partime = " << diff.count() / diff_par.count() << " " << '\n';
  sorted.push_back(IsSorted(arr, N));

  bool x = true;
  for (auto i : sorted)
    x = x && i;

  ASSERT_EQ(1, x);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

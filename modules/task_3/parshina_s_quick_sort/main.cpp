// Copyright 2020 Parshina Sophie
#include <tbb/tbb.h>
#include <tbb/task_group.h>
#include <tbb/tick_count.h>
#include <ctime>
#include <cmath>
#include <utility>
#include <algorithm>
#include <random>
#include <vector>
#include <iostream>
#include "gtest/gtest.h"
#include "../../../modules/task_3/parshina_s_quick_sort/quick_sort.h"

#define N 100000

TEST(Hoare_Quick_Sort_TBB, Can_Sort_Correctly) {
  double* arr = new double[N];
  Get_Random_Array(arr, N);
  qHoareSortTbb(arr, N);
  ASSERT_EQ(1, IsSorted(arr, N));
}
TEST(Hoare_Quick_Sort_TBB, Can_Sort_Empty_Array) {
  double* arr = new double[N];
  for (int i = 0; i < N; i++) {
    arr[i] = 0;
  }
  qHoareSortTbb(arr, N);
  double sum_element = 0.0;
  for (int i = 0; i < N; i++) {
    sum_element += arr[i];
  }
  ASSERT_EQ(sum_element, 0);
}
TEST(Hoare_Quick_Sort_TBB, Can_Sort_Opposite_Elements) {
  double* arr = new double[N];
  Get_Random_Array(arr, N);
  for (int i = 0; i < N; i+=2) {
    arr[i] = arr[i + 1] * (-1);
  }
  double* arr2 = new double[N];
  Copy_elements(arr, arr2, N);
  qHoareSortTbb(arr, N);
  qHoareSort(arr2, 0, N - 1);
  ASSERT_EQ((int)std::equal(&arr[0], &arr[N], &arr2[0]), 1);
}
TEST(Hoare_Quick_Sort_TBB, Can_Sort_Already_Sorted_Elements) {
  double* arr = new double[N];
  Get_Random_Array(arr, N);
  qHoareSort(arr, 0, N - 1);
  double* arr2 = new double[N];
  Copy_elements(arr, arr2, N);
  qHoareSortTbb(arr, N);
  ASSERT_EQ((int)std::equal(&arr[0], &arr[N], &arr2[0]), 1);
}
TEST(Hoare_Quick_Sort_TBB, Can_Sort_Mixed_Array) {
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
  qHoareSortTbb(arr, N);
  ASSERT_EQ((int)std::equal(&arr[0], &arr[N], &arr2[0]), 1);
}
TEST(Hoare_Quick_Sort_TBB, DISABLED_Compare_Seq_and_Tbb_Average_Time) {
  double* arr = new double[N];
  double* arr2 = new double[N];
  std::vector<bool> sorted;

  Get_Random_Array(arr, N);
  Copy_elements(arr, arr2, N);

  tbb::tick_count t1 = tbb::tick_count::now();
  qHoareSort(arr2, 0, N - 1);
  double seq_time = (tbb::tick_count::now() - t1).seconds();
  std::cout << "Sequential time: " << seq_time << " s" << '\n';
  sorted.push_back(IsSorted(arr2, N));

  tbb::tick_count t2 = tbb::tick_count::now();
  qHoareSortTbb(arr, N);
  double parallel_time = (tbb::tick_count::now() - t2).seconds();
  std::cout << "Parallel tbb time: " << parallel_time << " s" << '\n';
  std::cout << "Acceleration = seqtime/partime = " << seq_time/parallel_time << " " << '\n';
  sorted.push_back(IsSorted(arr, N));

  bool x = true;
  for (auto i : sorted)
    x = x && i;

  ASSERT_EQ(1, x);
}

int main(int argc, char **argv) {
  tbb::task_scheduler_init init(tbb::task_scheduler_init::automatic);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

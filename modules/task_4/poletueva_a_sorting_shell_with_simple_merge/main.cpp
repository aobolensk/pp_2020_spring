// Copyright 2020 Poletueva Anastasia
#include <gtest/gtest.h>
#include <thread>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>
#include <string>
#include <random>
#include <ctime>
#include "./poletueva_a_sorting_shell_with_simple_merge.h"

TEST(Sort_Shell_Seq, Test_1_Random_Shell) {
  std::vector<int> vec = getRandom(10);
  std::vector<int> res = SortShell(vec, 10);
  std::sort(vec.begin(), vec.end());
  ASSERT_EQ(vec, res);
}

TEST(Sort_Shell_Seq, Test_2_Merge_Of_Two_Vectors) {
  std::vector<int> vec1 = {3, 6, 9, 24, 2, 82};
  std::vector<int> vec2 = { 7, 32, 37, 15, 4, 45 };

  std::vector<int> res1 = SortShell(vec1, 6);
  std::vector<int> res2 = SortShell(vec2, 6);

  std::vector<int> res_merge = Merge_of_two_vectors(res1, res2);

  std::vector<int> res_s(vec1);

  res_s.insert(res_s.end(), vec2.begin(), vec2.end());

  std::sort(res_s.begin(), res_s.end());
  ASSERT_EQ(res_merge, res_s);
}

TEST(Sort_Shell_Seq, Test_3_Random_Merge_Of_Two_Vectors) {
  std::vector<int> vec1 = getRandom(5, 2);
  std::vector<int> vec2 = getRandom(10, 5);

  std::vector<int> res1 = SortShell(vec1, 5);
  std::vector<int> res2 = SortShell(vec2, 10);

  std::cout << std::endl;

  std::vector<int> res_merge = Merge_of_two_vectors(res1, res2);

  std::vector<int> res_s(vec1);

  res_s.insert(res_s.end(), vec2.begin(), vec2.end());

  std::sort(res_s.begin(), res_s.end());
  ASSERT_EQ(res_merge, res_s);
}

TEST(Sort_Shell_Seq, Test_4_Random_Merge) {
  std::vector<int> vec = getRandom(10);
  std::vector<std::vector<int>> a = division(vec, 4);

  for (unsigned int i = 0; i < a.size(); i++) {
    a[i] = SortShell(a[i], a[i].size());
  }

  std::vector<int> res = Merge(a, 4, 10);
  std::sort(vec.begin(), vec.end());
  ASSERT_EQ(vec, res);
}

TEST(Sort_Shell_Seq, Test_5_Random_Merge) {
  std::vector<int> vec = getRandom(100);

  std::vector<int> res = Shell_with_merge(vec, 4, 100);
  std::sort(vec.begin(), vec.end());
  ASSERT_EQ(vec, res);
}

TEST(Sort_Shell_STD, Test_6_Random_Merge) {
  const int size = 30;
  const int thread_count = 4;

  std::vector<int> vec = getRandom(size);

  std::vector<int> res = Shell_with_merge_std(vec, thread_count, size);
  std::sort(vec.begin(), vec.end());
  ASSERT_EQ(vec, res);
}

TEST(Sort_Shell_STD, Test_7_Random_Merge) {
  const int size = 20;
  const int thread_count = 2;

  std::vector<int> vec = getRandom(size);

  std::vector<int> res = Shell_with_merge_std(vec, thread_count, size);
  std::sort(vec.begin(), vec.end());
  ASSERT_EQ(vec, res);
}

TEST(Sort_Shell_STD, Test_8_Random_Merge) {
  const int size = 30;
  const int thread_count = 2;

  std::vector<int> vec = getRandom(size);

  std::vector<int> res = Shell_with_merge_std(vec, thread_count, size);
  std::sort(vec.begin(), vec.end());
  ASSERT_EQ(vec, res);
}
/*
TEST(Sort_Shell_STD, Test_9_Random_Merge_10000_4) {
  const int size = 10000;
  const int thread_count = 4;
  std::vector<int> vec = getRandom(size);

  clock_t t1 = clock();
  std::vector<int> res1 = Shell_with_merge_std(vec, thread_count, size);
  clock_t t2 = clock();

  double dt1 = (t2 - t1) / (double) CLOCKS_PER_SEC;

  clock_t t3 = clock();
  std::vector<int> res2 = Shell_with_merge(vec, thread_count, size);
  clock_t t4 = clock();

  double dt2 = (t4 - t3) / (double) CLOCKS_PER_SEC;

  std::cout << "time of seq = " << dt1 << std::endl;

  std::cout << "time of std::threads = " << dt2 << std::endl;

  ASSERT_EQ(res1, res2);
}

TEST(Sort_Shell_STD, Test_10_Random_Merge_10000003_4) {
  const int size = 1000003;
  const int thread_count = 4;

  std::vector<int> vec = getRandom(size);

  clock_t t1 = clock();
  std::vector<int> res1 = Shell_with_merge_std(vec, thread_count, size);
  clock_t t2 = clock();

  double dt1 = (t2 - t1) / (double) CLOCKS_PER_SEC;

  clock_t t3 = clock();
  std::vector<int> res2 = Shell_with_merge(vec, thread_count, size);
  clock_t t4 = clock();

  double dt2 = (t4 - t3) / (double) CLOCKS_PER_SEC;

  std::cout << "time of seq = " << dt2 << std::endl;

  std::cout << "time of std::threads = " << dt1 << std::endl;

  ASSERT_EQ(res1, res2);
}

TEST(Sort_Shell_STD, Test_11_Random_Merge_10000002_4) {
  const int size = 10000002;
  const int thread_count = 4;

  std::vector<int> vec = getRandom(size);

  clock_t t1 = clock();
  std::vector<int> res1 = Shell_with_merge_std(vec, thread_count, size);
  clock_t t2 = clock();

  double dt1 = (t2 - t1) / (double) CLOCKS_PER_SEC;

  clock_t t3 = clock();
  std::vector<int> res2 = Shell_with_merge(vec, thread_count, size);
  clock_t t4 = clock();

  double dt2 = (t4 - t3) / (double) CLOCKS_PER_SEC;

  std::cout << "time of seq = " << dt2 << std::endl;

  std::cout << "time of std::threads = " << dt1 << std::endl;

  ASSERT_EQ(res1, res2);
}

TEST(Sort_Shell_STD, Test_12_Random_Merge_10000002_2) {
  const int size = 10000002;
  const int thread_count = 2;

  std::vector<int> vec = getRandom(size);

  clock_t t1 = clock();
  std::vector<int> res1 = Shell_with_merge_std(vec, thread_count, size);
  clock_t t2 = clock();

  double dt1 = (t2 - t1) / (double) CLOCKS_PER_SEC;

  clock_t t3 = clock();
  std::vector<int> res2 = Shell_with_merge(vec, thread_count, size);
  clock_t t4 = clock();

  double dt2 = (t4 - t3) / (double) CLOCKS_PER_SEC;

  std::cout << "time of seq = " << dt2 << std::endl;

  std::cout << "time of std::threads = " << dt1 << std::endl;

  ASSERT_EQ(res1, res2);
}*/

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

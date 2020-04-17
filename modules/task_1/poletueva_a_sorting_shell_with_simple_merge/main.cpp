// Copyright 2020 Poletueva Anastasia
#include <gtest/gtest.h>
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

TEST(Sort_Shell_Seq, Test_2_Random_Shell) {
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

TEST(Sort_Shell_Seq, Test_3_Random_Shell) {
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
  std::vector<int> vec = getRandom(20);

  std::vector<int> res = Shell_with_merge(vec, 4, 20);
  std::sort(vec.begin(), vec.end());
  ASSERT_EQ(vec, res);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Copyright 2020 Bandenkov Daniil

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./shell_batcher.h"

TEST(test_Shell_Sort, test_on_20_elements) {
  std::vector<int> res = getRandomVector(20);
  std::vector<int> Shell = shellSort(res, 20);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(Shell, res);
}

TEST(test_merge_batcher, Merge) {
  std::vector<int> merg0 = getRandomVector(20);
  std::vector<int> merg1 = getRandomVector(20);
  std::sort(merg0.begin(), merg0.end());
  std::sort(merg1.begin(), merg1.end());
  std::vector<int>even = evenBatcher(merg0, merg0);
  std::vector<int>odd = oddBatcher(merg1, merg1);
  std::vector<int>res = mergeBatcher(even, odd);
  std::vector<int>stl_mege(40);
  std::merge(merg0.begin(), merg0.end(), merg1.begin(), merg1.end(), stl_mege.begin());
  ASSERT_EQ(stl_mege, res);
}

TEST(test_Shell_Betch_sort, test_on_20_elements) {
  std::vector<int> res = getRandomVector(20);
  std::vector<int> betch = shellBatch(res, 20);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

TEST(test_Shell_Betch_sort, test_on_100_elements) {
  std::vector<int> res = getRandomVector(100);
  std::vector<int> betch = shellBatch(res, 100);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

TEST(test_Shell_Betch_sort, test_on_1000_elements) {
  std::vector<int> res = getRandomVector(1000);
  std::vector<int> betch = shellBatch(res, 1000);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

TEST(test_Shell_Betch_sort, test_on_10000_elem) {
  std::vector<int> res = getRandomVector(10000);
  std::vector<int> betch = shellBatch(res, 10000);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Copyright 2020 Bandenkov Daniil
#include <gtest/gtest.h>
#include <tbb/tbb.h>
#include <vector>
#include <utility>
#include <functional>
#include <cmath>
#include <algorithm>
#include "./shell_batcher.h"

TEST(test_Shell_Betch_sort_seq, test_on_1000_element) {
  std::vector<int> res = getRandomVector(1000);
  std::vector<int> betch = shellBatcher_seq(res, 4, 1000);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

TEST(test_Shell_Betch_sort_tbb, test_on_20_elements_2_thread) {
  std::vector<int> res = getRandomVector(20);
  std::vector<int> betch = shellBatcher_tbb(res, 2, 20);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

TEST(test_Shell_Betch_sort_tbb, test_on_1000_elements_2_thread) {
  std::vector<int> res = getRandomVector(1000);
  std::vector<int> betch = shellBatcher_tbb(res, 2, 1000);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

TEST(test_Shell_Betch_sort_tbb, test_on_1000_elements_4_thread) {
  std::vector<int> res = getRandomVector(1000);
  std::vector<int> betch = shellBatcher_tbb(res, 4, 1000);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

TEST(test_Shell_Betch_sort_tbb, test_on_5000_elements_4_thread) {
  std::vector<int> res = getRandomVector(5000);
  std::vector<int> betch = shellBatcher_tbb(res, 4, 5000);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

TEST(test_Shell_Betch_sort_tbb, test_on_5000_elements_6_thread) {
  std::vector<int> res = getRandomVector(5000);
  std::vector<int> betch = shellBatcher_tbb(res, 6, 5000);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

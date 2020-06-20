// Copyright 2020 Bandenkov Daniil
#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include <functional>
#include <cmath>
#include <ctime>
#include <algorithm>
#include "./shell_batcher.h"

TEST(test_Shell_Betch_sort_seq, test_on_1000_element) {
  std::vector<int> res = getRandomVector(1000);
  std::vector<int> betch = shellBatcher_seq(res, 4, 1000);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

TEST(test_Shell_Betch_sort_std, test_on_1000_elements_2_threads) {
  std::vector<int> res = getRandomVector(1000);
  std::vector<int> betch = shellBatcher_std(res, 2, 1000);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

TEST(test_Shell_Betch_sort_std, test_on_1000_elements_4_threads) {
  std::vector<int> res = getRandomVector(1000);
  std::vector<int> betch = shellBatcher_std(res, 4, 1000);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

TEST(test_Shell_Betch_sort_std, test_on_5000_elements_4_threads) {
  std::vector<int> res = getRandomVector(5000);
  std::vector<int> betch = shellBatcher_std(res, 4, 5000);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

TEST(test_Shell_Betch_sort_std, test_on_5000_elements_6_threads) {
  std::vector<int> res = getRandomVector(5000);
  std::vector<int> betch = shellBatcher_std(res, 6, 5000);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(betch, res);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

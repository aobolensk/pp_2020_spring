// Copyright 2020 Kolesova Kristina

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./shell_sort_batch.h"

TEST(test_Shell_Sort, test_on_10_elements) {
  std::vector<int> res = randVec(10);
  std::vector<int> Shell = sortShell(res, 0, 9);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(Shell, res);
}

TEST(test_Betch_Shell_Sort, test_on) {
  std::vector<int> res1 = {35, 28, 5, 38, 93, 48, 16, 52, 2, 62};
  std::vector<int> Shell1 = shellBetchSort_omp(res1);
  std::sort(res1.begin(), res1.end());
  ASSERT_EQ(Shell1, res1);
}

TEST(test_Betch_Shell_Sort, test_on100) {
  std::vector<int> res = randVec(100);
  std::vector<int> Shell = shellBetchSort_omp(res);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(Shell, res);
}

TEST(test_Betch_Shell_Sort, test_on200) {
  std::vector<int> res = randVec(200);
  std::vector<int> Shell = shellBetchSort_omp(res);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(Shell, res);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

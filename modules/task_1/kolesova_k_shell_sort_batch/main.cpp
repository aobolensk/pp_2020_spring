

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include "./shell_sort_batch.h"

TEST(test_Shell_Sort, test_on_10_elements) {
  std::vector<int> res = randVec(10);
  std::vector<int> Shell = sortShell(res, 0, 10);
  std::sort(res.begin(), res.end());
  ASSERT_EQ(Shell, res);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
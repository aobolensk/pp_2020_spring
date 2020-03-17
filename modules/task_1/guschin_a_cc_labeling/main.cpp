// Copyright 2020 Guschin Alexander
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_1/guschin_a_cc_labeling/cc_labeling.h"

TEST(Sequential, No_Throw) {
  std::vector<std::vector<std::int8_t>> A(3, std::vector<std::int8_t>(3));
  A = {
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1}
  };
  ASSERT_NO_THROW(Labeling(A));
}

TEST(Sequential, Can_Lable_Pic) {
  std::vector<std::vector<std::int8_t>> A(3, std::vector<std::int8_t>(3));
  A = {
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1}
  };
  std::vector<std::vector<int>> res(3, std::vector<int>(3));
  res = {
    {1, 0, 2},
    {0, 2, 2},
    {2, 2, 2}
  };
  EXPECT_EQ(Labeling(A), res);
}

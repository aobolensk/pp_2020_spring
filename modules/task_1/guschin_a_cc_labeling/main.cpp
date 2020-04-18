// Copyright 2020 Guschin Alexander
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_1/guschin_a_cc_labeling/cc_labeling.h"

TEST(CC_Labeling, No_Throw) {
  std::vector<std::vector<std::int8_t>> A(3, std::vector<std::int8_t>(3));
  A = {
    {1, 0, 1},
    {0, 1, 1},
    {1, 1, 1}
  };
  ASSERT_NO_THROW(Labeling(A));
}

TEST(CC_Labeling, Can_Lable_Pic) {
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

TEST(CC_Labeling, Can_Lable_Another_Pic) {
  std::vector<std::vector<std::int8_t>> A(4, std::vector<std::int8_t>(4));
  A = {
    {1, 1, 0, 1},
    {0, 1, 1, 0},
    {1, 0, 1, 1},
    {0, 1, 1, 0}
  };
  std::vector<std::vector<int>> res(4, std::vector<int>(4));
  res = {
    {1, 1, 0, 2},
    {0, 1, 1, 0},
    {3, 0, 1, 1},
    {0, 1, 1, 0}
  };
  EXPECT_EQ(Labeling(A), res);
}

TEST(CC_Labeling, Can_Lable_Pic_With_Different_Size) {
  std::vector<std::vector<std::int8_t>> A(4, std::vector<std::int8_t>(2));
  A = {
    {1, 1},
    {0, 1},
    {1, 0},
    {1, 1}
  };
  std::vector<std::vector<int>> res(4, std::vector<int>(2));
  res = {
    {1, 1},
    {0, 1},
    {2, 0},
    {2, 2}
  };
  EXPECT_EQ(Labeling(A), res);
}

TEST(CC_Labeling, Can_Merge) {
  std::vector<std::vector<int>> A(4, std::vector<int>(4));
  A = {
    {3, 3, 0, 0},
    {0, 3, 0, 0},
    {4, 3, 0, 0},
    {0, 0, 0, 0}
  };
  std::vector<std::vector<int>> res(4, std::vector<int>(4));
  res = {
    {3, 3, 0, 0},
    {0, 3, 0, 0},
    {3, 3, 0, 0},
    {0, 0, 0, 0}
  };
  Merge(&A, 4, 3, 4, 4);
  EXPECT_EQ(A, res);
}

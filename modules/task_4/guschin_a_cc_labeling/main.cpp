// Copyright 2020 Guschin Alexander
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_4/guschin_a_cc_labeling/cc_labeling.h"

TEST(CC_Labeling_omp, Can_find_invalid_labeling) {
  std::vector<std::vector<std::int32_t>> A(4, std::vector<std::int32_t>(4));
  A = {{1, 1, 1, 0},
       {0, 1, 2, 2},
       {0, 1, 0, 2},
       {1, 1, 0, 1}};
  EXPECT_EQ(IsLabeled(A), false);
}

TEST(CC_Labeling_omp, Can_find_valid_labeling) {
  std::vector<std::vector<std::int32_t>> A(4, std::vector<std::int32_t>(4));
  A = {{1, 1, 1, 0},
       {0, 0, 1, 0},
       {0, 0, 0, 2},
       {2, 2, 2, 2}};
  EXPECT_EQ(IsLabeled(A), true);
}

TEST(CC_Labeling_omp, No_Throw) {
  std::vector<std::vector<std::int8_t>> A(4, std::vector<std::int8_t>(4));
  A = {{1, 1, 1, 0},
       {0, 1, 0, 1},
       {0, 1, 0, 1},
       {1, 1, 0, 1}};
  ASSERT_NO_THROW(Labeling_std(A));
}

TEST(CC_Labeling_omp, Can_lable_omp_with_premade_pic) {
  std::vector<std::vector<std::int8_t>> A(8, std::vector<std::int8_t>(4));
  A = {{1, 1, 1, 0},
       {0, 1, 0, 1},
       {1, 1, 0, 1},
       {1, 0, 1, 1},
       {1, 0, 0, 0},
       {1, 1, 1, 1},
       {1, 0, 0, 1},
       {0, 1, 0, 1}};
  std::vector<std::vector<std::int32_t>> res = Labeling_std(A);
  EXPECT_EQ(IsLabeled(res), true);
}

TEST(CC_Labeling_omp, Can_lable_omp_with_10000_pixel) {
  std::vector<std::vector<std::int8_t>> A(100, std::vector<std::int8_t>(100));
  Fill_random(&A);
  std::vector<std::vector<std::int32_t>>  res = Labeling_std(A);
  EXPECT_EQ(IsLabeled(res), true);
}


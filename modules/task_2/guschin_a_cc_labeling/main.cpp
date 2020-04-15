// Copyright 2020 Guschin Alexander
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_2/guschin_a_cc_labeling/cc_labeling.h"

TEST(CC_Labeling_omp, No_Throw) {
    std::vector<std::vector<std::int8_t>> A(3, std::vector<std::int8_t>(3));
  A = {{1, 1, 1, 0},
       {0, 1, 0, 1},
       {0, 1, 0, 1},
       {1, 1, 0, 1}};
    ASSERT_NO_THROW(Labeling_omp(A));
}

TEST(CC_Labeling_omp, No_Throw2) {
  std::vector<std::vector<std::int8_t>> A(10, std::vector<std::int8_t>(10));
  Fill_random(&A);
  ASSERT_NO_THROW(Labeling_omp(A));
}

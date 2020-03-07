// Copyright 2020 Zhivaev Artem

#include <omp.h>
#include <gtest/gtest.h>
#include "./strassen_mult_openmp.h"

TEST(Test, Test) {
  ASSERT_TRUE(true);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

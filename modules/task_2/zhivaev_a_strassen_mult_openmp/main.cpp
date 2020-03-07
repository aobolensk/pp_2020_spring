// Copyright 2020 Zhivaev Artem

#include <omp.h>
#include <gtest/gtest.h>
#include <vector>
#include "./strassen_mult_openmp.h"

TEST(Test, Test) {
  ASSERT_TRUE(true);
}

TEST(Sequential, Matrix_256x256) {
  const unsigned int kSize = 256;
  std::vector<double> a(kSize * kSize);
  std::vector<double> b(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> resultExpected(kSize * kSize);

  for (unsigned int i = 0; i < kSize * kSize; i++) {
    a[i] = i + 1;
    b[i] = kSize * kSize - i;
  }
  multSeq(kSize, a.data(), b.data(), resultExpected.data());

  strassenMult(kSize, a.data(), b.data(), result.data());

  ASSERT_EQ(resultExpected, result);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

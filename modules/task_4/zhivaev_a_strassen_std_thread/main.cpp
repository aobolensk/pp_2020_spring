// Copyright 2020 Zhivaev Artem

#include <gtest/gtest.h>

#include <vector>

#include "./strassen_std_thread.h"

const double EPSILON = 0.0000001;

void multSeq(int size, const double* a, const double* b, double* result);

TEST(Parallel, Matrix_64x64) {
  const int kSize = 64;
  std::vector<double> a(kSize * kSize);
  std::vector<double> b(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> expected(kSize * kSize);
  
  for (int i = 0; i < kSize * kSize; i++) {
    a[i] = i + 1;
    b[i] = kSize * kSize - i;
  }
  multSeq(kSize, a.data(), b.data(), expected.data());
  
  strassenMultStdThread(kSize, a.data(), b.data(), result.data());
  
  for (int i = 0; i < kSize * kSize; i++) {
    ASSERT_NEAR(expected[i], result[i], expected[i] * EPSILON);
  }
}

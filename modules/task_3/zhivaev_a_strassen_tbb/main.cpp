// Copyright 2020 Zhivaev Artem

#include <gtest/gtest.h>

#include <vector>

#include "./strassen_tbb.h"

const double EPSILON = 0.000001;

void multSeq(int size, const double* a, const double* b, double* result);

TEST(Parallel, Matrix_64x64) {
  const int size = 64;
  std::vector<double> a(size * size);
  std::vector<double> b(size * size);
  std::vector<double> result(size * size);
  std::vector<double> expected(size * size);

  for (int i = 0; i < size * size; i++) {
    a[i] = i + 1;
    b[i] = size * size - i;
  }
  multSeq(size, a.data(), b.data(), expected.data());

  multStrassenTbb(size, a.data(), b.data(), result.data());

  for (int i = 0; i < size * size; i++) {
    ASSERT_NEAR(expected[i], result[i], expected[i] * EPSILON);
  }
}

TEST(Parallel, DISABLED_Matrix_2048x2048) {
  const int size = 2048;
  std::vector<double> a(size * size);
  std::vector<double> b(size * size);
  std::vector<double> result(size * size);
  std::vector<double> expected(size * size);

  for (int i = 0; i < size * size; i++) {
    a[i] = i + 1;
    b[i] = size * size - i;
  }
  multSeq(size, a.data(), b.data(), expected.data());

  multStrassenTbb(size, a.data(), b.data(), result.data());

  for (int i = 0; i < size * size; i++) {
    ASSERT_NEAR(expected[i], result[i], expected[i] * EPSILON);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

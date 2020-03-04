// Copyright 2020 Zhivaev Artem

#include <gtest/gtest.h>

#include <array>
#include <vector>
#include <stdexcept>

#include "./strassen_mult.h"

TEST(Sequential, Assert_true) { ASSERT_TRUE(true); }

TEST(Sequential, Matrix_64x64) {
  const size_t kSize = 64;
  std::vector<double> a(kSize * kSize);
  std::vector<double> b(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> resultExpected(kSize * kSize);

  for (size_t i = 0; i < kSize * kSize; i++) {
    a[i] = i + 1;
    b[i] = kSize * kSize - i;
  }
  multSeq(kSize, a.data(), b.data(), resultExpected.data());

  strassenMultSeq(kSize, a.data(), b.data(), result.data());

  ASSERT_EQ(resultExpected, result);
}

TEST(Sequential, Throw_if_size_is_not_power_of_2) {
  const size_t kSize = 63;
  std::vector<double> a(kSize * kSize);
  std::vector<double> b(kSize * kSize);
  std::vector<double> result(kSize * kSize);

  ASSERT_THROW(strassenMultSeq(kSize, a.data(), b.data(), result.data()),
               std::invalid_argument);
}

TEST(Helper_Functions, Power_of_2) {
  size_t number = 1;
  for (int i = 0; i < sizeof(size_t) * CHAR_BIT; i++) {
    ASSERT_EQ(i, powerOf2(number));
    number *= 2;
  }
}

TEST(Helper_Functions, Split_matrix) {
  const size_t kSize = 8;
  std::vector<double> a(kSize * kSize);
  std::vector<double> a11(kSize * kSize / 4);
  std::vector<double> a12(kSize * kSize / 4);
  std::vector<double> a21(kSize * kSize / 4);
  std::vector<double> a22(kSize * kSize / 4);
  std::vector<double> a11Expected(kSize * kSize / 4);
  std::vector<double> a12Expected(kSize * kSize / 4);
  std::vector<double> a21Expected(kSize * kSize / 4);
  std::vector<double> a22Expected(kSize * kSize / 4);

  for (size_t i = 0; i < kSize * kSize; i++) {
    a[i] = i + 1;
  }
  a11Expected = {1, 2, 3, 4, 9, 10, 11, 12, 17, 18, 19, 20, 25, 26, 27, 28};
  a12Expected = {5, 6, 7, 8, 13, 14, 15, 16, 21, 22, 23, 24, 29, 30, 31, 32};
  a21Expected = {33, 34, 35, 36, 41, 42, 43, 44, 49, 50, 51, 52, 57, 58, 59, 60};
  a22Expected = {37, 38, 39, 40, 45, 46, 47, 48, 53, 54, 55, 56, 61, 62, 63, 64};

  splitMatrix(kSize, a.data(), a11.data(), a12.data(), a21.data(), a22.data());

  ASSERT_EQ(a11Expected, a11);
  ASSERT_EQ(a12Expected, a12);
  ASSERT_EQ(a21Expected, a21);
  ASSERT_EQ(a22Expected, a22);
}

TEST(Helper_Functions, Assemble_matrix) {
  const size_t kSize = 8;
  std::vector<double> a(kSize * kSize);
  std::vector<double> a11(kSize * kSize / 4);
  std::vector<double> a12(kSize * kSize / 4);
  std::vector<double> a21(kSize * kSize / 4);
  std::vector<double> a22(kSize * kSize / 4);
  std::vector<double> aExpected(kSize * kSize);

  for (size_t i = 0; i < kSize * kSize; i++) {
    aExpected[i] = i + 1;
  }
  a11 = {1, 2, 3, 4, 9, 10, 11, 12, 17, 18, 19, 20, 25, 26, 27, 28};
  a12 = {5, 6, 7, 8, 13, 14, 15, 16, 21, 22, 23, 24, 29, 30, 31, 32};
  a21 = {33, 34, 35, 36, 41, 42, 43, 44, 49, 50, 51, 52, 57, 58, 59, 60};
  a22 = {37, 38, 39, 40, 45, 46, 47, 48, 53, 54, 55, 56, 61, 62, 63, 64};

  assembleMatrix(kSize, a.data(), a11.data(), a12.data(), a21.data(),
                 a22.data());
  
  ASSERT_EQ(aExpected, a);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

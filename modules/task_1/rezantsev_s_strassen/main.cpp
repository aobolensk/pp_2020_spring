// Copyright 2020 Rezantsev Sergey
#include <vector>
#include "../../modules/task_1/rezantsev_s_strassen/strassen.h"
#include "gtest/gtest.h"

TEST(Strassen, correct_sum) {
  int n = 20;
  std::vector<double> a(n * n), b(n * n), c(n * n), res(n * n);
  for (int i = 0; i < n * n; i++) {
    a[i] = i;
    b[i] = n * n - i;
    c[i] = n * n;
  }
  res = sumMatrix(a, b, n);
  ASSERT_TRUE(isEqMatrix(c, res, n));
}

TEST(Strassen, correct_size) {
  int n = 64;
  int m = 50;
  int l = 31;
  ASSERT_EQ(checkSize(n), 64);
  ASSERT_EQ(checkSize(m), 64);
  ASSERT_EQ(checkSize(l), 32);
}

TEST(Strassen, correct_resize) {
  int n = 3;
  std::vector<double> a(n * n);
  std::vector<double> b(16);
  b[0] = 0;
  b[1] = 1;
  b[2] = 2;
  b[3] = 0;
  b[4] = 3;
  b[5] = 4;
  b[6] = 5;
  b[7] = 0;
  b[8] = 6;
  b[9] = 7;
  b[10] = 8;
  b[11] = 0;
  b[12] = 0;
  b[13] = 0;
  b[14] = 0;
  b[15] = 0;
  for (int i = 0; i < n * n; i++) {
    a[i] = i;
  }
  a = resizeMatrix(a, n);
  ASSERT_TRUE(isEqMatrix(a, b, n));
}

TEST(Strassen, correct_subt) {
  int n = 2;
  std::vector<double> a(n * n), b(n * n), c(n * n), res(n * n);
  for (int i = 0; i < n * n; i++) {
    a[i] = i;
    b[i] = i;
    c[i] = 0;
  }
  res = subtMatrix(a, b, n);
  ASSERT_TRUE(isEqMatrix(c, res, n));
}

TEST(Strassen, correct_mult) {
  int n = 2;
  std::vector<double> a(n * n), b(n * n), c(n * n), res(n * n);
  for (int i = 0; i < n * n; i++) {
    a[i] = i + 1;
    b[i] = i + n * n + 1;
  }
  c[0] = 19;
  c[1] = 22;
  c[2] = 43;
  c[3] = 50;
  res = multMatrix(a, b, n);
  ASSERT_TRUE(isEqMatrix(c, res, n));
}

TEST(Strassen, correct_split) {
  int n = 4;
  int m = 2;
  std::vector<double> a(n * n);
  std::vector<double> a11(m * m);
  std::vector<double> a12(m * m);
  std::vector<double> a21(m * m);
  std::vector<double> a22(m * m);
  std::vector<double> b11(m * m);
  std::vector<double> b12(m * m);
  std::vector<double> b21(m * m);
  std::vector<double> b22(m * m);

  b11[0] = 0;
  b11[1] = 1;
  b11[2] = 4;
  b11[3] = 5;

  b12[0] = 2;
  b12[1] = 3;
  b12[2] = 6;
  b12[3] = 7;

  b21[0] = 8;
  b21[1] = 9;
  b21[2] = 12;
  b21[3] = 13;

  b22[0] = 10;
  b22[1] = 11;
  b22[2] = 14;
  b22[3] = 15;

  for (int i = 0; i < n * n; i++) {
    a[i] = i;
  }
  splitMatrix(a, &a11, &a22, &a12, &a21, n);
  ASSERT_TRUE(isEqMatrix(b11, a11, m));
  ASSERT_TRUE(isEqMatrix(b12, a12, m));
  ASSERT_TRUE(isEqMatrix(b22, a22, m));
  ASSERT_TRUE(isEqMatrix(b21, a21, m));
}

TEST(Strassen, correct_collect) {
  int n = 4;
  int m = 2;
  std::vector<double> a(n * n), b(n * n);
  std::vector<double> b11(m * m);
  std::vector<double> b12(m * m);
  std::vector<double> b21(m * m);
  std::vector<double> b22(m * m);
  b11[0] = 0;
  b11[1] = 1;
  b11[2] = 4;
  b11[3] = 5;

  b12[0] = 2;
  b12[1] = 3;
  b12[2] = 6;
  b12[3] = 7;

  b21[0] = 8;
  b21[1] = 9;
  b21[2] = 12;
  b21[3] = 13;

  b22[0] = 10;
  b22[1] = 11;
  b22[2] = 14;
  b22[3] = 15;
  for (int i = 0; i < n * n; i++) {
    a[i] = i;
  }
  b = collectMatrix(b11, b22, b12, b21, m);
  ASSERT_TRUE(isEqMatrix(b, a, n));
}

TEST(Strassen, correct_strassen_4x4) {
  int n = 4;
  std::vector<double> a(n * n), b(n * n), c(n * n), d(n * n);
  for (int i = 0; i < n * n; i++) {
    a[i] = 2;
    b[i] = 1;
  }
  c = multMatrix(a, b, n);
  d = strassen(a, b, n);
  ASSERT_TRUE(isEqMatrix(c, d, n));
}

TEST(Strassen, correct_strassen_8x8) {
  int n = 8;
  std::vector<double> a(n * n), b(n * n), c(n * n), d(n * n);
  for (int i = 0; i < n * n; i++) {
    a[i] = i;
    b[i] = n * n - i;
  }
  c = multMatrix(a, b, n);
  d = strassen(a, b, n);
  ASSERT_TRUE(isEqMatrix(c, d, n));
}

TEST(Strassen, correct_strassen_16x16) {
  int n = 16;
  std::vector<double> a(n * n), b(n * n), c(n * n), d(n * n);
  for (int i = 0; i < n * n; i++) {
    a[i] = i;
    b[i] = n * n - i;
  }
  c = multMatrix(a, b, n);
  d = strassen(a, b, n);
  ASSERT_TRUE(isEqMatrix(c, d, n));
}

TEST(Strassen, correct_strassen_16x16_1) {
  int n = 16;
  std::vector<double> a(n * n), b(n * n), c(n * n), d(n * n);
  for (int i = 0; i < n * n; i++) {
    a[i] = i;
    b[i] = (n * n - i) * 2;
  }
  c = multMatrix(a, b, n);
  d = strassen(a, b, n);
  ASSERT_TRUE(isEqMatrix(c, d, n));
}

TEST(Strassen, correct_strassen_16x16_2) {
  int n = 16;
  std::vector<double> a(n * n), b(n * n), c(n * n), d(n * n);
  for (int i = 0; i < n * n; i++) {
    a[i] = i * n;
    b[i] = n * n - i;
  }
  c = multMatrix(a, b, n);
  d = strassen(a, b, n);
  ASSERT_TRUE(isEqMatrix(c, d, n));
}

TEST(Strassen, correct_strassen_10x10) {
  int n = 16;
  std::vector<double> a(n * n);
  std::vector<double> b(n * n);
  std::vector<double> c;
  std::vector<double> d;
  for (int i = 0; i < n * n; i++) {
    a[i] = 10;
    b[i] = 5;
  }
  a = resizeMatrix(a, n);
  b = resizeMatrix(b, n);
  n = checkSize(n);
  c = multMatrix(a, b, n);
  d = strassen(a, b, n);
  ASSERT_TRUE(isEqMatrix(c, d, n));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

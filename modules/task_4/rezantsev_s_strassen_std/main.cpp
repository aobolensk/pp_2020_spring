// Copyright 2020 Rezantsev Sergey
#include <time.h>
#include <thread>
#include <vector>
#include "../../modules/task_4/rezantsev_s_strassen_std/strassen.h"
#include "gtest/gtest.h"

TEST(Strassen_std, correct_strassen_4x4) {
  int n = 4;
  std::vector<double> a(n * n), b(n * n), c(n * n), d(n * n);
  for (int i = 0; i < n * n; i++) {
    a[i] = 2;
    b[i] = 1;
  }
  c = multMatrix(a, b, n);
  strassen_std(a, b, &d);
  ASSERT_TRUE(isEqMatrix(c, d, n));
}

TEST(Strassen_std, correct_strassen_8x8) {
  int n = 8;
  std::vector<double> a(n * n), b(n * n), c(n * n), d(n * n);
  for (int i = 0; i < n * n; i++) {
    a[i] = i;
    b[i] = n * n - i;
  }
  c = multMatrix(a, b, n);
  strassen_std(a, b, &d);
  ASSERT_TRUE(isEqMatrix(c, d, n));
}

TEST(Strassen_std, correct_strassen_16x16) {
  int n = 16;
  std::vector<double> a(n * n), b(n * n), c(n * n), d(n * n);
  for (int i = 0; i < n * n; i++) {
    a[i] = i;
    b[i] = n * n - i;
  }
  c = multMatrix(a, b, n);
  strassen_std(a, b, &d);
  ASSERT_TRUE(isEqMatrix(c, d, n));
}

TEST(Strassen_std, correct_strassen_16x16_1) {
  int n = 16;
  std::vector<double> a(n * n), b(n * n), c(n * n), d(n * n);
  for (int i = 0; i < n * n; i++) {
    a[i] = i;
    b[i] = (n * n - i) * 2;
  }
  c = multMatrix(a, b, n);
  strassen_std(a, b, &d);
  ASSERT_TRUE(isEqMatrix(c, d, n));
}

TEST(Strassen_std, correct_strassen_16x16_2) {
  int n = 16;
  std::vector<double> a(n * n), b(n * n), c(n * n), d(n * n);
  for (int i = 0; i < n * n; i++) {
    a[i] = i * n;
    b[i] = n * n - i;
  }
  c = multMatrix(a, b, n);
  strassen_std(a, b, &d);
  ASSERT_TRUE(isEqMatrix(c, d, n));
}
/*
TEST(Strassen_std, correct_strassen_128x128) {
  int n = 64;
  std::vector<double> a(n * n), b(n * n), c, d(n * n);
  for (int i = 0; i < n * n; i++) {
    a[i] = i;
    b[i] = n * n - i;
  }
  double p1, p2, t1, t2;
  t1 = clock();
  strassen_std(a, b, &d);
  t2 = clock();
  t2 -= t1;
  t2 /= CLOCKS_PER_SEC;
  std::cout << "std\t" << t2 << std::endl;
  p1 = clock();
  c = strassen(a, b, n);
  p2 = clock();
  p2 -= p1;
  p2 /= CLOCKS_PER_SEC;
  std::cout << "seq\t" << p2 << std::endl;
  ASSERT_TRUE(isEqMatrix(c, d, n));
}
*/

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

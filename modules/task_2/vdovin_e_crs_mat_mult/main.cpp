// Copyright 2020 Vdovin Eugene
#include <gtest/gtest.h>
#include <vector>
#include <complex>
#include <cmath>
#include "./crs_mat_mult.h"

TEST(CRSMatrix, test_copy_1) {
  std::vector<std::complex<double>> v = { 1, 2, 3, 4, 8, 5, 7, 1, 6 };
  std::vector<int> c = { 0, 4, 2, 3, 3, 5, 1, 2, 5 };
  std::vector<int> r = { 0, 2, 4, 4, 6, 6, 9 };

  CRSMatrix a(6, 9, v, c, r);
  CRSMatrix b(6, 9, v, c, r);

  EXPECT_EQ(a, b);
}

TEST(CRSMatrix, test_copy_2) {
  std::vector<std::complex<double>> v = { 1, 2, 3, 4, 8, 5, 7, 1, 6 };
  std::vector<int> c = { 0, 4, 2, 3, 3, 5, 1, 2, 5 };
  std::vector<int> r = { 0, 2, 4, 4, 6, 6, 9 };

  CRSMatrix a(6, 9, v, c, r);
  CRSMatrix b(a);

  EXPECT_EQ(a, b);
}

TEST(CRSMatrix, test_equally) {
  std::vector<std::complex<double>> v = { 1, 2, 3, 4, 8, 5, 7, 1, 6 };
  std::vector<int> c = { 0, 4, 2, 3, 3, 5, 1, 2, 5 };
  std::vector<int> r = { 0, 2, 4, 4, 6, 6, 9 };

  CRSMatrix a(6, 9, v, c, r);
  CRSMatrix b;
  b = a;

  EXPECT_EQ(a, b);
}

TEST(CRSMatrix, test_transpose) {
  std::vector<std::complex<double>> vt = { 1, 7, 3, 1, 4, 8, 2, 5, 6 };
  std::vector<int> ct = { 0, 5, 1, 5, 1, 3, 0, 3, 5 };
  std::vector<int> rt = { 0, 1, 2, 4, 6, 7, 9 };

  std::vector<std::complex<double>> v = { 1, 2, 3, 4, 8, 5, 7, 1, 6 };
  std::vector<int> c = { 0, 4, 2, 3, 3, 5, 1, 2, 5 };
  std::vector<int> r = { 0, 2, 4, 4, 6, 6, 9 };

  CRSMatrix a(6, 9, v, c, r);
  CRSMatrix at(6, 9, vt, ct, rt);

  EXPECT_EQ(at, a.transpose());
}

TEST(CRSMatrix, test_multiplicate) {
  std::vector<std::complex<double>> vm = { 1, 2, 32, 20, 35, 5, 64, 70, 42, 27, 28, 36 };
  std::vector<int> cm = { 0, 4, 3, 5, 1, 2, 3, 5, 1, 2, 3, 5 };
  std::vector<int> rm = { 0, 2, 4, 4, 8, 8, 12 };

  std::vector<std::complex<double>> v = { 1, 2, 3, 4, 8, 5, 7, 1, 6 };
  std::vector<int> c = { 0, 4, 2, 3, 3, 5, 1, 2, 5 };
  std::vector<int> r = { 0, 2, 4, 4, 6, 6, 9 };

  CRSMatrix a(6, 9, v, c, r);
  CRSMatrix b(6, 9, v, c, r);
  CRSMatrix ab(6, 12, vm, cm, rm);

  EXPECT_EQ(ab, a * b);
}

/*TEST(CRSMatrix, test_build) {
    CRSMatrix a(20000, 100000);
    CRSMatrix b(20000, 100000);

    a.buildRandomCRSMatrix();
    b.buildRandomCRSMatrix();

    a.getThreads(1);
    unsigned int start1_time = clock();
    a * b;
    unsigned int end1_time = clock();
    std::cout << "Lin time: " << (end1_time - start1_time) / 1000.0 << std::endl;

    a.getThreads(4);
    unsigned int start2_time = clock();
    a * b;
    unsigned int end2_time = clock();
    std::cout << "Par time: " << (end2_time - start2_time) / 1000.0 << std::endl;

    EXPECT_EQ(0, 0);
}*/

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

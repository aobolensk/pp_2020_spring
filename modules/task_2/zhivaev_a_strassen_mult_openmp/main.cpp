// Copyright 2020 Zhivaev Artem

#include <gtest/gtest.h>
#include <omp.h>

#include <vector>

#include "./strassen_mult_openmp.h"

void multSeq(unsigned int size, const double* a, const double* b,
             double* result);
void strassen1(unsigned int size, const double* a1, const double* a2,
               const double* b1, const double* b2, double* result);
void strassen2(unsigned int size, const double* a1, const double* a2,
               const double* b, double* result);
void strassen3(unsigned int size, const double* a, const double* b1,
               const double* b2, double* result);
void strassen4(unsigned int size, const double* a1, const double* a2,
               const double* b1, const double* b2, double* result);
unsigned int nextPowerOf2(unsigned int number);

TEST(Helper_Functions, Next_power_of_2) {
  ASSERT_EQ(1u, nextPowerOf2(1));
  ASSERT_EQ(2u, nextPowerOf2(2));
  ASSERT_EQ(4u, nextPowerOf2(4));
  ASSERT_EQ(8u, nextPowerOf2(8));
  ASSERT_EQ(16u, nextPowerOf2(16));
  ASSERT_EQ(32u, nextPowerOf2(32));
  ASSERT_EQ(64u, nextPowerOf2(64));
  ASSERT_EQ(128u, nextPowerOf2(128));
  ASSERT_EQ(256u, nextPowerOf2(256));
  ASSERT_EQ(512u, nextPowerOf2(512));
  ASSERT_EQ(1024u, nextPowerOf2(1024));
  ASSERT_EQ(2048u, nextPowerOf2(2048));
  ASSERT_EQ(4096u, nextPowerOf2(4096));
  ASSERT_EQ(4u, nextPowerOf2(3));
  ASSERT_EQ(8u, nextPowerOf2(5));
  ASSERT_EQ(8u, nextPowerOf2(7));
  ASSERT_EQ(16u, nextPowerOf2(9));
  ASSERT_EQ(16u, nextPowerOf2(15));
  ASSERT_EQ(32u, nextPowerOf2(17));
  ASSERT_EQ(32u, nextPowerOf2(31));
  ASSERT_EQ(64u, nextPowerOf2(63));
  ASSERT_EQ(64u, nextPowerOf2(33));
  ASSERT_EQ(128u, nextPowerOf2(65));
  ASSERT_EQ(128u, nextPowerOf2(127));
  ASSERT_EQ(256u, nextPowerOf2(129));
  ASSERT_EQ(256u, nextPowerOf2(255));
  ASSERT_EQ(512u, nextPowerOf2(257));
  ASSERT_EQ(512u, nextPowerOf2(511));
  ASSERT_EQ(1024u, nextPowerOf2(513));
  ASSERT_EQ(1024u, nextPowerOf2(1023));
  ASSERT_EQ(2048u, nextPowerOf2(2047));
  ASSERT_EQ(4096u, nextPowerOf2(4095));
}

TEST(Helper_Functions, Strassen1) {
  const unsigned int kSize = 32;
  std::vector<double> a1(kSize * kSize);
  std::vector<double> a2(kSize * kSize);
  std::vector<double> b1(kSize * kSize);
  std::vector<double> b2(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> expected(kSize * kSize);

  for (unsigned int i = 0; i < kSize * kSize; i++) {
    a1[i] = i + 1;
    a2[i] = i + 1;
    b1[i] = i + 1;
    b2[i] = i + 1;
  }
  for (unsigned int i = 0; i < kSize; i++) {
    for (unsigned int j = 0; j < kSize; j++) {
      expected[i * kSize + j] = 0.0;
      for (unsigned int k = 0; k < kSize; k++) {
        expected[i * kSize + j] += (a1[i * kSize + k] + a2[i * kSize + k]) *
                                   (b1[k * kSize + j] + b2[k * kSize + j]);
      }
    }
  }

  strassen1(kSize, a1.data(), a2.data(), b1.data(), b2.data(), result.data());

  ASSERT_EQ(expected, result);
}

TEST(Helper_Functions, Strassen2) {
  const unsigned int kSize = 32;
  std::vector<double> a1(kSize * kSize);
  std::vector<double> a2(kSize * kSize);
  std::vector<double> b(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> expected(kSize * kSize);

  for (unsigned int i = 0; i < kSize * kSize; i++) {
    a1[i] = i + 1;
    a2[i] = i + 1;
    b[i] = i + 1;
  }
  for (unsigned int i = 0; i < kSize; i++) {
    for (unsigned int j = 0; j < kSize; j++) {
      expected[i * kSize + j] = 0.0;
      for (unsigned int k = 0; k < kSize; k++) {
        expected[i * kSize + j] +=
            (a1[i * kSize + k] + a2[i * kSize + k]) * (b[k * kSize + j]);
      }
    }
  }

  strassen2(kSize, a1.data(), a2.data(), b.data(), result.data());

  ASSERT_EQ(expected, result);
}

TEST(Helper_Functions, Strassen3) {
  const unsigned int kSize = 32;
  std::vector<double> a(kSize * kSize);
  std::vector<double> b1(kSize * kSize);
  std::vector<double> b2(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> expected(kSize * kSize);

  for (unsigned int i = 0; i < kSize * kSize; i++) {
    a[i] = i + 1;
    b1[i] = i + 1;
    b2[i] = i + 1;
  }
  for (unsigned int i = 0; i < kSize; i++) {
    for (unsigned int j = 0; j < kSize; j++) {
      expected[i * kSize + j] = 0.0;
      for (unsigned int k = 0; k < kSize; k++) {
        expected[i * kSize + j] +=
            (a[i * kSize + k]) * (b1[k * kSize + j] - b2[k * kSize + j]);
      }
    }
  }

  strassen3(kSize, a.data(), b1.data(), b2.data(), result.data());

  ASSERT_EQ(expected, result);
}

TEST(Helper_Functions, Strassen4) {
  const unsigned int kSize = 32;
  std::vector<double> a1(kSize * kSize);
  std::vector<double> a2(kSize * kSize);
  std::vector<double> b1(kSize * kSize);
  std::vector<double> b2(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> expected(kSize * kSize);

  for (unsigned int i = 0; i < kSize * kSize; i++) {
    a1[i] = i + 1;
    a2[i] = i + 1;
    b1[i] = i + 1;
    b2[i] = i + 1;
  }
  for (unsigned int i = 0; i < kSize; i++) {
    for (unsigned int j = 0; j < kSize; j++) {
      expected[i * kSize + j] = 0.0;
      for (unsigned int k = 0; k < kSize; k++) {
        expected[i * kSize + j] += (a1[i * kSize + k] - a2[i * kSize + k]) *
                                   (b1[k * kSize + j] + b2[k * kSize + j]);
      }
    }
  }

  strassen4(kSize, a1.data(), a2.data(), b1.data(), b2.data(), result.data());

  ASSERT_EQ(expected, result);
}

TEST(Parallel, Matrix_8x8) {
  const unsigned int kSize = 8;
  std::vector<double> a(kSize * kSize);
  std::vector<double> b(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> resultExpected(kSize * kSize);

  for (unsigned int i = 0; i < kSize * kSize; i++) {
    a[i] = i + 1;
    b[i] = kSize * kSize - i;
  }
  multSeq(kSize, a.data(), b.data(), resultExpected.data());

  strassenMultOmp(kSize, a.data(), b.data(), result.data());

  ASSERT_EQ(resultExpected, result);
}

TEST(Parallel, Matrix_16x16) {
  const unsigned int kSize = 16;
  std::vector<double> a(kSize * kSize);
  std::vector<double> b(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> resultExpected(kSize * kSize);

  for (unsigned int i = 0; i < kSize * kSize; i++) {
    a[i] = i + 1;
    b[i] = kSize * kSize - i;
  }
  multSeq(kSize, a.data(), b.data(), resultExpected.data());

  strassenMultOmp(kSize, a.data(), b.data(), result.data());

  ASSERT_EQ(resultExpected, result);
}

TEST(Parallel, Matrix_32x32) {
  const unsigned int kSize = 32;
  std::vector<double> a(kSize * kSize);
  std::vector<double> b(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> resultExpected(kSize * kSize);

  for (unsigned int i = 0; i < kSize * kSize; i++) {
    a[i] = i + 1;
    b[i] = kSize * kSize - i;
  }
  multSeq(kSize, a.data(), b.data(), resultExpected.data());

  strassenMultOmp(kSize, a.data(), b.data(), result.data());

  ASSERT_EQ(resultExpected, result);
}

TEST(Parallel, Matrix_64x64) {
  const unsigned int kSize = 64;
  std::vector<double> a(kSize * kSize);
  std::vector<double> b(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> resultExpected(kSize * kSize);

  for (unsigned int i = 0; i < kSize * kSize; i++) {
    a[i] = i + 1;
    b[i] = kSize * kSize - i;
  }
  multSeq(kSize, a.data(), b.data(), resultExpected.data());

  strassenMultOmp(kSize, a.data(), b.data(), result.data());

  ASSERT_EQ(resultExpected, result);
}

TEST(Parallel, Matrix_128x128) {
  const unsigned int kSize = 128;
  std::vector<double> a(kSize * kSize);
  std::vector<double> b(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> resultExpected(kSize * kSize);

  for (unsigned int i = 0; i < kSize * kSize; i++) {
    a[i] = i + 1;
    b[i] = kSize * kSize - i;
  }
  multSeq(kSize, a.data(), b.data(), resultExpected.data());

  strassenMultOmp(kSize, a.data(), b.data(), result.data());

  ASSERT_EQ(resultExpected, result);
}

TEST(Parallel, Matrix_256x256) {
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

  strassenMultOmp(kSize, a.data(), b.data(), result.data());

  ASSERT_EQ(resultExpected, result);
}

TEST(Parallel, DISABLED_Matrix_512x512) {
  const unsigned int kSize = 512;
  std::vector<double> a(kSize * kSize);
  std::vector<double> b(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> resultExpected(kSize * kSize);

  for (unsigned int i = 0; i < kSize * kSize; i++) {
    a[i] = i + 1;
    b[i] = kSize * kSize - i;
  }

  double start = omp_get_wtime();
  multSeq(kSize, a.data(), b.data(), resultExpected.data());
  double end = omp_get_wtime();

  double seqTime = end - start;
  std::cout << "Sequential: " << seqTime << std::endl;

  start = omp_get_wtime();
  strassenMultOmp(kSize, a.data(), b.data(), result.data());
  end = omp_get_wtime();

  double parTime = end - start;
  std::cout << "Parallel: " << parTime << std::endl;

  std::cout << "x" << static_cast<double>(seqTime) / parTime << " faster"
            << std::endl;

  ASSERT_EQ(resultExpected, result);
}

TEST(Parallel, DISABLED_Matrix_1024x1024) {
  const unsigned int kSize = 1024;
  std::vector<double> a(kSize * kSize);
  std::vector<double> b(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> resultExpected(kSize * kSize);

  for (unsigned int i = 0; i < kSize * kSize; i++) {
    a[i] = i + 1;
    b[i] = kSize * kSize - i;
  }

  double start, end;

  start = omp_get_wtime();
  multSeq(kSize, a.data(), b.data(), resultExpected.data());
  end = omp_get_wtime();

  double seqTime = end - start;
  std::cout << "Sequential: " << seqTime << std::endl;

  start = omp_get_wtime();
  strassenMultOmp(kSize, a.data(), b.data(), result.data());
  end = omp_get_wtime();

  double parTime = end - start;
  std::cout << "Parallel: " << parTime << std::endl;

  std::cout << "x" << static_cast<double>(seqTime) / parTime << " faster"
            << std::endl;

  ASSERT_EQ(resultExpected, result);
}

TEST(Parallel, DISABLED_Matrix_2048x2048) {
  const unsigned int kSize = 2048;
  std::vector<double> a(kSize * kSize);
  std::vector<double> b(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> resultExpected(kSize * kSize);

  for (unsigned int i = 0; i < kSize * kSize; i++) {
    a[i] = i + 1;
    b[i] = kSize * kSize - i;
  }

  double start, end;

  start = omp_get_wtime();
  multSeq(kSize, a.data(), b.data(), resultExpected.data());
  end = omp_get_wtime();

  double seqTime = end - start;
  std::cout << "Sequential: " << seqTime << std::endl;

  start = omp_get_wtime();
  strassenMultOmp(kSize, a.data(), b.data(), result.data());
  end = omp_get_wtime();

  double parTime = end - start;
  std::cout << "Parallel: " << parTime << std::endl;

  std::cout << "x" << static_cast<double>(seqTime) / parTime << " faster"
            << std::endl;

  for (unsigned int i = 0; i < 2048 * 2048; i++) {
    ASSERT_NEAR(resultExpected[i], result[i], resultExpected[i] * 0.000000001);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

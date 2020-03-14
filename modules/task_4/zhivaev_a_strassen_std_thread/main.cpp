// Copyright 2020 Zhivaev Artem

#include <gtest/gtest.h>

#include <chrono>
#include <iostream>
#include <vector>

#include "./strassen_std_thread.h"

const double EPSILON = 0.0000001;

void multSeq(int size, const double* a, const double* b, double* result);

TEST(Parallel, Matrix_8x8) {
  const int kSize = 8;
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

TEST(Parallel, Matrix_16x16) {
  const int kSize = 16;
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

TEST(Parallel, Matrix_32x32) {
  const int kSize = 32;
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

TEST(Parallel, Matrix_128x128) {
  const int kSize = 128;
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

TEST(Parallel, Matrix_256x256) {
  const int kSize = 256;
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

TEST(Parallel, DISABLED_Matrix_512x512) {
  const int kSize = 512;
  std::vector<double> a(kSize * kSize);
  std::vector<double> b(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> expected(kSize * kSize);

  for (int i = 0; i < kSize * kSize; i++) {
    a[i] = i + 1;
    b[i] = kSize * kSize - i;
  }

  auto start = std::chrono::high_resolution_clock::now();
  multSeq(kSize, a.data(), b.data(), expected.data());
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsedSeq = end - start;
  std::cout << "Size: " << kSize << std::endl
            << "\tSequential: " << elapsedSeq.count() << std::endl;

  start = std::chrono::high_resolution_clock::now();
  strassenMultStdThread(kSize, a.data(), b.data(), result.data());
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsedPar = end - start;
  std::cout << "\tParallel: " << elapsedPar.count() << std::endl
            << "\tx" << (elapsedSeq.count() / elapsedPar.count()) << " faster"
            << std::endl;

  for (int i = 0; i < kSize * kSize; i++) {
    ASSERT_NEAR(expected[i], result[i], expected[i] * EPSILON);
  }
}

TEST(Parallel, DISABLED_Matrix_1024x1024) {
  const int kSize = 1024;
  std::vector<double> a(kSize * kSize);
  std::vector<double> b(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> expected(kSize * kSize);

  for (int i = 0; i < kSize * kSize; i++) {
    a[i] = i + 1;
    b[i] = kSize * kSize - i;
  }

  auto start = std::chrono::high_resolution_clock::now();
  multSeq(kSize, a.data(), b.data(), expected.data());
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsedSeq = end - start;
  std::cout << "Size: " << kSize << std::endl
            << "\tSequential: " << elapsedSeq.count() << std::endl;

  start = std::chrono::high_resolution_clock::now();
  strassenMultStdThread(kSize, a.data(), b.data(), result.data());
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsedPar = end - start;
  std::cout << "\tParallel: " << elapsedPar.count() << std::endl
            << "\tx" << (elapsedSeq.count() / elapsedPar.count()) << " faster"
            << std::endl;

  for (int i = 0; i < kSize * kSize; i++) {
    ASSERT_NEAR(expected[i], result[i], expected[i] * EPSILON);
  }
}

TEST(Parallel, DISABLED_Matrix_2048x2048) {
  const int kSize = 2048;
  std::vector<double> a(kSize * kSize);
  std::vector<double> b(kSize * kSize);
  std::vector<double> result(kSize * kSize);
  std::vector<double> expected(kSize * kSize);

  for (int i = 0; i < kSize * kSize; i++) {
    a[i] = i + 1;
    b[i] = kSize * kSize - i;
  }

  auto start = std::chrono::high_resolution_clock::now();
  multSeq(kSize, a.data(), b.data(), expected.data());
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsedSeq = end - start;
  std::cout << "Size: " << kSize << std::endl
            << "\tSequential: " << elapsedSeq.count() << std::endl;

  start = std::chrono::high_resolution_clock::now();
  strassenMultStdThread(kSize, a.data(), b.data(), result.data());
  end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsedPar = end - start;
  std::cout << "\tParallel: " << elapsedPar.count() << std::endl
            << "\tx" << (elapsedSeq.count() / elapsedPar.count()) << " faster"
            << std::endl;

  for (int i = 0; i < kSize * kSize; i++) {
    ASSERT_NEAR(expected[i], result[i], expected[i] * EPSILON);
  }
}

// Copyright 2020 Zhivaev Artem

#include "../../../modules/task_2/zhivaev_a_strassen_mult_openmp/strassen_mult_openmp.h"

#include <omp.h>

#include <bitset>
#include <sstream>
#include <stdexcept>
#include <string>

void multSeq(unsigned int side, const double* a, const double* b,
             double* result) {
  for (unsigned int i = 0; i < side; i++) {
    for (unsigned int j = 0; j < side; j++) {
      result[i * side + j] = 0.0;
      for (unsigned int k = 0; k < side; k++) {
        result[i * side + j] += a[i * side + k] * b[k * side + j];
      }
    }
  }
}

int powerOf2(unsigned int number) {
  std::bitset<sizeof(unsigned int) * 8> bitset(number);
  if (bitset.count() != 1) {
    return -1;
  }
  std::string bitString = bitset.to_string();
  for (unsigned int i = 0; i < bitString.size(); i++) {
    if (bitString.at(bitString.size() - 1 - i) == '1') {
      return i;
    }
  }
  return -1;
}

void splitMatrix(unsigned int size, const double* a, double* a11, double* a12,
                 double* a21, double* a22) {
  unsigned int fSize = size / 2;
  for (unsigned int i = 0; i < fSize; i++) {
    for (unsigned int j = 0; j < fSize; j++) {
      a11[i * fSize + j] = a[i * size + j];
      a12[i * fSize + j] = a[i * size + fSize + j];
      a21[i * fSize + j] = a[(fSize + i) * size + j];
      a22[i * fSize + j] = a[(fSize + i) * size + fSize + j];
    }
  }
}

void assembleMatrix(unsigned int size, double* a, const double* a11,
                    const double* a12, const double* a21, const double* a22) {
  unsigned int fSize = size / 2;
  for (unsigned int i = 0; i < fSize; i++) {
    for (unsigned int j = 0; j < fSize; j++) {
      a[i * size + j] = a11[i * fSize + j];
      a[i * size + fSize + j] = a12[i * fSize + j];
      a[(fSize + i) * size + j] = a21[i * fSize + j];
      a[(fSize + i) * size + fSize + j] = a22[i * fSize + j];
    }
  }
}

void matrixSum(unsigned int side, const double* a, const double* b, double* c) {
  for (unsigned int i = 0; i < side * side; i++) {
    c[i] = a[i] + b[i];
  }
}

void matrixSub(unsigned int side, const double* a, const double* b, double* c) {
  for (unsigned int i = 0; i < side * side; i++) {
    c[i] = a[i] - b[i];
  }
}

void strassenMultOmp(unsigned int size, const double* a, const double* b,
                     double* result) {
  if (powerOf2(size) < 0) {
    std::ostringstream stringStream;
    stringStream << "Size " << size << " is not power of 2";
    throw std::invalid_argument(stringStream.str());
  }
  if (size <= 32) {
    multSeq(size, a, b, result);
    return;
  }
  double* a11 = new double[size * size * 2];
  double* a12 = a11 + size * size / 4;
  double* a21 = a12 + size * size / 4;
  double* a22 = a21 + size * size / 4;

  double* b11 = a22 + size * size / 4;
  double* b12 = b11 + size * size / 4;
  double* b21 = b12 + size * size / 4;
  double* b22 = b21 + size * size / 4;

  double* c11 = new double[size * size + (size * size / 4) * 9];
  double* c12 = c11 + size * size / 4;
  double* c21 = c12 + size * size / 4;
  double* c22 = c21 + size * size / 4;

  double* m1 = c22 + size * size / 4;
  double* m2 = m1 + size * size / 4;
  double* m3 = m2 + size * size / 4;
  double* m4 = m3 + size * size / 4;
  double* m5 = m4 + size * size / 4;
  double* m6 = m5 + size * size / 4;
  double* m7 = m6 + size * size / 4;

  double* t1 = m7 + size * size / 4;
  double* t2 = t1 + size * size / 4;

  double* m1t1 = new double[(size * size / 4) * 10];
  double* m1t2 = m1t1 + size * size / 4;
  double* m2t1 = m1t2 + size * size / 4;
  double* m3t2 = m2t1 + size * size / 4;
  double* m4t2 = m3t2 + size * size / 4;
  double* m5t1 = m4t2 + size * size / 4;
  double* m6t1 = m5t1 + size * size / 4;
  double* m6t2 = m6t1 + size * size / 4;
  double* m7t1 = m6t2 + size * size / 4;
  double* m7t2 = m7t1 + size * size / 4;

  splitMatrix(size, a, a11, a12, a21, a22);
  splitMatrix(size, b, b11, b12, b21, b22);

// M1 = (A11 + A22)(B11 + B22)
#pragma omp task
  {
    matrixSum(size / 2, a11, a22, m1t1);
    matrixSum(size / 2, b11, b22, m1t2);
    strassenMultOmp(size / 2, m1t1, m1t2, m1);
  }

// M2 = (A21 + A22)B11
#pragma omp task
  {
    matrixSum(size / 2, a21, a22, m2t1);
    strassenMultOmp(size / 2, m2t1, b11, m2);
  }

// M3 = A11(B12 - B22)
#pragma omp task
  {
    matrixSub(size / 2, b12, b22, m3t2);
    strassenMultOmp(size / 2, a11, m3t2, m3);
  }

// M4 = A22(B21 - B11)
#pragma omp task
  {
    matrixSub(size / 2, b21, b11, m4t2);
    strassenMultOmp(size / 2, a22, m4t2, m4);
  }

// M5 = (A11 + A12) B22
#pragma omp task
  {
    matrixSum(size / 2, a11, a12, m5t1);
    strassenMultOmp(size / 2, m5t1, b22, m5);
  }

// M6 = (A21 - A11)(B11 + B12)
#pragma omp task
  {
    matrixSub(size / 2, a21, a11, m6t1);
    matrixSum(size / 2, b11, b12, m6t2);
    strassenMultOmp(size / 2, m6t1, m6t2, m6);
  }

// M7 = (A12 - A22)(B21 + B22)
#pragma omp task
  {
    matrixSub(size / 2, a12, a22, m7t1);
    matrixSum(size / 2, b21, b22, m7t2);
    strassenMultOmp(size / 2, m7t1, m7t2, m7);
  }

#pragma omp taskwait

  // C11 = M1 + M4 - M5 + M7
  matrixSum(size / 2, m1, m4, t1);
  matrixSub(size / 2, t1, m5, t2);
  matrixSum(size / 2, t2, m7, c11);

  // C12 = M3 + M5
  matrixSum(size / 2, m3, m5, c12);

  // C21 = M2 + M4
  matrixSum(size / 2, m2, m4, c21);

  // C22 = M1 - M2 + M3 + M6
  matrixSub(size / 2, m1, m2, t1);
  matrixSum(size / 2, t1, m3, t2);
  matrixSum(size / 2, t2, m6, c22);

  assembleMatrix(size, result, c11, c12, c21, c22);

  delete[] a11;
  delete[] c11;
  delete[] m1t1;
}

void strassenMult(unsigned int size, const double* a, const double* b,
                  double* result) {
#pragma omp parallel
  {
#pragma omp single
    { strassenMultOmp(size, a, b, result); }
  }
}

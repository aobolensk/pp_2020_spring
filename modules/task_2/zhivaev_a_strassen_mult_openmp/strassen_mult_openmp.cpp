// Copyright 2020 Zhivaev Artem

#include "../../../modules/task_2/zhivaev_a_strassen_mult_openmp/strassen_mult_openmp.h"

#include <bitset>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

void strassenMultRecursive(unsigned int size, const double* a, const double* b,
                           double* result);

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

// (A1 + A2)(B1 + B2)
void strassen1(unsigned int size, const double* a1, const double* a2,
               const double* b1, const double* b2, double* result) {
  double* t1 = new double[size * size * 2];
  double* t2 = t1 + size * size;
  int i;
  int length = size * size;

  for (i = 0; i < length; i++) {
    t1[i] = a1[i] + a2[i];
    t2[i] = b1[i] + b2[i];
  }

  multSeq(size, t1, t2, result);

  delete[] t1;
}

// (A1 + A2)B
void strassen2(unsigned int size, const double* a1, const double* a2,
               const double* b, double* result) {
  double* t = new double[size * size];
  int i;
  int length = size * size;

  for (i = 0; i < length; i++) {
    t[i] = a1[i] + a2[i];
  }

  multSeq(size, t, b, result);

  delete[] t;
}

// A(B1 - B2)
void strassen3(unsigned int size, const double* a, const double* b1,
               const double* b2, double* result) {
  double* t = new double[size * size];
  int i;
  int length = size * size;

  for (i = 0; i < length; i++) {
    t[i] = b1[i] - b2[i];
  }

  multSeq(size, a, t, result);

  delete[] t;
}

// (A1 - A2)(B1 + B2)
void strassen4(unsigned int size, const double* a1, const double* a2,
               const double* b1, const double* b2, double* result) {
  double* t1 = new double[size * size * 2];
  double* t2 = t1 + size * size;
  int i;
  int length = size * size;

  for (i = 0; i < length; i++) {
    t1[i] = a1[i] - a2[i];
    t2[i] = b1[i] + b2[i];
  }

  multSeq(size, t1, t2, result);

  delete[] t1;
}

void strassenMultRecursive(unsigned int size, const double* a, const double* b,
                           double* result) {
  if (size <= 32) {
    multSeq(size, a, b, result);
    return;
  }
  int i;
  int qLength = size * size / 4;
  double* a11 = new double[size * size];
  double* a12 = a11 + size * size / 4;
  double* a21 = a12 + size * size / 4;
  double* a22 = a21 + size * size / 4;
  double* b11 = new double[size * size];
  double* b12 = b11 + size * size / 4;
  double* b21 = b12 + size * size / 4;
  double* b22 = b21 + size * size / 4;
  double* c11 = new double[size * size];
  double* c12 = c11 + size * size / 4;
  double* c21 = c12 + size * size / 4;
  double* c22 = c21 + size * size / 4;

  double* m1 = new double[(size * size / 4) * 7];
  double* m2 = m1 + size * size / 4;
  double* m3 = m2 + size * size / 4;
  double* m4 = m3 + size * size / 4;
  double* m5 = m4 + size * size / 4;
  double* m6 = m5 + size * size / 4;
  double* m7 = m6 + size * size / 4;

  splitMatrix(size, a, a11, a12, a21, a22);
  splitMatrix(size, b, b11, b12, b21, b22);

#pragma omp parallel sections shared(a11, a12, a21, a22, b11, b12, b21, b22)
  {
// M1 = (A11 + A22)(B11 + B22)
#pragma omp section
    { strassen1(size / 2, a11, a22, b11, b22, m1); }

// M2 = (A21 + A22)B11
#pragma omp section
    { strassen2(size / 2, a21, a22, b11, m2); }

// M3 = A11(B12 - B22)
#pragma omp section
    { strassen3(size / 2, a11, b12, b22, m3); }

// M4 = A22(B21 - B11)
#pragma omp section
    { strassen3(size / 2, a22, b21, b11, m4); }

// M5 = (A11 + A12)B22
#pragma omp section
    { strassen2(size / 2, a11, a12, b22, m5); }

// M6 = (A21 - A11)(B11 + B12)
#pragma omp section
    { strassen4(size / 2, a21, a11, b11, b12, m6); }

// M7 = (A12 - A22)(B21 + B22)
#pragma omp section
    { strassen4(size / 2, a12, a22, b21, b22, m7); }
  }

// C11 = M1 + M4 - M5 + M7
  for (i = 0; i < qLength; i++) {
    c11[i] = m1[i] + m4[i] - m5[i] + m7[i];
  }

// C12 = M3 + M5
  for (i = 0; i < qLength; i++) {
    c12[i] = m3[i] + m5[i];
  }

// C21 = M2 + M4
  for (i = 0; i < qLength; i++) {
    c21[i] = m2[i] + m4[i];
  }

// C22 = M1 - M2 + M3 + M6
  for (i = 0; i < qLength; i++) {
    c22[i] = m1[i] - m2[i] + m3[i] + m6[i];
  }

  assembleMatrix(size, result, c11, c12, c21, c22);

  delete[] a11;
  delete[] b11;
  delete[] c11;
  delete[] m1;
}

unsigned int nextPowerOf2(unsigned int number) {
  if (powerOf2(number) != -1) {
    return number;
  }
  std::bitset<sizeof(unsigned int) * 8> bits(number);
  for (unsigned int i = static_cast<unsigned int>(bits.size() - 1); i != 0;
       i--) {
    if (bits.test(i - 1)) {
      bits.reset();
      bits.set(i);
      return static_cast<unsigned int>(bits.to_ulong());
    }
  }
  return 0;
}

void strassenMultOmp(unsigned int size, const double* a, const double* b,
                     double* result) {
  if (powerOf2(size) < 0) {
    std::ostringstream stringStream;
    stringStream << "Size " << size << " is not power of 2";
    throw std::invalid_argument(stringStream.str());
  }
  strassenMultRecursive(size, a, b, result);
}

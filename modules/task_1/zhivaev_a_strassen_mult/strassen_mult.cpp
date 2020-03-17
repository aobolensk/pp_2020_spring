// Copyright 2020 Zhivaev Artem

#include "../../modules/task_1/zhivaev_a_strassen_mult/strassen_mult.h"

#include <bitset>
#include <cstdlib>
#include <sstream>
#include <climits>
#include <stdexcept>
#include <string>

void strassenMultSeq(unsigned int side, const double* a, const double* b,
                     double* result) {
  if (powerOf2(side) < 0) {
    std::ostringstream stringStream;
    stringStream << "Size " << side << " is not power of 2";
    throw std::invalid_argument(stringStream.str());
  }
  if (side <= 32) {
    multSeq(side, a, b, result);
    return;
  }
  double* a11 = new double[side * side * 2];
  double* a12 = a11 + side * side / 4;
  double* a21 = a12 + side * side / 4;
  double* a22 = a21 + side * side / 4;

  double* b11 = a22 + side * side / 4;
  double* b12 = b11 + side * side / 4;
  double* b21 = b12 + side * side / 4;
  double* b22 = b21 + side * side / 4;

  double* c11 = new double[side * side + (side * side / 4) * 9];
  double* c12 = c11 + side * side / 4;
  double* c21 = c12 + side * side / 4;
  double* c22 = c21 + side * side / 4;

  double* m1 = c22 + side * side / 4;
  double* m2 = m1 + side * side / 4;
  double* m3 = m2 + side * side / 4;
  double* m4 = m3 + side * side / 4;
  double* m5 = m4 + side * side / 4;
  double* m6 = m5 + side * side / 4;
  double* m7 = m6 + side * side / 4;

  double* t1 = m7 + side * side / 4;
  double* t2 = t1 + side * side / 4;

  splitMatrix(side, a, a11, a12, a21, a22);
  splitMatrix(side, b, b11, b12, b21, b22);

  // M1 = (A11 + A22)(B11 + B22)
  matrixSum(side / 2, a11, a22, t1);
  matrixSum(side / 2, b11, b22, t2);
  strassenMultSeq(side / 2, t1, t2, m1);

  // M2 = (A21 + A22)B11
  matrixSum(side / 2, a21, a22, t1);
  strassenMultSeq(side / 2, t1, b11, m2);

  // M3 = A11(B12 - B22)
  matrixSub(side / 2, b12, b22, t1);
  strassenMultSeq(side / 2, a11, t1, m3);

  // M4 = A22(B21 - B11)
  matrixSub(side / 2, b21, b11, t1);
  strassenMultSeq(side / 2, a22, t1, m4);

  // M5 = (A11 + A12)B22
  matrixSum(side / 2, a11, a12, t1);
  strassenMultSeq(side / 2, t1, b22, m5);

  // M6 = (A21 - A11)(B11 + B12)
  matrixSub(side / 2, a21, a11, t1);
  matrixSum(side / 2, b11, b12, t2);
  strassenMultSeq(side / 2, t1, t2, m6);

  // M7 = (A12 - A22)(B21 + B22)
  matrixSub(side / 2, a12, a22, t1);
  matrixSum(side / 2, b21, b22, t2);
  strassenMultSeq(side / 2, t1, t2, m7);

  // C11 = M1 + M4 - M5 + M7
  matrixSum(side / 2, m1, m4, t1);
  matrixSub(side / 2, t1, m5, t2);
  matrixSum(side / 2, t2, m7, c11);

  // C12 = M3 + M5
  matrixSum(side / 2, m3, m5, c12);

  // C21 = M2 + M4
  matrixSum(side / 2, m2, m4, c21);

  // C22 = M1 - M2 + M3 + M6
  matrixSub(side / 2, m1, m2, t1);
  matrixSum(side / 2, t1, m3, t2);
  matrixSum(side / 2, t2, m6, c22);

  assembleMatrix(side, result, c11, c12, c21, c22);

  delete[] a11;
  delete[] c11;
}

void multSeq(unsigned int side, const double* a, const double* b, double* result) {
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

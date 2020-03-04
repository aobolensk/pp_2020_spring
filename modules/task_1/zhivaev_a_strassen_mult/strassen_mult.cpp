// Copyright 2020 Zhivaev Artem

#include "../../modules/task_1/zhivaev_a_strassen_mult/strassen_mult.h"

#include <bitset>
#include <climits>
#include <sstream>
#include <stdexcept>

void strassenMultSeq(size_t side, const double* a, const double* b,
                     double* result) {
  if (powerOf2(side) == -1) {
    std::ostringstream stringStream;
    stringStream << "Size " << side << " is not power of 2";
    throw std::invalid_argument(stringStream.str());
  }
   multSeq(side, a, b, result);
}

void multSeq(size_t side, const double* a, const double* b, double* result) {
  for (size_t i = 0; i < side; i++) {
    for (size_t j = 0; j < side; j++) {
      result[i * side + j] = 0.0;
      for (size_t k = 0; k < side; k++) {
        result[i * side + j] += a[i * side + k] * b[k * side + j];
      }
    }
  }
}

int powerOf2(size_t number) {
  size_t b = 1;
  int pow = 0;
  std::bitset<sizeof(size_t) * CHAR_BIT> bitset(number);
  bitset.count();
  if (bitset.count() != 1) {
    return -1;
  }
  std::string bitString = bitset.to_string();
  for (size_t i = 0; i < bitString.size(); i++) {
    if (bitString.at(bitString.size() - 1 - i) == '1') {
      return i;
    }
  }
}

void splitMatrix(size_t size, const double* a, double* a11, double* a12,
                 double* a21, double* a22) {
  size_t fSize = size / 2;
  for (int i = 0; i < fSize; i++) {
    for (int j = 0; j < fSize; j++) {
      a11[i * fSize + j] = a[i * size + j];
      a12[i * fSize + j] = a[i * size + fSize + j];
      a21[i * fSize + j] = a[(fSize + i) * size + j];
      a22[i * fSize + j] = a[(fSize + i) * size + fSize + j];
    }
  }
}

void assembleMatrix(size_t size, double* a, const double* a11,
  const double* a12, const double* a21, const double* a22) {
  size_t fSize = size / 2;
  for (int i = 0; i < fSize; i++) {
    for (int j = 0; j < fSize; j++) {
      a[i * size + j] = a11[i * fSize + j];
      a[i * size + fSize + j] = a12[i * fSize + j];
      a[(fSize + i) * size + j] = a21[i * fSize + j];
      a[(fSize + i) * size + fSize + j] = a22[i * fSize + j];
    }
  }
}

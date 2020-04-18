// Copyright 2020 Golubeva Anna

#include <random>
#include <iostream>
#include <algorithm>
#include <vector>
#include "../../../modules/task_1/golubeva_a_fox_mult/fox.h"

Matrix simpleMult(const Matrix& A, const Matrix& B) {
    if (A[0].size() != B.size())
        throw "Different size";
    int n = A.size();
    int m = B[0].size();
    Matrix C(n, std::vector<double>(n, 0));
    int size = B.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int t = 0; t < size; t++) {
                C[i][j] += A[i][t]*B[t][j];
            }
        }
    }
    return C;
}

Matrix foxMult(const Matrix& A, const Matrix& B, const int &blockSize) {
    if (A[0].size() != B.size())
        throw "Different size";
    int n = A.size();
    if (blockSize > n)
      throw "block size is larger than matrix size";
    Matrix C(n, std::vector<double>(n, 0));
    int endA, endB;
    for (int a = 0; a < n; a+=blockSize) {
      endA = std::min(a + blockSize, n);
        for (int b = 0; b < n; b+=blockSize) {
          endB = std::min(b + blockSize, n);
            for (int i = 0; i < n; i++) {
              for (int j = a; j < endA; j++) {
                for (int k = b; k < endB; k++) {
                  C[i][j] += A[i][k] * B[k][j];
                    }
                }
            }
        }
    }

  return C;
}


Matrix randMatrix(const int& size) {
  if (size <= 0) {
    throw "Wrong size matrix";
  }
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0, 1000.0);
  Matrix matr(size, std::vector<double>(size));
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      matr[i][j] = dis(gen);
    }
  }
  return matr;
}

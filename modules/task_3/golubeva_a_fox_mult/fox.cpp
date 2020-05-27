// Copyright 2020 Golubeva Anna
#include "../../../modules/task_3/golubeva_a_fox_mult/fox.h"
#include <omp.h>
#include <tbb/tbb.h>
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>

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

bool isSquare(const Matrix &A) {
    if (A.size()!= A[0].size())
      return false;
    return true;
}


bool canBeMultiplied(const Matrix &A, const Matrix &B) {
        if (A[0].size() != B.size())
          return false;
    return true;
}

Matrix foxMult(const Matrix& A, const Matrix& B) {
    if (!isSquare(A) || !isSquare(B))
      throw("Matrix isn't square");
    if (!canBeMultiplied(A, B))
      throw("Different number of rows and columns");

    tbb::task_scheduler_init init;
    auto numThreads = init.default_num_threads();

    int n = A.size();
    int q = std::sqrt(numThreads);
    int blockSize;
    int nOld = n;
    Matrix A2 = A;
    Matrix B2 = B;

    while (n%q != 0) {
        A2.push_back(std::vector<double>(n, 0));
        B2.push_back(std::vector<double>(n, 0));
        n++;
    }
    for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n - nOld; ++j) {
                A2[i].push_back(0);
                B2[i].push_back(0);
            }
        }

    Matrix res(n, std::vector<double>(n));
    blockSize = n / q;

    tbb::parallel_for(tbb::blocked_range2d<size_t>(0, n, blockSize, 0, n, blockSize),
                        [&](const tbb::blocked_range2d<size_t>& r){
        int i_thread = r.rows().begin() / blockSize;
        int j_thread = r.cols().begin() / blockSize;
        int h1 = i_thread * blockSize;
        int h2 = j_thread * blockSize;

        Matrix blockA(blockSize), blockB(blockSize);
        Matrix blockC(blockSize, std::vector<double>(blockSize, 0));

        for (int z = 0; z < q; ++z) {
            int s = ((i_thread+z) % q)* blockSize;
            for (int k = 0; k < blockSize; ++k) {
                blockA[k] = std::vector<double>(A2[h1+k].begin()+s, A2[h1+k].begin()+ s + blockSize);
                blockB[k] = std::vector<double>(B2[s+k].begin()+h2, B2[s+k].begin()+(h2+blockSize));
            }
            for (int i = 0; i < blockSize; i++) {
                for (int j = 0; j < blockSize; j++) {
                    for (int t = 0; t < blockSize; t++)
                    blockC[i][j] += blockA[i][t]*blockB[t][j];
                }
            }
        }

        for (int i = 0; i < blockSize; i++) {
            for (int j = 0; j < blockSize; j++) {
                res[i+h1][j+h2] = blockC[i][j];
            }
        }
    });

    if (nOld != n) {
        tbb::parallel_for(tbb::blocked_range<size_t>(0, n), [&](const tbb::blocked_range<size_t>& r) {
            for (auto j = r.begin(); j < r.end(); j++) {
                res[j].resize(nOld);
            }
        });
    }
    res.resize(nOld);
    return res;
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



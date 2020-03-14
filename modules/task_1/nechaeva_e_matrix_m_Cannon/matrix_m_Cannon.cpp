// Copyright 2020 Nechaeva Ekaterina

#include <random>
#include <iostream>
#include <algorithm>
#include <exception>
#include <vector>
#include "../../../modules/task_1/nechaeva_e_matrix_m_Cannon/matrix_m_Cannon.h"

matrix RandomMatrix(const int n) {
    if (n <= 0)
        throw std::invalid_argument("Negative size");

    std::mt19937 generator;
    std::random_device device;
    generator.seed(device());
    std::uniform_real_distribution<double> distribution(0, 100);;

    matrix rez(n, std::vector<double>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            rez[i][j] = distribution(generator);

    return rez;
}

matrix NaiveMulti(const matrix &A, const matrix &B) {
    if (A[0].size() != B.size())
        throw std::invalid_argument("Different values for col and row");

    size_t n = A[0].size();
    size_t m = A.size();
    size_t l = B[0].size();
    matrix rez(m, std::vector<double>(l, 0));

    for (size_t i = 0; i < m; i++)
        for (size_t j = 0; j < l; j++)
            for (size_t k = 0; k < n; k++)
                rez[i][j] += A[i][k]*B[k][j];

    return rez;
}

bool CompareValues(const double &a, const double &b) {
    return std::fabs(a - b) < 0.00001;
}

bool CompareMatrix(const matrix &A, const matrix &B) {
    if (A[0].size() != B[0].size() || A.size() != B.size())
        return false;

    bool temp = true;
    for (size_t i = 0; i < A.size(); i++) {
        if (temp == false)
            break;
        for (size_t j = 0; j < A[0].size(); j++)
            if (!CompareValues(A[i][j], B[i][j])) {
                temp = false;
                break;
            }
    }

    return temp;
}

matrix BlockMulti(const matrix &A, const matrix &B, const int &blockSize) {
    if (A[0].size() != B.size())
        throw std::invalid_argument("Different values for col and row");
    int temp = blockSize;
    if (temp > static_cast<int>(A.size()))
        throw std::invalid_argument("Wrong blockSize");

    int n = A[0].size();
    int jjMin, kkMin;
    matrix rez(n, std::vector<double>(n, 0));

    for (int jj = 0; jj < n; jj += blockSize) {
        jjMin = std::min(jj + blockSize, n);
       for (int kk = 0; kk < n; kk += blockSize) {
           kkMin = std::min(kk+ blockSize, n);
           for (int i = 0; i < n; i++) {
               for (int k = kk; k < kkMin; k++) {
                   for (int j = jj; j < jjMin; j++) {
                      rez[i][j]  +=  A[i][k] * B[k][j];
                   }
                }
            }
        }
    }

    return rez;
}

// Copyright 2020 Isaev Ilya

#include <random>
#include <iostream>
#include <exception>
#include "matrix_mult.h"

Matrix getRandomMatrix(const int& n) {
    if (n <= 0) {
        throw std::exception();
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 100);
    
    Matrix res(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            res[i][j] = dis(gen);
        }
    }
    return res;
}

Matrix naiveMultiplication(const Matrix& mat1, const Matrix& mat2) {
    if (mat1[0].size() != mat2.size())
        throw std::exception();
    
    size_t n = mat1.size();
    size_t m = mat2[0].size();
    Matrix res(n, std::vector<double>(n, 0));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            for (size_t k = 0; k < mat2.size(); ++k) {
                res[i][j] += mat1[i][k]*mat2[k][j];
            }
        }
    }
    return res;
}

Matrix foxMultiplication(const Matrix& mat1, const Matrix& mat2) {
    if (!isSquared(mat1) || !isSquared(mat2) || mat1.size() != mat2.size())
        throw std::exception();

    size_t n = mat1.size();
    Matrix res(n, std::vector<double>(n, 0));
    return res;
}

bool matrixComparison(const Matrix& mat1, const Matrix& mat2) {
    if (mat1.size() != mat2.size() || mat1[0].size() != mat2[0].size())
        throw std::exception();
    bool isequal = true;
    for (size_t i = 0; i < mat1.size(); ++i) {
        for (size_t j = 0; j < mat1[0].size(); ++j)
            if (!doubleComparison(mat1[i][j], mat2[i][j]))
                isequal = false;
    }
    return isequal;
};

bool doubleComparison(const double& a, const double& b) {
    return std::abs(a-b) <= std::numeric_limits<double>::epsilon()*std::max(std::abs(a),std::abs(b));
}

bool isSquared(const Matrix& mat) {
    return mat.size() == mat[0].size();
}
// Copyright 2020 Isaev Ilya

#include <random>
#include <iostream>
#include <exception>
#include "matrix_mult.h"

std::vector<std::vector<double> > getRandomMatrix(const int& n, const int& m) {
    if (n <= 0 || m <= 0) {
        throw std::exception();
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 100);
    
    std::vector<std::vector<double> > res(n, std::vector<double>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            res[i][j] = dis(gen);
        }
    }
    return res;
}

std::vector<std::vector<double> > operator*(const std::vector<std::vector<double> >& mat1, const std::vector<std::vector<double> >& mat2) {
    if (mat1.size() != mat2[0].size())
        throw std::exception();
    
    int n = static_cast<int>(mat1.size());
    int m = static_cast<int>(mat2[0].size());
    std::vector<std::vector<double> > res(n, std::vector<double>(m, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < n; ++k) {
                res[i][j] += mat1[i][k]*mat2[k][j];
            }
        }
    }
    return res;
}

bool matrixComparison(const std::vector<std::vector<double> >& mat1, const std::vector<std::vector<double> >& mat2) {
    bool isequal = true;
    int n = static_cast<int>(mat1.size());
    if (n != static_cast<int>(mat2.size()) || n != static_cast<int>(mat1[0].size()))
        throw std::exception();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            if (!doubleComparison(mat1[i][j], mat2[i][j]))
                isequal = false;
    }
    return isequal;
};

bool doubleComparison(const double& a, const double& b) {
    return std::abs(a-b) <= std::numeric_limits<double>::epsilon()*std::max(std::abs(a),std::abs(b));
}
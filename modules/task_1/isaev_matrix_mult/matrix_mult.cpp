// Copyright 2020 Isaev Ilya

#include <random>
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
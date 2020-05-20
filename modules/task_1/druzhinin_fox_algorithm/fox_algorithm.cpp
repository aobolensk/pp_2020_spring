// Copyright 2020 Druzhinin Alexei

#include "../../../modules/task_1/druzhinin_fox_algorithm/fox_algorithm.h"
#include <math.h>
#include <algorithm>
#include <limits>
#include <random>

void fillMatrix(double* a, const int size) {  // filling the matrix with random double values
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1000.0);
    for (int i = 0; i < size * size; i++)
        a[i] = dis(gen);
}

bool comparisonMatrixes(const double* a, const double* b, const int size) {  // comparison two matrixes
    for (int i = 0; i < size * size; i++) {
        if (std::fabs(a[i] - b[i]) > std::numeric_limits<double>::epsilon() * std::max(a[i], b[i]) * 100) {
            return false;
        }
    }
    return true;
}

void defaultMatrixMult(const double* a, const double* b, const int size, double* res) {  // default multiplication
    double tmp;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            tmp = 0;
            for (int k = 0; k < size; k++) {
                tmp += a[i * size + k] * b[k * size + j];
            }
            res[i * size + j] = tmp;
        }
    }
}


void blockMatrixMult(const double* a, const double* b, const int size, double* res) {  // blocked matrix multiplication
    int block_size = std::sqrt(size);
    for (int i = 0; i < size * size; i++)
        res[i] = 0;
    double tmp;
    for (int i = 0; i < size; i += block_size) {  // ijk cycle by blocks
        for (int j = 0; j < size; j += block_size) {
            for (int k = 0; k < size; k += block_size) {
                for (int ii = i; ii < std::min(size, i + block_size); ii++) {  // ijk cycle by elements
                    for (int jj = j; jj < std::min(size, j + block_size); jj++) {
                        tmp = 0;
                        for (int kk = k; kk < std::min(size, k + block_size); kk++) {
                            tmp += a[ii * size + kk] * b[kk * size + jj];
                        }
                        res[ii * size + jj] += tmp;
                    }
                }
            }
        }
    }
}

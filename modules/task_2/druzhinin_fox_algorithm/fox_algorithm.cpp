// Copyright 2020 Druzhinin Alexei

#include "../../../modules/task_2/druzhinin_fox_algorithm/fox_algorithm.h"
#include <math.h>
#include <omp.h>
#include <algorithm>
#include <limits>
#include <random>

void fillMatrix(double* a, const int size) {  // filling the matrix with random double values
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 100.0);
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

void foxAlgorithm(double *a, double *b, double *res, int n, int count_proc) {  // parallel version of Fox algorithm
    int q = std::sqrt(count_proc);
    #pragma omp parallel num_threads(q * q)
    {
        int counter;
        int procNum = omp_get_thread_num();
        int i1 = procNum / q;
        int j1 = procNum % q;
        double *a_tmp;
        double *b_tmp;
        double *res_tmp;
        for (counter = 0; counter < q; counter++) {
            a_tmp = a + (n * i1 + ((i1 + counter) % q)) * (n / q);
            b_tmp = b + (n * ((i1 + counter) % q) + j1) * (n / q);
            res_tmp = res + (n * i1 + j1) * (n / q);
            for (int i = 0; i < n / q; i++) {
                for (int j = 0; j < n / q; j++) {
                    for (int k = 0; k < n / q; k++) {
                        res_tmp[i * n + j] += a_tmp[i * n + k] * b_tmp[k * n + j];
                    }
                }
            }
        }
    }
}

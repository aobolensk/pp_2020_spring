// Copyright 2020 Iamshchikov Ivan
#include <omp.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include "../../modules/task_2/iamshchikov_i_sparse_matrix_mult/sparse_matrix_mult.h"

CcsMatrix::CcsMatrix(int _M, int _N, int nz) {
    if (_M <= 0 || _N <= 0) throw "wrong size";
    M = _M;
    N = _N;
    colIndex.resize(_N + 1);
    not_zero_number = nz;
    value.resize(nz);
    row.resize(nz);
}

double measurementOfTime(int M1, int N1, int N2, int num_threads) {
    if (M1 <= 0 || N1 <= 0 || N2 <= 0) throw "wrong size";
    if (num_threads <= 0) throw "wrong number of threads";

    double t1, t2;
    CcsMatrix m1(generateMatrix(M1, N1));
    CcsMatrix m2(generateMatrix(N1, N2));

    omp_set_num_threads(num_threads);
    t1 = omp_get_wtime();
    matrixMultiplicate(&m1, &m2);
    t2 = omp_get_wtime();

    return t2 - t1;
}

bool operator==(const CcsMatrix& m1, const CcsMatrix& m2) {
    return m1.value == m2.value && m1.row == m2.row &&
        m1.colIndex == m2.colIndex && m1.M == m2.M;
}

CcsMatrix generateMatrix(int M, int N) {
    if (M <= 0 || N <= 0) throw "wrong size";
    int nz = 0, nz_in_col = 0, tmp = 0;
    std::mt19937 gen;
    std::vector<int> row;
    gen.seed(static_cast<unsigned int>(time(0)));
    nz = gen() % static_cast<int>(sqrt(M*N));
    nz_in_col = (nz / N == 0) ? 1 : nz / N;

    CcsMatrix m(M, N, 0);
    m.not_zero_number = nz_in_col * N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < nz_in_col; j++) {
            m.value.push_back(gen() % static_cast<int>(M*N));
            tmp = gen() % static_cast<int>(M);
            while (std::find(row.begin(), row.end(), tmp) != row.end())
                tmp = gen() % static_cast<int>(M);
            m.row.push_back(tmp);
        }
        m.colIndex[i] = i * nz_in_col;
    }
    m.colIndex[N] = N * nz_in_col;
    return m;
}

CcsMatrix transposeMatrix(const CcsMatrix* m) {
    int i, j, k1, k2, iindex, rindex, row, tmp, s = 0;
    double v;
    CcsMatrix res(m->N, m->M, m->not_zero_number);

    for (i = 0; i < m->not_zero_number; i++)
        res.colIndex[m->row[i] + 1]++;

    for (i = 1; i <= m->M; i++) {
        tmp = res.colIndex[i];
        res.colIndex[i] = s;
        s += tmp;
    }

    for (i = 0; i < m->N; i++) {
        k1 = m->colIndex[i];
        k2 = m->colIndex[i + 1];
        row = i;
        for (j = k1; j < k2; j++) {
            v = m->value[j];
            rindex = m->row[j];
            iindex = res.colIndex[rindex + 1];
            res.value[iindex] = v;
            res.row[iindex] = row;
            res.colIndex[rindex + 1]++;
        }
    }
    return res;
}

double scalarMultiplication(const CcsMatrix* transposed_m, const CcsMatrix* m,
                            int i, int j) {
    double res = 0;
    int k = 0;
    for (k = transposed_m->colIndex[i]; k < transposed_m->colIndex[i+1]; k++)
        for (int l = m->colIndex[j]; l < m->colIndex[j+1]; l++)
            if (transposed_m->row[k] == m->row[l]) {
                res += transposed_m->value[k] * m->value[l];
                break;
            }
    return res;
}

CcsMatrix matrixMultiplicate(const CcsMatrix* m1, const CcsMatrix* m2) {
    if (m1->N != m2->M) throw "m1 and m2 are incompatible";
    CcsMatrix res(m1->M, m2->N, 0);
    CcsMatrix transposed_m1(transposeMatrix(m1));

    #pragma omp parallel if (m2->N > 1) shared(res, transposed_m1)
    {
        int colNZ = 0, first_col = m2->N;
        double value_tmp;
        std::vector<double> local_value;
        std::vector<int> local_row;

        #pragma omp for schedule(static)
        for (int j = 0; j < m2->N; j++) {
            if (j < first_col) first_col = j;

            colNZ = 0;
            for (int i = 0; i < transposed_m1.N; i++) {
                value_tmp = scalarMultiplication(&transposed_m1, m2, i, j);
                if (value_tmp != 0) {
                    local_value.push_back(value_tmp);
                    local_row.push_back(i);
                    colNZ++;
                }
            }
            res.colIndex[j] = colNZ;
        }

        #pragma omp master
        {
            int nz = 0, s = res.N;
            for (int j = 0; j < s; j++) {
                int tmp = res.colIndex[j];
                res.colIndex[j] = nz;
                nz += tmp;
            }
            res.colIndex[s] = nz;

            res.value.resize(res.colIndex.back());
            res.row.resize(res.colIndex.back());
        }

        #pragma omp barrier

        if (omp_get_thread_num() == 0) {
            std::memcpy(res.value.data(), local_value.data(),
                   local_value.size() * sizeof(double));
            std::memcpy(res.row.data(), local_row.data(),
                   local_row.size() * sizeof(int));

        } else if (local_value.size() != 0) {
            std::memcpy(&(res.value[res.colIndex[first_col]]),
                    local_value.data(), local_value.size() * sizeof(double));
            std::memcpy(&(res.row[res.colIndex[first_col]]),
                    local_row.data(), local_row.size() * sizeof(int));
        }
    }

    return res;
}

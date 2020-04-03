// Copyright 2020 Iamshchikov Ivan
#include <algorithm>
#include <cstring>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include "tbb/tbb.h"
#include "../../modules/task_3/iamshchikov_i_sparse_matrix_mult/sparse_matrix_mult.h"

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

    CcsMatrix m1(generateMatrix(M1, N1));
    CcsMatrix m2(generateMatrix(N1, N2));

    tbb::task_scheduler_init init(num_threads);

    tbb::tick_count t1 = tbb::tick_count::now();
    matrixMultiplicate(&m1, &m2);
    tbb::tick_count t2 = tbb::tick_count::now();

    init.terminate();

    return (t2 - t1).seconds();
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
    nz = static_cast<int>(sqrt(M*N));
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
    for (k = transposed_m->colIndex[i]; k < transposed_m->colIndex[i + 1]; k++)
        for (int l = m->colIndex[j]; l < m->colIndex[j + 1]; l++)
            if (transposed_m->row[k] == m->row[l]) {
                res += transposed_m->value[k] * m->value[l];
                break;
            }
    return res;
}

class Multiplicator {
 private:
    CcsMatrix transposed_A, B;
    std::vector<double>* value;
    std::vector<int>* row;
    std::vector<int>* resColIndex;

 public:
    Multiplicator(const CcsMatrix* _transposed_A, const CcsMatrix* _B,
        std::vector<double>* _value, std::vector<int>* _row,
        std::vector<int>* _resColIndex) : transposed_A(*_transposed_A), B(*_B),
        value(_value), row(_row), resColIndex(_resColIndex) {}
    void operator()(const tbb::blocked_range<int>& r) const {
        int colNZ = 0, first_col = B.N;
        double value_tmp;
        int begin = r.begin(), end = r.end();

        for (int j = begin; j < end; j++) {
            if (j < first_col) first_col = j;

            colNZ = 0;
            for (int i = 0; i < transposed_A.N; i++) {
                value_tmp = scalarMultiplication(&transposed_A, &B, i, j);
                if (value_tmp != 0) {
                    value[j].push_back(value_tmp);
                    row[j].push_back(i);
                    colNZ++;
                }
            }
            (*resColIndex)[j] = colNZ;
        }
    }
};

CcsMatrix matrixMultiplicate(const CcsMatrix* m1, const CcsMatrix* m2) {
    if (m1->N != m2->M) throw "m1 and m2 are incompatible";

    CcsMatrix res(m1->M, m2->N, 0);
    CcsMatrix transposed_m1(transposeMatrix(m1));
    int N = res.N;
    std::vector<double>* value = new std::vector<double>[N];
    std::vector<int>* row = new std::vector<int>[N];

    int grainsize = 10;
    tbb::parallel_for(tbb::blocked_range<int>(0, m2->N, grainsize),
    Multiplicator(&transposed_m1, m2, value, row, &res.colIndex));

    int nz = 0;
    for (int j = 0; j < N; j++) {
        int tmp = res.colIndex[j];
        res.colIndex[j] = nz;
        nz += tmp;
    }
    res.colIndex[N] = nz;

    res.value.resize(res.colIndex.back());
    res.row.resize(res.colIndex.back());

    int count = 0;
    for (int i = 0; i < N; i++) {
        int size = value[i].size();
        if (size > 0) {
            memcpy(&res.value[count], &value[i][0],
                size * sizeof(double));
            memcpy(&res.row[count], &row[i][0],
                size * sizeof(int));
            count += size;
        }
    }

    delete[] value;
    delete[] row;

    return res;
}

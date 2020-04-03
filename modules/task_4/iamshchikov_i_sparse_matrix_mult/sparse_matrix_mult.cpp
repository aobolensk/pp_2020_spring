// Copyright 2020 Iamshchikov Ivan
#include <algorithm>
#include <cstring>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <thread>
#include "../../modules/task_4/iamshchikov_i_sparse_matrix_mult/sparse_matrix_mult.h"

CcsMatrix::CcsMatrix(int _M, int _N, int nz) {
    if (_M <= 0 || _N <= 0) throw "wrong size";
    M = _M;
    N = _N;
    colIndex.resize(_N + 1);
    not_zero_number = nz;
    value.resize(nz);
    row.resize(nz);
}

int getInvolvedThreadNumber(int n, int th_num) {
    if (n / th_num == 0) return n;
    else if (n / th_num > 0) return th_num;
    else
        throw - 1;
}

void setNumberOfColumn(int nthreads, int N, std::vector<int>* number_of_col,
                       std::vector<int>* start_col) {
    int count = N / nthreads;
    if (N % nthreads != 0) {
        for (int i = 0; i < N % nthreads; ++i)
            number_of_col->push_back(count + 1);

        for (int i = N % nthreads; i < nthreads; ++i)
            number_of_col->push_back(count);
    } else {
        for (int i = 0; i < nthreads; ++i)
            number_of_col->push_back(count);
    }

    int tmp = 0;
    start_col->push_back(0);
    for (int i = 1; i < nthreads; i++) {
        tmp += number_of_col->at(i - 1);
        start_col->push_back(tmp);
    }
}

void  multOnThread(int th_num, std::vector<int>* number_of_col, 
                  std::vector<int>* start_col, const CcsMatrix* transposed_m1,
                  const CcsMatrix* m2, CcsMatrix* res, 
                  std::vector<double>* value, std::vector<int>* row) {
    int colNZ = 0;
    double value_tmp;
    int begin = start_col->at(th_num),
        end = begin + number_of_col->at(th_num);
    
    for (int j = begin; j < end; j++) {
        colNZ = 0;
        for (int i = 0; i < transposed_m1->N; i++) {
            value_tmp = scalarMultiplication(transposed_m1, m2, i, j);
            if (value_tmp != 0) {
                value[j].push_back(value_tmp);
                row[j].push_back(i);
                colNZ++;
            }
        }
        res->colIndex[j] = colNZ;
    }
}

double measurementOfTime(int M1, int N1, int N2, int nthreads) {
    if (M1 <= 0 || N1 <= 0 || N2 <= 0) throw "wrong size";
    if (nthreads <= 0) throw "wrong number of threads";

    std::chrono::time_point<std::chrono::steady_clock> begin, end;
    std::chrono::milliseconds elapsed_ms;
    CcsMatrix m1(generateMatrix(M1, N1));
    CcsMatrix m2(generateMatrix(N1, N2));

    begin = std::chrono::steady_clock::now();

    matrixMultiplicate(&m1, &m2, nthreads);

    end = std::chrono::steady_clock::now();
    elapsed_ms = 
    std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    return static_cast<double>(elapsed_ms.count());
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

CcsMatrix matrixMultiplicate(const CcsMatrix* m1, const CcsMatrix* m2, 
                             const int nthreads) {
    if (m1->N != m2->M) throw "m1 and m2 are incompatible";

    int involved_th_num;
    CcsMatrix res(m1->M, m2->N, 0);
    CcsMatrix transposed_m1(transposeMatrix(m1));
    int N = res.N;
    std::vector<int> number_of_col, start_col;
    std::vector<double>* value = new std::vector<double>[N];
    std::vector<int>* row = new std::vector<int>[N];
    std::thread *threads = new std::thread[nthreads];

    involved_th_num = getInvolvedThreadNumber(N, nthreads);
    setNumberOfColumn(involved_th_num, N, &number_of_col, &start_col);

    for (int i = 0; i < involved_th_num; i++)
        threads[i] = std::thread(multOnThread, i, &number_of_col, &start_col,
                                &transposed_m1, m2, &res, value, row);

    for (int i = 0; i < involved_th_num; i++)
        threads[i].join();

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
    delete[] threads;

    return res;
}

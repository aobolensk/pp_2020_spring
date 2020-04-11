// Copyright 2020 Iamshchikov Ivan
#include <vector>
#include "../../modules/task_1/iamshchikov_i_sparse_matrix_mult/sparse_matrix_mult.h"

CcsMatrix::CcsMatrix(int _M, int _N, int nz) {
    if (_M <= 0 || _N <= 0) throw "wrong size";
    M = _M;
    N = _N;
    colIndex.resize(_N + 1);
    not_zero_number = nz;
    value.resize(nz);
    row.resize(nz);
}

bool operator==(const CcsMatrix& m1, const CcsMatrix& m2) {
    return m1.value == m2.value && m1.row == m2.row &&
        m1.colIndex == m2.colIndex && m1.M == m2.M;
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
    double value_tmp;
    int colNZ;
    CcsMatrix res(m1->M, m2->N, 0);
    CcsMatrix transposed_m1(transposeMatrix(m1));

    for (int j = 0; j < m2->N; j++) {
        colNZ = 0;
        for (int i = 0; i < transposed_m1.N; i++) {
            value_tmp = scalarMultiplication(&transposed_m1, m2, i, j);
            if (value_tmp != 0) {
                res.value.push_back(value_tmp);
                res.row.push_back(i);
                colNZ++;
            }
        }
        res.colIndex[j + 1] = colNZ + res.colIndex[j];
    }

    return res;
}

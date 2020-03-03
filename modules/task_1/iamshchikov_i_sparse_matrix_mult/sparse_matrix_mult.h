// Copyright 2020 Iamshchikov Ivan
#ifndef MODULES_TASK_1_IAMSHCHIKOV_I_SPARSE_MATRIX_MULT_SPARSE_MATRIX_MULT_H_
#define MODULES_TASK_1_IAMSHCHIKOV_I_SPARSE_MATRIX_MULT_SPARSE_MATRIX_MULT_H_
#include <vector>

struct CcsMatrix {
    int M, N;
    int not_zero_number;

    std::vector<double> value;
    std::vector<int> row;
    std::vector<int> colIndex;

    CcsMatrix(int _M, int _N, int nz);
};

bool operator==(const CcsMatrix& m1, const CcsMatrix& m2);
CcsMatrix transposeMatrix(const CcsMatrix* m);
double scalarMultiplication(const CcsMatrix* transposed_m, const CcsMatrix* m,
                            int i, int j);
CcsMatrix matrixMultiplicate(const CcsMatrix* m1, const CcsMatrix* m2);


#endif  // MODULES_TASK_1_IAMSHCHIKOV_I_SPARSE_MATRIX_MULT_SPARSE_MATRIX_MULT_H_

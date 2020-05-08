// Copyright 2020 Iamshchikov Ivan
#ifndef MODULES_TASK_4_IAMSHCHIKOV_I_SPARSE_MATRIX_MULT_SPARSE_MATRIX_MULT_H_
#define MODULES_TASK_4_IAMSHCHIKOV_I_SPARSE_MATRIX_MULT_SPARSE_MATRIX_MULT_H_
#include <vector>

struct CcsMatrix {
    int M, N;
    int not_zero_number;

    std::vector<double> value;
    std::vector<int> row;
    std::vector<int> colIndex;

    CcsMatrix(int _M, int _N, int nz);
    CcsMatrix() = default;
};

int getInvolvedThreadNumber(int n, int th_num);
void setNumberOfColumn(int nthreads, int N, std::vector<int>* number_of_col, 
                       std::vector<int>* start_col);
void multOnThread(int th_num, std::vector<int>* number_of_col, 
    std::vector<int>* start_col, const CcsMatrix* transposed_m1,
    const CcsMatrix* m2, CcsMatrix* res, std::vector<double>* value,
    std::vector<int>* row);
double measurementOfTime(int M1, int N1, int N2, int nthreads);
bool operator==(const CcsMatrix& m1, const CcsMatrix& m2);
CcsMatrix generateMatrix(int M, int N);
CcsMatrix transposeMatrix(const CcsMatrix* m);
double scalarMultiplication(const CcsMatrix* transposed_m, const CcsMatrix* m,
    int i, int j);
CcsMatrix matrixMultiplicate(const CcsMatrix* m1, const CcsMatrix* m2,
    const int nthreads = std::thread::hardware_concurrency());

#endif  // MODULES_TASK_4_IAMSHCHIKOV_I_SPARSE_MATRIX_MULT_SPARSE_MATRIX_MULT_H_

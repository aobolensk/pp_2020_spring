// Copyright 2020 Makarova Viktoria
#ifndef MODULES_TASK_3_MAKAROVA_V_CRS_MATRIX_MULT_TBB_MATRIX_MULT_H_
#define MODULES_TASK_3_MAKAROVA_V_CRS_MATRIX_MULT_TBB_MATRIX_MULT_H_
#include <vector>
#include <complex>

struct Matrix {
    int rows, cols;
    std::vector<std::complex<int>> val;
    Matrix(int rows, int cols): rows(rows), cols(cols) {
        val = std::vector<std::complex<int>>(cols * rows);
    }
    ~Matrix() = default;
};

struct MatrixCRS {
    int rows, cols;
    std::vector<std::complex<int>> val;
    std::vector<int> cols_pos;
    std::vector<int> ptrs;
    MatrixCRS() = default;
    ~MatrixCRS() = default;
};

MatrixCRS generateRandomCRSMat(int rows, int cols);
Matrix generateRandomMat(int rows, int cols);

MatrixCRS convert(const Matrix &inMat);
MatrixCRS transp(const MatrixCRS &inMat);

MatrixCRS matrixCRSMult(const MatrixCRS &first, const MatrixCRS &second);
MatrixCRS matrixCRSMultTBB(const MatrixCRS &first, const MatrixCRS &second);
Matrix matrixMult(const Matrix &first, const Matrix &second);

void print(const MatrixCRS &in);

#endif  // MODULES_TASK_3_MAKAROVA_V_CRS_MATRIX_MULT_TBB_MATRIX_MULT_H_

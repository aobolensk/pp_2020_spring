// Copyright 2020 Kurakin Mikhail
#ifndef MODULES_TASK_1_KURAKIN_M_MULTIPLY_MATRIX_FOX_MULTIPLY_MATRIX_FOX_H_
#define MODULES_TASK_1_KURAKIN_M_MULTIPLY_MATRIX_FOX_MULTIPLY_MATRIX_FOX_H_
#include <vector>

typedef std::vector<std::vector<double>> matrix;
typedef unsigned int uint;
bool canMultiplicate(const matrix &a, const matrix &b);
void prepareOutMatrix(matrix *matrixOut, uint sizeRow, uint sizeCol);
bool initMatrixRand(matrix *a, uint sizeRow, uint sizeCol);
bool simpleMaxtrixMultiply(const matrix &a, const matrix &b, matrix *out);

bool canUseFoxAlg(const matrix &a, const matrix &b);
bool algFoxMatrixMultiply(const matrix &a, const matrix &b, matrix *out);

#endif  // MODULES_TASK_1_KURAKIN_M_MULTIPLY_MATRIX_FOX_MULTIPLY_MATRIX_FOX_H_

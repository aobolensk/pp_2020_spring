// Copyright 2020 Nazarov Vladislav
#ifndef MODULES_TASK_1_NAZAROV_V_SPARCE_MATRIX_MULTIPLICATION_SPARCE_MATRIX_MULTIPLICATION_H_
#define MODULES_TASK_1_NAZAROV_V_SPARCE_MATRIX_MULTIPLICATION_SPARCE_MATRIX_MULTIPLICATION_H_

#include <vector>
#include <complex>
#include <iostream>
#include <cmath>

typedef std::complex<double> cpx;

class CRS_Matrix {
    std::vector<cpx> val;
    std::vector<size_t> colIndex;
    std::vector<size_t> rowIndex;
    size_t col, row;
 public:
    explicit CRS_Matrix(const std::vector<std::vector<cpx>>& matrix);
    CRS_Matrix(const std::vector<cpx> _val, std::vector<size_t> _colIndex, std::vector<size_t> _rowIndex) :
        val(_val), colIndex(_colIndex), rowIndex(_rowIndex) {}
    bool operator== (const CRS_Matrix& mat);
    std::vector<cpx> getVal() {return val;}
    std::vector<size_t> getColIndex() {return colIndex;}
    std::vector<size_t> getRowIndex() {return rowIndex;}
};

#endif  // MODULES_TASK_1_NAZAROV_V_SPARCE_MATRIX_MULTIPLICATION_SPARCE_MATRIX_MULTIPLICATION_H_

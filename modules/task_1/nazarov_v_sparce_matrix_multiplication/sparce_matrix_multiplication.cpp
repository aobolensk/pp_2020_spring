// Copyright 2020 Nazarov Vladislav

#include <vector>
#include <stdexcept>
#include "../../../modules/task_1/nazarov_v_sparce_matrix_multiplication/sparce_matrix_multiplication.h"

CRS_Matrix::CRS_Matrix(const std::vector<std::vector<cpx>>& matrix) {
    row = matrix.size();
    col = matrix[0].size();
    for (const auto& elem : matrix)
        if (elem.size() != col)
            throw std::runtime_error("Different numbers of columns");
    size_t NonZeroCounter = 0;
    rowIndex.push_back(0);

    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j)
            if ((std::abs(matrix[i][j].real()) > pow(10, -9)) && (std::abs(matrix[i][j].imag()) > pow(10, -9))) {
                val.push_back(matrix[i][j]);
                colIndex.push_back(j);
                NonZeroCounter++;
            }
        rowIndex.push_back(NonZeroCounter);
    }
}

bool CRS_Matrix::operator== (const CRS_Matrix& mat) {
    if ((colIndex != mat.colIndex) || (rowIndex != mat.rowIndex) || (val.size() != mat.val.size()))
        return false;
    for (size_t i = 0; i < val.size(); ++i) {
        if ((std::abs(val[i].real()-mat.val[i].real()) > pow(10, -9)) ||
            (std::abs(val[i].imag()-mat.val[i].imag()) > pow(10, -9)) )
            return false;
    }
    return true;
}

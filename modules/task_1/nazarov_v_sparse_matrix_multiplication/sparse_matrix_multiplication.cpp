// Copyright 2020 Nazarov Vladislav

#include <vector>
#include <stdexcept>
#include "../../../modules/task_1/nazarov_v_sparse_matrix_multiplication/sparse_matrix_multiplication.h"

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
            if ((std::abs(matrix[i][j].real()) > pow(10, -9)) || (std::abs(matrix[i][j].imag()) > pow(10, -9))) {
                val.push_back(matrix[i][j]);
                colIndex.push_back(j);
                NonZeroCounter++;
            }
        rowIndex.push_back(NonZeroCounter);
    }
}

bool CRS_Matrix::operator== (const CRS_Matrix& mat) const& {
    if ((row != mat.row) || (col != mat.col) || (colIndex != mat.colIndex) ||
       (rowIndex != mat.rowIndex) || (val.size() != mat.val.size()))
        return false;
    for (size_t i = 0; i < val.size(); ++i) {
        if ((std::abs(val[i].real()-mat.val[i].real()) > pow(10, -9)) ||
            (std::abs(val[i].imag()-mat.val[i].imag()) > pow(10, -9)) )
            return false;
    }
    return true;
}

// CRS_Matrix CRS_Matrix::operator* (const CRS_Matrix& mat) const& {

// }

CRS_Matrix CRS_Matrix::transpose() {
    std::vector<std::vector<size_t>> index(col);
    std::vector<std::vector<cpx>> values(col);
    for (size_t i = 1; i < rowIndex.size(); ++i)
        for (size_t j = rowIndex[i-1]; j < rowIndex[i]; ++j) {
            index[colIndex[j]].push_back(i-1);
            values[colIndex[j]].push_back(val[j]);
        }
    CRS_Matrix res;
    res.col = row;
    res.row = col;
    size_t size = 0;
    res.rowIndex.push_back(0);
    for (size_t i = 0; i < col; ++i) {
        for (size_t j = 0; j < index[i].size(); ++j) {
            res.val.push_back(values[i][j]);
            res.colIndex.push_back(index[i][j]);
        }
        size += index[i].size();
        res.rowIndex.push_back(size);
    }
    // for (auto& elem : index) {
    //     for(auto& elem1 : elem)
    //         std::cout << elem1<<" ";
    //     std::cout<<std::endl;
    // }
    // for (auto& elem : values) {
    //     for(auto& elem1 : elem)
    //         std::cout << elem1<<" ";
    //     std::cout<<std::endl;
    // }
    return res;
}

void CRS_Matrix::print() {
    std::cout << "Value = [ ";
    for (const auto& elem : val)
        std::cout << elem << " ";
    std::cout << "] " << std::endl << "Col_Index = [ ";
    for (const auto& elem : colIndex)
        std::cout << elem << " ";
    std::cout << "] " << std::endl << "Row_Index = [ ";
    for (const auto& elem : rowIndex)
        std::cout << elem << " ";
    std::cout << "] " << std::endl;
}

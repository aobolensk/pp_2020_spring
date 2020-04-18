// Copyright 2020 Nazarov Vladislav

#include <omp.h>
#include <vector>
#include <stdexcept>
#include <random>
#include <set>
#include <utility>
#include "../../../modules/task_2/nazarov_v_sparse_matrix_multiplication/sparse_matrix_multiplication.h"

CRS_Matrix::CRS_Matrix(const std::vector<std::vector<cpx>>& matrix) {
    row = matrix.size();
    col = matrix[0].size();
    for (const auto& elem : matrix)
        if (elem.size() != col)
            throw std::runtime_error("Different numbers of columns");
    size_t NonZeroCounter = 0;
    rowIndex.push_back(0ul);

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

CRS_Matrix CRS_Matrix::operator* (const CRS_Matrix& mat) const& {
    CRS_Matrix res;
    res.rowIndex.push_back(0);
    res.row = row;
    res.col = mat.row;
    size_t NonZeroCounter = 0;
    if (col != mat.col)
        throw std::runtime_error("Different numbers of cols");
    for (size_t i = 1; i < rowIndex.size(); ++i) {
        std::vector<cpx> tmpVec(mat.rowIndex.size(), cpx(0, 0));
        for (size_t j = 1; j < mat.rowIndex.size(); ++j) {
            cpx sum = 0;
            size_t lhsIter = rowIndex[i-1], rhsIter = mat.rowIndex[j-1];
            while ((lhsIter < rowIndex[i]) && (rhsIter < mat.rowIndex[j])) {
                if (colIndex[lhsIter] == mat.colIndex[rhsIter]) {
                    sum += val[lhsIter++] * mat.val[rhsIter++];
                } else {
                    if (colIndex[lhsIter] < mat.colIndex[rhsIter])
                        lhsIter++;
                    else
                        rhsIter++;
                }
            }
            if (std::abs(sum.real()) > pow(10, -9) || std::abs(sum.imag()) > pow(10, -9)) {
                tmpVec[j-1] = sum;
                NonZeroCounter++;
            }
        }
        for (size_t iter = 0; iter < mat.rowIndex.size(); ++iter)
            if (std::abs(tmpVec[iter].real()) > pow(10, -9) || std::abs(tmpVec[iter].imag()) > pow(10, -9)) {
                res.val.push_back(tmpVec[iter]);
                res.colIndex.push_back(iter);
            }
        res.rowIndex.push_back(NonZeroCounter);
    }
    return res;
}

CRS_Matrix CRS_Matrix::parallelMultiply(const CRS_Matrix& mat) const& {
    CRS_Matrix res;
    res.rowIndex.push_back(0);
    res.row = row;
    res.col = mat.row;
    size_t NonZeroCounter = 0;
    if (col != mat.col)
        throw std::runtime_error("Different numbers of cols");
    for (size_t i = 1; i < rowIndex.size(); ++i) {
        std::vector<cpx> tmpVec(mat.rowIndex.size(), cpx(0, 0));
#pragma omp parallel for schedule(static, 16)
        for (int j = 1; j < static_cast<int>(mat.rowIndex.size()); ++j) {
            cpx sum = 0;
            size_t lhsIter = rowIndex[i-1], rhsIter = mat.rowIndex[j-1];
            while ((lhsIter < rowIndex[i]) && (rhsIter < mat.rowIndex[j])) {
                if (colIndex[lhsIter] == mat.colIndex[rhsIter]) {
                    sum += val[lhsIter++] * mat.val[rhsIter++];
                } else {
                    if (colIndex[lhsIter] < mat.colIndex[rhsIter])
                        lhsIter++;
                    else
                        rhsIter++;
                }
            }
            if (std::abs(sum.real()) > pow(10, -9) || std::abs(sum.imag()) > pow(10, -9)) {
                tmpVec[j-1] = sum;
#pragma omp atomic
                NonZeroCounter++;
            }
        }
        for (size_t iter = 0; iter < mat.rowIndex.size(); ++iter)
            if (std::abs(tmpVec[iter].real()) > pow(10, -9) || std::abs(tmpVec[iter].imag()) > pow(10, -9)) {
                res.val.push_back(tmpVec[iter]);
                res.colIndex.push_back(iter);
            }
        res.rowIndex.push_back(NonZeroCounter);
    }
    return res;
}

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

std::vector<std::vector<cpx>> CRS_Matrix::getSparseMatrix() {
    std::vector<std::vector<cpx>> res(row);
    for (auto& elem : res)
        elem.resize(col);
    for (size_t i = 1; i < rowIndex.size(); ++i) {
        size_t rowIter = rowIndex[i-1];
        for (size_t j = 0; j < col; ++j) {
            if ((rowIter < rowIndex[i]) && (j == colIndex[rowIter])) {
                res[i-1][j] = val[rowIter];
                rowIter++;
            } else {
                res[i-1][j] = 0;
            }
        }
    }
    return res;
}


std::vector<std::vector<cpx>> naiveMultiplication(const std::vector<std::vector<cpx>>& matrix1,
    const std::vector<std::vector<cpx>>& matrix2) {
    if (matrix1[0].size() != matrix2.size())
    throw std::runtime_error("Different numbers of cols");
    std::vector<std::vector<cpx>> res(matrix1.size(), std::vector<cpx>(matrix2[0].size()));
    for (size_t i = 0; i < matrix1.size(); ++i)
        for (size_t j = 0; j < matrix2[0].size(); ++j) {
            res[i][j] = 0;
            for (size_t k = 0; k < matrix1[0].size(); ++k)
                res[i][j] += matrix1[i][k] * matrix2[k][j];
        }
    return res;
}

CRS_Matrix getRandomCRSMatrix(const size_t& col, const size_t& row, const double& percent) {
    if ((percent > 1) || (percent < 0))
        throw std::runtime_error("Invalid parameters");
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disComplex(1, 10);
    std::uniform_int_distribution<> disRow(0, row-1);
    std::uniform_int_distribution<> disCol(0, col-1);
    std::set<std::pair<int, int>> index;
    size_t num = static_cast<size_t>(col*row*percent);
    if (num < 1)
        num++;
    while (index.size() < num)
        index.insert(std::pair<int, int>(disRow(gen), disCol(gen)));
    std::vector<cpx> _val;
    std::vector<size_t> _col, _row;
    _row.push_back(0ul);
    size_t curRow = 0;
    size_t NonZeroCounter = 0;
    for (const std::pair<int, int>& elem : index) {
        while (static_cast<size_t>(elem.first) != curRow) {
            curRow++;
            _row.push_back(NonZeroCounter);
        }
        NonZeroCounter++;
        _col.push_back(static_cast<size_t>(elem.second));
        _val.push_back(cpx(disComplex(gen), disComplex(gen)));
    }
    for (; curRow < row; ++curRow)
        _row.push_back(NonZeroCounter);
    return CRS_Matrix(_val, _col, _row, col, row);
}

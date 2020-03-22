// Copyright 2020 Sokolov Andrey
#include <vector>
#include "../../../modules/task_1/sokolov_a_sparse_matrix_string_crs/sparse_matrix_string_crs.h"

SparseMatrix::SparseMatrix(const Matrix& matrix) {
    rows = matrix.size();
    cols = matrix[0].size();

    size_t elemsInRow{0};
    constexpr double tolerance{1e-6};
    rowIndex.reserve(rows + 1);
    rowIndex.push_back(0);

    for (size_t idx{0}; idx < rows; ++idx) {
        for (size_t jdx{0}; jdx < cols; ++jdx) {
            if (std::fabs(matrix[idx][jdx]) >= tolerance) {
                value.push_back(matrix[idx][jdx]);
                colIndex.push_back(jdx);
                ++elemsInRow;
            }
        }
        rowIndex.push_back(elemsInRow);
    }
}

SparseMatrix::SparseMatrix(size_t _rows, size_t _cols,
                           std::vector<double> _value,
                           std::vector<size_t>    _colIndex,
                           std::vector<size_t>    _rowIndex) {
    rows = _rows;
    cols = _cols;
    value = _value;
    colIndex = _colIndex;
    rowIndex = _rowIndex;
}

SparseMatrix::SparseMatrix(size_t _rows, size_t _cols, size_t _elemsCount) {
    rows = _rows;
    cols = _cols;
    value.resize(_elemsCount);
    colIndex.resize(_elemsCount);
    rowIndex.resize(_rows + 1);
}

bool SparseMatrix::operator== (const SparseMatrix& matrix) const& {
    if (rows != matrix.rows) {
        std::cout << "Rows are not equal" << std::endl;
        return false;
    } else if (cols != matrix.cols) {
        std::cout << "Cols are not equal" << std::endl;
        return false;
    } else if (colIndex != matrix.colIndex) {
        std::cout << "colIndex are not equal" << std::endl;
        return false;
    } else if (rowIndex != matrix.rowIndex) {
        std::cout << "rowIndex are not equal" << std::endl;
        return false;
    } else if (value.size() != matrix.value.size()) {
        std::cout << "Value size are not equal" << std::endl;
        return false;
    }
    for (size_t idx{0}; idx < value.size(); ++idx) {
        if ((std::abs(value[idx] - matrix.value[idx]) > 1e-3)) {
            return false;
            std::cout << "Not Equal! " << value[idx] << " and " << matrix.value[idx]  << std::endl;
        }
    }
    return true;
}

Matrix SparseMatrix::SparseToMatrix() {
    Matrix result{};
    result.resize(rows);
    for (size_t idx{0}; idx < rows; ++idx) {
        result[idx].resize(cols);
    }
    size_t tmpCols{0};
    for (size_t idx{0}; idx < rows; ++idx) {
        size_t tmpRows{rowIndex[idx+1] - rowIndex[idx]};
        for (size_t jdx{0}; jdx < cols; jdx++) {
            if (jdx == colIndex[tmpCols] && tmpRows != 0) {
                tmpRows--;
                result[idx][jdx] = value[tmpCols++];
            } else {
                result[idx][jdx] = 0.0;
            }
        }
    }
    return result;
}

SparseMatrix SparseMatMul(const SparseMatrix& matrixA, const SparseMatrix& matrixB) {
    SparseMatrix result{};
    result.rows = matrixA.rows;
    result.cols = matrixB.cols;
    result.rowIndex.push_back(0);
    std::vector<double> tmpResultRow(matrixA.rows, 0);

    for (size_t idx{0}; idx < matrixA.rows; ++idx) {
        for (size_t jdx{matrixA.rowIndex[idx]}; jdx < matrixA.rowIndex[idx + 1]; ++jdx) {
            size_t tmpCol {matrixA.colIndex[jdx]};

            for (size_t kdx{matrixB.rowIndex[tmpCol]}; kdx < matrixB.rowIndex[tmpCol + 1]; ++kdx) {
                tmpResultRow[matrixB.colIndex[kdx]] += matrixA.value[jdx] * matrixB.value[kdx];
            }
        }
        for (size_t kdx{0}; kdx < matrixA.rows; ++kdx) {
            if (tmpResultRow[kdx] != 0) {
                result.value.push_back(tmpResultRow[kdx]);
                result.colIndex.push_back(kdx);
                tmpResultRow[kdx] = 0;
            }
        }
        result.rowIndex.push_back(result.value.size());
    }
    return result;
}

Matrix MatMul(const Matrix& matrixA, const Matrix& matrixB) {
    Matrix result{matrixA.size()};
    for (size_t idx{0}; idx < result.size(); ++idx) {
        result[idx].resize(matrixB[0].size());
    }

    for (size_t idx{0}; idx < matrixA.size(); ++idx) {
        for (size_t jdx{0}; jdx < matrixB[0].size(); ++jdx) {
            result[idx][jdx] = 0;
            for (size_t kdx{0}; kdx < matrixA[0].size(); ++kdx) {
                result[idx][jdx] += matrixA[idx][kdx] * matrixB[kdx][jdx];
            }
        }
    }
    return result;
}

// coeff from 0 to 100
Matrix generateMatrix(const size_t& rows, const size_t& cols, const size_t& coeff) {
    Matrix result{};
    result.resize(rows);
    for (size_t idx{0}; idx < rows; ++idx) {
        result[idx].resize(cols);
    }
    std::random_device rd{};
    std::mt19937 mt {rd()};
    std::uniform_real_distribution<double> disValue{ 0.0, 10.0 };
    std::uniform_int_distribution<size_t> disProbability {0, 100};

    for (size_t idx{ 0 }; idx < rows; ++idx) {
        for (size_t jdx{ 0 }; jdx < cols; ++jdx) {
            result[idx][jdx] = 0.0;
            if (disProbability(mt) <= coeff) {
                result[idx][jdx] = disValue(mt);
            }
        }
    }
    return result;
}

void SparseMatrix::printDefault() {
    std::cout << "Value:" << std::endl;
    for (size_t idx{ 0 }; idx < value.size(); ++idx) {
        std::cout << value[idx] << " ";
    }
    std::cout << std::endl << "colIndex:" << std::endl;
    for (size_t idx{ 0 }; idx < colIndex.size(); ++idx) {
        std::cout << colIndex[idx] << " ";
    }
    std::cout << std::endl << "rowIndex:" << std::endl;
    for (size_t idx{ 0 }; idx < rowIndex.size(); ++idx) {
        std::cout << rowIndex[idx] << " ";
    }
    std::cout << std::endl;
}

void SparseMatrix::printMatrix() {
    size_t tmpValue{ 0 };
    size_t tmpRows{ 0 };
    size_t tmpCols{ 0 };
    for (size_t idx{ 0 }; idx < rows; ++idx) {
        for (size_t jdx{ 0 }; jdx < cols; ++jdx) {
            if (tmpRows == rowIndex[idx + 1]) {
                std::cout << "0   ";
            } else if (jdx == colIndex[tmpCols]) {
                std::cout << round(value[tmpValue] * 10) / 10 << " ";
                tmpValue++;
                tmpCols++;
                tmpRows++;
            } else {
                std::cout << "0   ";
            }
        }
        std::cout << std::endl;
    }
}

void print(const Matrix& matrix) {
    for (size_t idx{ 0 }; idx < matrix.size(); ++idx) {
        for (size_t jdx{ 0 }; jdx < matrix[0].size(); ++jdx) {
            std::cout << round(matrix[idx][jdx] * 10) / 10 << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

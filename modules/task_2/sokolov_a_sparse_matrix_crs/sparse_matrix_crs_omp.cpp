// Copyright 2020 Sokolov Andrey
#include <omp.h>
#include "./sparse_matrix_crs_omp.h"


SparseMatrix::SparseMatrix(const Matrix& matrix) {
    rows = matrix.size();
    cols = matrix[0].size();

    size_t elemsInRow{0};
    constexpr double tolerance{1e-6};
    rowIndex = {};
    colIndex = {};
    value = {};
    rowIndex.reserve(rows * cols);
    colIndex.reserve(rows * cols);
    value.reserve(rows + 1);
    rowIndex.push_back(0);

    for (int idx{0}; idx < rows; ++idx) {
        for (int jdx{0}; jdx < cols; ++jdx) {
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
                           std::vector<int> _colIndex,
                           std::vector<int> _rowIndex) {
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
    Matrix result(rows, std::vector<double>(cols, 0.0));

    int tmpCols{0};
    for (int idx{0}; idx < rows; ++idx) {
        int tmpRows{rowIndex[idx+1] - rowIndex[idx]};
        while (tmpRows != 0) {
            result[idx][colIndex[tmpCols]] = value[tmpCols];
            tmpRows--;
            tmpCols++;
        }
    }
    return result;
}

SparseMatrix SparseMatMul(const SparseMatrix& matrixA, const SparseMatrix& matrixB) {
    SparseMatrix result{};
    result.rows = matrixA.rows;
    result.cols = matrixB.cols;
    result.rowIndex = {};
    result.colIndex = {};
    result.value = {};
    result.rowIndex.reserve(result.rows + 1);
    result.colIndex.reserve(result.rows * result.cols);
    result.value.reserve(result.rows * result.cols);
    result.rowIndex.push_back(0);
    std::vector<double> tmpResultRow(matrixA.rows, 0);

    for (int idx{ 0 }; idx < matrixA.rows; ++idx) {
        for (int jdx{ matrixA.rowIndex[idx] }; jdx < matrixA.rowIndex[idx + 1]; ++jdx) {
            int tmpCol{ matrixA.colIndex[jdx] };

            for (int kdx{ matrixB.rowIndex[tmpCol] }; kdx < matrixB.rowIndex[tmpCol + 1]; ++kdx) {
                tmpResultRow[matrixB.colIndex[kdx]] += matrixA.value[jdx] * matrixB.value[kdx];
            }
        }
        for (int kdx{ 0 }; kdx < matrixA.rows; ++kdx) {
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

SparseMatrix SparseMatMulOmp(const SparseMatrix& matrixA, const SparseMatrix& matrixB) {
    constexpr int numThreads{4};
    omp_set_num_threads(numThreads);

    SparseMatrix result{};
    result.rows = matrixA.rows;
    result.cols = matrixB.cols;
    result.rowIndex.resize(result.rows + 1);
    std::vector<int> tmpResultRow(matrixA.rows + 1, 0);
    std::vector<int>* tmpResultCols = new std::vector<int>[matrixA.rows];
    std::vector<double>* tmpResultValue = new std::vector<double>[matrixA.rows];
    int tmpCol {0};

#pragma omp parallel for default(shared) private(tmpCol)
    for (int idx = 0; idx < matrixA.rows; ++idx) {
        std::vector<double> tmpResult(matrixA.rows + 1, 0);
        for (int jdx{matrixA.rowIndex[idx]}; jdx < matrixA.rowIndex[idx + 1]; ++jdx) {
            tmpCol = matrixA.colIndex[jdx];
            for (int kdx{matrixB.rowIndex[tmpCol]}; kdx < matrixB.rowIndex[tmpCol + 1]; ++kdx) {
                tmpResult[matrixB.colIndex[kdx]] += matrixA.value[jdx] * matrixB.value[kdx];
            }
        }
        for (int kdx{0}; kdx < matrixA.rows; ++kdx) {
            if (tmpResult[kdx] != 0.0) {
                tmpResultValue[idx].push_back(tmpResult[kdx]);
                tmpResultCols[idx].push_back(kdx);
                tmpResultRow[idx]++;
            }
        }
    }

    int count{0};
    int tmpRows{0};

    for (int idx{0}; idx < result.rows; ++idx) {
        int tmp = tmpResultRow[idx];
        result.rowIndex[idx] = tmpRows;
        tmpRows += tmp;
    }

    result.rowIndex[matrixA.rows] = tmpRows;
    result.colIndex.resize(tmpRows);
    result.value.resize(tmpRows);
    for (int idx{0}; idx < result.rows; ++idx) {
        size_t size {tmpResultCols[idx].size()};
        if (size != 0) {
            memcpy(&result.colIndex[count], &tmpResultCols[idx][0], size * sizeof(int));
            memcpy(&result.value[count], &tmpResultValue[idx][0], size * sizeof(double));
            count += size;
        }
    }
    delete[]tmpResultCols;
    delete[]tmpResultValue;

    return result;
}

Matrix MatMul(const Matrix& matrixA, const Matrix& matrixB) {
    size_t rowsA = matrixA.size();
    size_t colsA = matrixA[0].size();
    size_t colsB = matrixB[0].size();

    Matrix result(rowsA, std::vector<double>(colsB));

    for (size_t idx{0}; idx < rowsA; ++idx) {
        for (size_t jdx{0}; jdx < colsB; ++jdx) {
            result[idx][jdx] = 0;
            for (size_t kdx{0}; kdx < colsA; ++kdx) {
                result[idx][jdx] += matrixA[idx][kdx] * matrixB[kdx][jdx];
            }
        }
    }
    return result;
}

// coeff from 0 to 100
Matrix generateMatrix(const size_t& rows, const size_t& cols, const size_t& coeff) {
    Matrix result{};
    result.resize(rows, std::vector<double>(cols));

    std::random_device rd{};
    std::mt19937 mt {rd()};
    std::uniform_real_distribution<double> disValue{ 0.0, 10.0 };
    std::uniform_int_distribution<size_t> disProbability {0, 100};

    for (size_t idx{0U}; idx < rows; ++idx) {
        for (size_t jdx{0U}; jdx < cols; ++jdx) {
            if (disProbability(mt) <= coeff) {
                result[idx][jdx] = disValue(mt);
            } else {
                result[idx][jdx] = 0.0;
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
    int tmpValue{ 0 };
    int tmpRows{ 0 };
    int tmpCols{ 0 };
    for (int idx{ 0 }; idx < rows; ++idx) {
        for (int jdx{ 0 }; jdx < cols; ++jdx) {
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

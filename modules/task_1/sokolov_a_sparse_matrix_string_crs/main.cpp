// Copyright 2020 Sokolov Andrey
#include <gtest/gtest.h>
#include <vector>
#include "./sparse_matrix_string_crs.h"

// #define DEBUG
// #define DEBUG_LAST

TEST(Sparse_Matrix, Test_Create_Sparse_Matrix) {
    Matrix matrix{ { 1.1, 0.0, 0.0, 0.0, 2.2, 0.0 },
                   { 0.0, 0.0, 3.3, 4.4, 0.0, 0.0 },
                   { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                   { 0.0, 0.0, 0.0, 8.8, 0.0, 5.5 },
                   { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                   { 0.0, 7.7, 1.1, 0.0, 0.0, 6.6} };
    SparseMatrix sparseMatrixA{ matrix };

    size_t rows{ 6 };
    size_t cols{ 6 };
    std::vector<double> value{ 1.1, 2.2, 3.3, 4.4, 8.8, 5.5, 7.7, 1.1, 6.6 };
    std::vector<size_t> colIndex{ 0, 4, 2, 3, 3, 5, 1, 2, 5 };
    std::vector<size_t> rowIndex{ 0, 2, 4, 4, 6, 6, 9 };
    SparseMatrix sparseMatrixB{ rows, cols, value, colIndex, rowIndex };

    ASSERT_EQ(sparseMatrixA, sparseMatrixB);
}

TEST(Sparse_Matrix, Test_Compare_Sparse_Matrix) {
    size_t rowsA{ 6 };
    size_t colsA{6};
    std::vector<double> valueA{1.1, 2.2, 3.3, 4.4, 8.8, 5.5, 7.7, 1.1, 6.6};
    std::vector<size_t> colIndexA{0, 4, 2, 3, 3, 5, 1, 2, 5};
    std::vector<size_t> rowIndexA{0, 2, 4, 4, 6, 6, 9};

    size_t rowsB{ 6 };
    size_t colsB{ 6 };
    std::vector<double> valueB{ 1.1, 2.2, 3.3, 4.4, 8.8, 5.5, 7.7, 1.1, 6.6 };
    std::vector<size_t> colIndexB{ 0, 4, 2, 3, 3, 5, 1, 2, 5 };
    std::vector<size_t> rowIndexB{ 0, 2, 4, 4, 6, 6, 9 };

    SparseMatrix matrixA{ rowsA, colsA, valueA, colIndexA, rowIndexA };
    SparseMatrix matrixB{ rowsB, colsB, valueB, colIndexB, rowIndexB };
    ASSERT_TRUE(matrixA == matrixB);
}

TEST(Sparse_Matrix, Test_Sparse_To_Matrix) {
    size_t rowsA{ 6 };
    size_t colsA{ 6 };
    std::vector<double> valueA{ 1.1, 2.2, 3.3, 4.4, 8.8, 5.5, 7.7, 1.1, 6.6 };
    std::vector<size_t> colIndexA{ 0, 4, 2, 3, 3, 5, 1, 2, 5 };
    std::vector<size_t> rowIndexA{ 0, 2, 4, 4, 6, 6, 9 };

    SparseMatrix matrixSparse{ rowsA, colsA, valueA, colIndexA, rowIndexA };
    Matrix       matrix{ matrixSparse.SparseToMatrix() };
    SparseMatrix result{ matrix };

#ifdef DEBUG
    std::cout << "Matrix Sparse:" << std::endl;
    matrixSparse.printDefault();
    std::cout << std::endl;
    matrixSparse.printMatrix();
    std::cout << std::endl;
    std::cout << "Matrix: "<< std::endl;
    print(matrix);
    std::cout << "Result:" << std::endl;
    result.printDefault();
    std::cout << std::endl;
    result.printMatrix();
    std::cout << std::endl;
#endif

    ASSERT_EQ(matrixSparse, result);
}

TEST(Sparse_Matrix, Test_Random_Sparse_To_Matrix) {
    SparseMatrix matrixSparse{ generateMatrix(50, 50, 2) };
    Matrix       matrix{ matrixSparse.SparseToMatrix() };
    SparseMatrix result{ matrix };

#ifdef DEBUG
    std::cout << "Matrix Sparse:" << std::endl;
    matrixSparse.printDefault();
    std::cout << std::endl;
    matrixSparse.printMatrix();
    std::cout << std::endl;
    std::cout << "Matrix: " << std::endl;
    print(matrix);
    std::cout << "Result:" << std::endl;
    result.printDefault();
    std::cout << std::endl;
    result.printMatrix();
    std::cout << std::endl;
#endif

    ASSERT_EQ(matrixSparse, result);
}

TEST(Sparse_Matrix, Test_Matrix_Miltiplication) {
    constexpr double tolerance{ 1e-4 };

    Matrix matrixA{ { 1.1, 0.0, 0.0, 0.0, 2.2, 0.0 },
                    { 0.0, 0.0, 3.3, 4.4, 0.0, 0.0 },
                    { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                    { 0.0, 0.0, 0.0, 8.8, 0.0, 5.5 },
                    { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                    { 0.0, 7.7, 1.1, 0.0, 0.0, 6.6 } };

    Matrix matrixB{ { 1.1, 0.0, 0.0, 0.0, 2.2, 0.0 },
                    { 0.0, 0.0, 3.3, 4.4, 0.0, 0.0 },
                    { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                    { 0.0, 0.0, 0.0, 8.8, 0.0, 5.5 },
                    { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },
                    { 0.0, 7.7, 1.1, 0.0, 0.0, 6.6 } };

    Matrix goldResult{ { 1.21, 0.0,   0.0,   0.0,   2.42, 0.0   },
                       { 0.0,  0.0,   0.0,   38.72, 0.0,  24.2  },
                       { 0.0,  0.0,   0.0,   0.0,   0.0,  0.0   },
                       { 0.0,  42.35, 6.05,  77.44, 0.0,  84.7  },
                       { 0.0,  0.0,   0.0,   0.0,   0.0,  0.0   },
                       { 0.0,  50.82, 32.67, 33.88, 0.0,  43.56 } };

    Matrix result = MatMul(matrixA, matrixB);

    ASSERT_EQ(result.size(), goldResult.size());
    ASSERT_EQ(result[0].size(), goldResult[0].size());

    for (size_t idx{ 0 }; idx < result.size(); ++idx) {
        for (size_t jdx{ 0 }; jdx < result[0].size(); ++jdx) {
            ASSERT_NEAR(result[idx][jdx], goldResult[idx][jdx], tolerance);
        }
    }

#ifdef DEBUG
    std::cout << "Result:" << std::endl;
    print(result);
    std::cout << std::endl;
    std::cout << "Gold Result:" << std::endl;
    print(goldResult);
    std::cout << std::endl;
#endif
}

TEST(Sparse_Matrix, Test_Sparse_Matrix_Miltiplication) {
    size_t rowsA{ 6 };
    size_t colsA{ 6 };
    std::vector<double> valueA{ 1.1, 2.2, 3.3, 4.4, 8.8, 5.5, 7.7, 1.1, 6.6 };
    std::vector<size_t> colIndexA{ 0, 4, 2, 3, 3, 5, 1, 2, 5 };
    std::vector<size_t> rowIndexA{ 0, 2, 4, 4, 6, 6, 9 };

    size_t rowsB{ 6 };
    size_t colsB{ 6 };
    std::vector<double> valueB{ 1.1, 2.2, 3.3, 4.4, 8.8, 5.5, 7.7, 1.1, 6.6 };
    std::vector<size_t> colIndexB{ 0, 4, 2, 3, 3, 5, 1, 2, 5 };
    std::vector<size_t> rowIndexB{ 0, 2, 4, 4, 6, 6, 9 };

    Matrix goldMatrix{ { 1.21, 0.0,   0.0,   0.0,   2.42, 0.0   },
                       { 0.0,  0.0,   0.0,   38.72, 0.0,  24.2  },
                       { 0.0,  0.0,   0.0,   0.0,   0.0,  0.0   },
                       { 0.0,  42.35, 6.05,  77.44, 0.0,  84.7  },
                       { 0.0,  0.0,   0.0,   0.0,   0.0,  0.0   },
                       { 0.0,  50.82, 32.67, 33.88, 0.0,  43.56 } };

    SparseMatrix sparseMatrixA{ rowsA, colsA, valueA, colIndexA, rowIndexA };
    SparseMatrix sparseMatrixB{ rowsB, colsB, valueB, colIndexB, rowIndexB };

    SparseMatrix goldResult(goldMatrix);

    SparseMatrix result = SparseMatMul(sparseMatrixA, sparseMatrixB);

#ifdef DEBUG
    sparseMatrixA.printMatrix();
    std::cout << std::endl;
    sparseMatrixB.printMatrix();
    std::cout << std::endl;

    std::cout << "Result:";
    std::cout << std::endl;
    result.printDefault();
    std::cout << std::endl;
    result.printMatrix();
    std::cout << std::endl;

    std::cout << "GoldResult:";
    std::cout << std::endl;
    goldResult.printDefault();
    std::cout << std::endl;
    goldResult.printMatrix();
    std::cout << std::endl;
#endif

    ASSERT_EQ(result, goldResult);
}

TEST(Sparse_Matrix, Test_Both_Matrix_Miltiplication) {
    Matrix matrixA{ { 1.1, 0.0, 0.0 },
                    { 0.0, 0.0, 3.3 },
                    { 0.0, 0.0, 0.0 },
                    { 4.4, 0.0, 0.0 },
                    { 0.0, 0.0, 0.0 },
                    { 0.0, 7.7, 1.1 } };

    SparseMatrix sparseMatrixA{ matrixA };

    Matrix matrixB{ { 0.0, 0.0, 0.0, 9.9 },
                    { 5.5, 0.0, 1.1, 0.0 },
                    { 0.0, 0.0, 0.0, 0.0 },
                    { 0.0, 3.3, 0.0, 8.8 } };

    SparseMatrix sparseMatrixB{ matrixB };

    SparseMatrix resultSparse = SparseMatMul(sparseMatrixA, sparseMatrixB);
    Matrix       result = MatMul(matrixA, matrixB);

    SparseMatrix resultToSparse{ result };

    ASSERT_EQ(resultToSparse, resultSparse);

#ifdef DEBUG
    sparseMatrixA.printMatrix();
    std::cout << std::endl;
    sparseMatrixB.printMatrix();
    std::cout << std::endl;

    std::cout << "Result:";
    std::cout << std::endl;
    resultToSparse.printDefault();
    std::cout << std::endl;
    resultToSparse.printMatrix();
    std::cout << std::endl;

    std::cout << "Result Sparse:";
    std::cout << std::endl;
    resultSparse.printDefault();
    std::cout << std::endl;
    resultSparse.printMatrix();
    std::cout << std::endl;
#endif
}

TEST(Sparse_Matrix, Test_Both_Matrix_Miltiplication_With_Rand_Gen) {
    Matrix matrixA{ generateMatrix(20, 20, 10) };
    Matrix matrixB{ generateMatrix(20, 20, 10) };

    SparseMatrix sparseMatrixA{ matrixA };
    SparseMatrix sparseMatrixB{ matrixB };

    SparseMatrix resultSparse = SparseMatMul(sparseMatrixA, sparseMatrixB);
    Matrix       result = MatMul(matrixA, matrixB);

    SparseMatrix resultToSparse{ result };
#ifdef DEBUG_LAST
    sparseMatrixA.printDefault();
    std::cout << std::endl;
    sparseMatrixA.printMatrix();
    std::cout << std::endl;
    sparseMatrixB.printDefault();
    std::cout << std::endl;
    sparseMatrixB.printMatrix();
    std::cout << std::endl;

    std::cout << "Result:";
    std::cout << std::endl;
    resultToSparse.printDefault();
    std::cout << std::endl;
    resultToSparse.printMatrix();
    std::cout << std::endl;

    std::cout << "Result Sparse:";
    std::cout << std::endl;
    resultSparse.printDefault();
    std::cout << std::endl;
    resultSparse.printMatrix();
    std::cout << std::endl;
#endif

    ASSERT_EQ(resultToSparse, resultSparse);
}

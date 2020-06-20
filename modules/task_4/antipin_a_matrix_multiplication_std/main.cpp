// Copyright 2020 Antipin Alexander
#include <gtest/gtest.h>
#include <vector>
#include "./matrix_multiplication.h"

// ------||------Matrix multiplication by std threads------||------

TEST(Matrix_multiplication, can_multiply_matrices) {
    std::vector<double> A = { 8.0, 5.0, 2.0, 4.0, 9.0, 1.0, 3.0 };
    std::vector<size_t> LI = { 5, 2, 0, 5, 3, 3, 4 };
    std::vector<size_t> LJ = { 0, 1, 2, 3, 4, 5, 7 };
    SparseMatrix<CCS> mat;
    mat.setMatrix(A, LI, LJ, 6);

    std::vector<double> A1 = { 2.0, 5.0, 8.0, 1.0, 4.0, 9.0, 1.0, 1.0, 3.0 };
    std::vector<size_t> LI1 = { 0, 2, 5, 0, 5, 3, 2, 3, 5 };
    std::vector<size_t> LJ1 = { 0, 0, 3, 3, 5, 6, 9 };
    SparseMatrix<CCS> mat1;
    mat1.setMatrix(A1, LI1, LJ1, 6);

    SparseMatrix<CCS> res;

    ASSERT_NO_THROW(getParallelSTDMatrixMultiplication(mat, mat1, &res, 6));
}

TEST(Matrix_multiplication, can_multiply_matrices_correct) {
    std::vector<double> A = { 8.0, 5.0, 2.0, 4.0, 9.0, 1.0, 3.0 };
    std::vector<size_t> LI = { 5, 2, 0, 5, 3, 3, 4 };
    std::vector<size_t> LJ = { 0, 1, 2, 3, 4, 5, 7 };
    SparseMatrix<CCS> mat;
    mat.setMatrix(A, LI, LJ, 6);

    std::vector<double> A1 = { 2.0, 5.0, 8.0, 1.0, 4.0, 9.0, 1.0, 1.0, 3.0 };
    std::vector<size_t> LI1 = { 0, 2, 5, 0, 5, 3, 2, 3, 5 };
    std::vector<size_t> LJ1 = { 0, 0, 3, 3, 5, 6, 9 };
    SparseMatrix<CCS> mat1;
    mat1.setMatrix(A1, LI1, LJ1, 6);

    SparseMatrix<CCS> res;

    getParallelSTDMatrixMultiplication(mat, mat1, &res, 4);

    EXPECT_NEAR(res.getElem(3, 1), 8, 0.000001);
    EXPECT_NEAR(res.getElem(4, 3), 12, 0.000001);
}

TEST(Matrix_multiplication, can_construct_usial_matrix_from_sparse) {
    std::vector<double> A1 = { 2.0, 5.0, 8.0, 1.0, 4.0, 9.0, 1.0, 1.0, 3.0 };
    std::vector<size_t> LI1 = { 0, 2, 5, 0, 5, 3, 2, 3, 5 };
    std::vector<size_t> LJ1 = { 0, 0, 3, 3, 5, 6, 9 };
    SparseMatrix<CCS> mat1;
    mat1.setMatrix(A1, LI1, LJ1, 6);

    std::vector<double> mat2;
    ASSERT_NO_THROW(constructMatrix(mat1, &mat2));
}

TEST(Matrix_multiplication, can_construct_usial_matrix_from_sparse_correct_1) {
    std::vector<double> A1 = { 2.0, 5.0, 8.0, 1.0, 4.0, 9.0, 1.0, 1.0, 3.0 };
    std::vector<size_t> LI1 = { 0, 2, 5, 0, 5, 3, 2, 3, 5 };
    std::vector<size_t> LJ1 = { 0, 0, 3, 3, 5, 6, 9 };
    SparseMatrix<CCS> mat1;
    mat1.setMatrix(A1, LI1, LJ1, 6);

    std::vector<double> mat2;
    constructMatrix(mat1, &mat2);

    EXPECT_EQ(0, mat2[2*6 + 0]);
    EXPECT_EQ(9, mat2[3*6 + 4]);
    EXPECT_EQ(8, mat2[5*6 + 1]);
}

TEST(Matrix_multiplication, can_construct_usial_matrix_from_sparse_correct_2) {
    SparseMatrix<CCS> mat1(10, 8);

    std::vector<double> mat2;
    constructMatrix(mat1, &mat2);

    EXPECT_NEAR(mat1.getElem(1, 3), mat2[1*10 + 3], 0.000001);
    EXPECT_NEAR(mat1.getElem(5, 5), mat2[5*10 + 5], 0.000001);
    EXPECT_NEAR(mat1.getElem(8, 6), mat2[8*10 + 6], 0.000001);
}

/*TEST(Matrix_multiplication, can_multiply_random_matrices) {
    SparseMatrix<CCS> mat(10000, 500);

    SparseMatrix<CCS> mat1(10000, 500);

    SparseMatrix<CCS> res;

    ASSERT_NO_THROW(getParallelSTDMatrixMultiplication(mat, mat1, &res));
}*/

TEST(Matrix_multiplication, can_multiply_same_as_usial_matrix) {
    SparseMatrix<CCS> mat1(100, 12);
    SparseMatrix<CCS> mat2(100, 12);
    SparseMatrix<CCS> mat3;

    std::vector<double> mat_1;
    std::vector<double> mat_2;
    std::vector<double> mat_3;
    constructMatrix(mat1, &mat_1);
    constructMatrix(mat2, &mat_2);
    matrixMultiplication(mat_1, 100, mat_2, &mat_3);
    getParallelSTDMatrixMultiplication(mat1, mat2, &mat3);
    EXPECT_NEAR(mat3.getElem(10, 10), mat_3[10 * 100 + 10], 0.000001);
    EXPECT_NEAR(mat3.getElem(25, 40), mat_3[25 * 100 + 40], 0.000001);
    EXPECT_NEAR(mat3.getElem(56, 81), mat_3[56 * 100 + 81], 0.000001);
    EXPECT_NEAR(mat3.getElem(73, 53), mat_3[73 * 100 + 53], 0.000001);
    EXPECT_NEAR(mat3.getElem(94, 4), mat_3[94 * 100 + 4], 0.000001);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

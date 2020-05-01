// Copyright 2020 Druzhinin Alexei

#include <gtest/gtest.h>
#include <omp.h>
#include "../../../modules/task_2/druzhinin_fox_algorithm/fox_algorithm.h"

#define SIZE_SMALL 3
#define SIZE_MEDIUM 10
#define SIZE_LARGE 50

TEST(Fox_Algorithm, Comparison_Equal_Matrixes_Correct) {
    // Arrange
    double a[SIZE_SMALL * SIZE_SMALL];  // matrix size = 3x3
    bool res;

    // Act
    fillMatrix(a, SIZE_SMALL);
    res = comparisonMatrixes(a, a, SIZE_SMALL);

    // Assert
    ASSERT_EQ(res, true);
}

TEST(Fox_Algorithm, Comparison_Unequal_Matrixes_Correct) {
    // Arrange
    double a[SIZE_SMALL * SIZE_SMALL];
    double b[SIZE_SMALL * SIZE_SMALL] = { 1.1, 1.1, 1.1,
                                        1.1, 1.1, 1.1,
                                        1.1, 1.1, 1.1 };
    bool res;

    // Act
    fillMatrix(a, SIZE_SMALL);
    res = comparisonMatrixes(a, b, SIZE_SMALL);

    // Assert
    ASSERT_EQ(res, false);
}

TEST(Fox_Algorithm, Default_Matrix_Multiplication_Correct) {
    // Arrange
    double a[SIZE_SMALL * SIZE_SMALL] = { 1.1, 1.1, 1.1,
                                        1.1, 1.1, 1.1,
                                        1.1, 1.1, 1.1 };
    double b[SIZE_SMALL * SIZE_SMALL] = { 1.2, 1.2, 1.2,
                                        1.2, 1.2, 1.2,
                                        1.2, 1.2, 1.2 };
    double res[SIZE_SMALL * SIZE_SMALL]{};
    double true_res[SIZE_SMALL * SIZE_SMALL] = { 3.96, 3.96, 3.96,
                                                3.96, 3.96, 3.96,
                                                3.96, 3.96, 3.96 };
    bool result;

    // Act
    defaultMatrixMult(a, b, SIZE_SMALL, res);
    result = comparisonMatrixes(res, true_res, SIZE_SMALL);

    // Assert
    ASSERT_EQ(result, true);
}

TEST(Fox_Algorithm, Parallel_Matrix_Multiplication_Correct_Small_Size) {
    // Arrange
    const int count_of_proc = 3;  // must be size % int(sqrt(count_of_proc)) = 0!
    double a[SIZE_SMALL * SIZE_SMALL] = { 1., 2., 3.,
                                        4., 5., 6.,
                                        7., 8., 9. };
    double b[SIZE_SMALL * SIZE_SMALL] = { 1., 2., 3.,
                                        4., 5., 6.,
                                        7., 8., 9. };
    double res[SIZE_SMALL * SIZE_SMALL]{};
    double true_res[SIZE_SMALL * SIZE_SMALL] = { 30.0, 36.0, 42.0,
                                                66.0, 81.0, 96.0,
                                                102.0, 126.0, 150.0 };
    bool result;

    // Act
    foxAlgorithm(a, b, res, SIZE_SMALL, count_of_proc);
    result = comparisonMatrixes(res, true_res, SIZE_SMALL);
    // Assert
    ASSERT_EQ(result, true);
}

TEST(Fox_Algorithm, Fox_and_Default_Matrix_Multiplication_Give_Identical_Result_Medium_Size) {
    // Arrange
    const int count_of_proc = 4;  // must be size % int(sqrt(count_of_proc)) = 0!
    double* a = new double[SIZE_MEDIUM * SIZE_MEDIUM];
    double* b = new double[SIZE_MEDIUM * SIZE_MEDIUM];
    double* def_res = new double[SIZE_MEDIUM * SIZE_MEDIUM]{};
    double* fox_res = new double[SIZE_MEDIUM * SIZE_MEDIUM]{};
    bool result;

    // Act
    fillMatrix(a, SIZE_MEDIUM);
    fillMatrix(b, SIZE_MEDIUM);
    defaultMatrixMult(a, b, SIZE_MEDIUM, def_res);
    foxAlgorithm(a, b, fox_res, SIZE_MEDIUM, count_of_proc);
    result = comparisonMatrixes(def_res, fox_res, SIZE_MEDIUM);

    // Assert
    ASSERT_EQ(result, true);
    delete[] a;
    delete[] b;
    delete[] def_res;
    delete[] fox_res;
}

TEST(Fox_Algorithm, Fox_and_Default_Matrix_Multiplication_Give_Identical_Result_Large_Size) {
    // Arrange
    const int count_of_proc = 4;  // must be size % int(sqrt(count_of_proc)) = 0!
    double* a = new double[SIZE_LARGE * SIZE_LARGE];
    double* b = new double[SIZE_LARGE * SIZE_LARGE];
    double* def_res = new double[SIZE_LARGE * SIZE_LARGE]{};
    double* fox_res = new double[SIZE_LARGE * SIZE_LARGE]{};
    bool result;

    // Act
    fillMatrix(a, SIZE_LARGE);
    fillMatrix(b, SIZE_LARGE);

    // double start_time = omp_get_wtime();
    defaultMatrixMult(a, b, SIZE_LARGE, def_res);
    // double def_time = omp_get_wtime() - start_time;
    // std::cout << "Default multiplication = " << def_time << std::endl;

    // start_time = omp_get_wtime();
    foxAlgorithm(a, b, fox_res, SIZE_LARGE, count_of_proc);
    // double fox_time = omp_get_wtime() - start_time;
    // std::cout << "Fox multiplication = " << fox_time << std::endl;
    // std::cout << "Speedup = " << def_time / fox_time << std::endl;

    result = comparisonMatrixes(def_res, fox_res, SIZE_LARGE);
    // Assert
    ASSERT_EQ(result, true);
    delete[] a;
    delete[] b;
    delete[] def_res;
    delete[] fox_res;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

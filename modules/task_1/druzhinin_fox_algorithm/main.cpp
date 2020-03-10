// Copyright 2020 Druzhinin Alexei

#include <gtest/gtest.h>
#include "../../../modules/task_1/druzhinin_fox_algorithm/fox_algorithm.h"

TEST(Fox_Algorithm, Comparison_Equal_Matrixes_Correct) {
    // Arrange
    double a[3 * 3];  // matrix size = 3
    bool res;

    // Act
    fillMatrix(a, 3);
    res = comparisonMatrixes(a, a, 3);

    // Assert
    ASSERT_EQ(res, true);
}

TEST(Fox_Algorithm, Comparison_Unequal_Matrixes_Correct) {
    // Arrange
    double a[3 * 3];
    double b[3 * 3] = {1.1, 1.1, 1.1,
                            1.1, 1.1, 1.1,
                            1.1, 1.1, 1.1};
    bool res;

    // Act
    fillMatrix(a, 3);
    res = comparisonMatrixes(a, b, 3);

    // Assert
    ASSERT_EQ(res, false);
}

TEST(Fox_Algorithm, Default_Matrix_Multiplication_Correct) {
    // Arrange
    double a[3 * 3] = {1.1, 1.1, 1.1,
                            1.1, 1.1, 1.1,
                            1.1, 1.1, 1.1};
    double b[3 * 3] = {1.2, 1.2, 1.2,
                            1.2, 1.2, 1.2,
                            1.2, 1.2, 1.2};
    double res[3 * 3]{};
    double true_res[3 * 3] = {3.96, 3.96, 3.96,
                            3.96, 3.96, 3.96,
                            3.96, 3.96, 3.96};
    bool result;

    // Act
    defaultMatrixMult(a, b, 3, res);
    result = comparisonMatrixes(res, true_res, 3);

    // Assert
    ASSERT_EQ(result, true);
}

TEST(Fox_Algorithm, Blocked_Matrix_Multiplication_Correct) {
    // Arrange
    double a[3 * 3] = {1.1, 1.1, 1.1,
                            1.1, 1.1, 1.1,
                            1.1, 1.1, 1.1};
    double b[3 * 3] = {1.2, 1.2, 1.2,
                            1.2, 1.2, 1.2,
                            1.2, 1.2, 1.2};
    double res[3 * 3]{};
    double true_res[3 * 3] = {3.96, 3.96, 3.96,
                            3.96, 3.96, 3.96,
                            3.96, 3.96, 3.96};
    bool result;

    // Act
    blockMatrixMult(a, b, 3, res);
    result = comparisonMatrixes(res, true_res, 3);

    // Assert
    ASSERT_EQ(result, true);
}

TEST(Fox_Algorithm, Blocked_and_Default_Matrix_Multiplication_Give_Identical_Result) {
    // Arrange
    double a[3 * 3];
    double b[3 * 3];
    double def_res[3 * 3]{};
    double block_res[3 * 3]{};
    bool result;

    // Act
    fillMatrix(a, 3);
    fillMatrix(b, 3);
    defaultMatrixMult(a, b, 3, def_res);
    blockMatrixMult(a, b, 3, block_res);
    result = comparisonMatrixes(def_res, block_res, 3);

    // Assert
    ASSERT_EQ(result, true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

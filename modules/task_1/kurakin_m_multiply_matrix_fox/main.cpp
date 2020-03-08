// Copyright 2020 Kurakin Mikhail
#include <gtest/gtest.h>
#include <omp.h>
#include <iostream>
#include "./multiply_matrix_fox.h"

TEST(Multiply_Matrix_Fox, Can_Multiplicate_Do_Properly_With_Wrong_Matrix) {
    matrix a;
    matrix b;
    uint aColSize = 2;
    uint aRowSize = 2;
    uint bRowSize = 3;  // bRow!=aCol

    a.resize(aRowSize);
    b.resize(bRowSize);
    for (uint i = 0; i < a.size(); i++) {
        a[i].resize(aColSize);
    }

    EXPECT_FALSE(canMultiplicate(a, b));
}

TEST(Multiply_Matrix_Fox, Can_Multiplicate_Do_Properly_With_Good_Matrix) {
    matrix a;
    matrix b;
    uint aColSize = 2;
    uint aRowSize = 2;
    uint bRowSize = 2;  // bRow==aCol

    a.resize(aRowSize);
    b.resize(bRowSize);
    for (uint i = 0; i < a.size(); i++) {
        a[i].resize(aColSize);
    }

    EXPECT_TRUE(canMultiplicate(a, b));
}

TEST(Multiply_Matrix_Fox, Prepare_Out_Matrix_Works_Properly) {
    matrix a;
    uint rowSize = 4;
    uint colSize = 4;
    prepareOutMatrix(&a, rowSize, colSize);

    for (uint i = 0; i < a.size(); i++) {
        for (uint j = 0; j < a[i].size(); j++) {
            EXPECT_DOUBLE_EQ(0, a[i][j]);
        }
    }
}

TEST(Multiply_Matrix_Fox, Can_Init_Matrix_With_Rand_Values) {
    matrix a;
    uint rowSize = 4;
    uint colSize = 4;

    EXPECT_TRUE(initMatrixRand(&a, rowSize, colSize));
}
TEST(Multiply_Matrix_Fox, Can_Multiply_Matrix_With_Simple_Method) {
    matrix a, b;
    matrix res;
    uint rowSize = 2;
    uint colSize = 2;

    prepareOutMatrix(&a, rowSize, colSize);
    prepareOutMatrix(&b, rowSize, colSize);

    for (uint i = 0; i < rowSize; i++) {  // init matrix
        for (uint j = 0; j < colSize; j++) {
            a[i][j] = (i * colSize) + (j + 1);
            b[i][j] = colSize * rowSize - ((i * colSize) + j);
        }
    }

    EXPECT_TRUE(simpleMaxtrixMultiply(a, b, &res));
}
TEST(Multiply_Matrix_Fox, Simple_Multiplication_Works_Properly) {
    matrix a, b;
    matrix expectRes, res;
    uint rowSize = 2;
    uint colSize = 2;

    prepareOutMatrix(&expectRes, rowSize, colSize);
    prepareOutMatrix(&a, rowSize, colSize);
    prepareOutMatrix(&b, rowSize, colSize);

    expectRes[0][0] = 8;
    expectRes[0][1] = 5;
    expectRes[1][0] = 20;
    expectRes[1][1] = 13;

    for (uint i = 0; i < rowSize; i++) {  // init matrix
        for (uint j = 0; j < colSize; j++) {
            a[i][j] = (i * colSize) + (j + 1);
            b[i][j] = colSize * rowSize - ((i * colSize) + j);
        }
    }

    simpleMaxtrixMultiply(a, b, &res);

    for (uint i = 0; i < rowSize; i++) {
        for (uint j = 0; j < colSize; j++) {
            EXPECT_DOUBLE_EQ(expectRes[i][j], res[i][j]);
        }
    }
}

TEST(Multiply_Matrix_Fox, Can_Use_Fox_Alg_Works_Right_With_Not_Square_Matrix) {
    matrix a, b;
    uint rowSize = 2;
    uint colSize = 3;

    prepareOutMatrix(&a, rowSize, colSize);
    prepareOutMatrix(&b, rowSize, colSize);

    EXPECT_FALSE(canUseFoxAlg(a, b));
}

TEST(Multiply_Matrix_Fox, Can_Use_Fox_Alg_Works_Right_With_Square_Matrix) {
    matrix a, b;
    uint rowSize = 3;
    uint colSize = 3;

    prepareOutMatrix(&a, rowSize, colSize);
    prepareOutMatrix(&b, rowSize, colSize);

    EXPECT_TRUE(canUseFoxAlg(a, b));
}
TEST(Multiply_Matrix_Fox, Fox_Alg_Matrix_Mult_Works_Properly) {
    matrix a, b;
    matrix expectRes, res;
    uint rowSize = 2;
    uint colSize = 2;

    prepareOutMatrix(&expectRes, rowSize, colSize);
    prepareOutMatrix(&a, rowSize, colSize);
    prepareOutMatrix(&b, rowSize, colSize);

    expectRes[0][0] = 8;
    expectRes[0][1] = 5;
    expectRes[1][0] = 20;
    expectRes[1][1] = 13;

    for (uint i = 0; i < rowSize; i++) {  // init matrix
        for (uint j = 0; j < colSize; j++) {
            a[i][j] = (i * colSize) + (j + 1);
            b[i][j] = colSize * rowSize - ((i * colSize) + j);
        }
    }

    algFoxMatrixMultiply(a, b, &res);

    for (uint i = 0; i < rowSize; i++) {
        for (uint j = 0; j < colSize; j++) {
            EXPECT_DOUBLE_EQ(expectRes[i][j], res[i][j]);
        }
    }
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

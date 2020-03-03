// Copyright 2020 Nazarov Vladislav
#include <gtest/gtest.h>
#include <vector>
#include "./sparce_matrix_multiplication.h"

TEST(Sparce_Matrix_Multiplication, Test_Matrix_Create) {
    std::vector<std::vector<cpx>> mat = {
        { cpx(10, -0.2), cpx(20, 1), cpx(0, 0),  cpx(0, 0),    cpx(0, 0),    cpx(0, 0) },
        { cpx(0, 0),     cpx(30, 6), cpx(0, 0),  cpx(40, 3.7), cpx(0, 0),    cpx(0, 0) },
        { cpx(0, 0),     cpx(0, 0),  cpx(50, 3), cpx(60, 8),   cpx(70, 2.5), cpx(0, 0) },
        { cpx(0, 0),     cpx(0, 0),  cpx(0, 0),  cpx(0, 0),    cpx(0, 0),    cpx(80, 3.9) },
    };
    CRS_Matrix matrix(mat);
    CRS_Matrix resMatrix(
        std::vector<cpx>({cpx(10, -0.2), cpx(20, 1), cpx(30, 6), cpx(40, 3.7), cpx(50, 3),
                          cpx(60, 8), cpx(70, 2.5), cpx(80, 3.9) }),
        std::vector<size_t>({0, 1, 1, 3, 2, 3, 4, 5}),
        std::vector<size_t>({0, 2, 4, 7, 8}));
    ASSERT_TRUE(matrix == resMatrix);
}

TEST(Sparce_Matrix_Multiplication, Test_Bad_Matrix) {
    std::vector<std::vector<cpx>> mat = {
        { cpx(10, -0.2), cpx(20, 1), cpx(0, 0),  cpx(0, 0),    cpx(0, 0),    cpx(0, 0) },
        { cpx(0, 0),  cpx(40, 3.7), cpx(0, 0),    cpx(0, 0) },
        { cpx(60, 8),   cpx(70, 2.5), cpx(0, 0) },
        { cpx(80, 3.9) },
    };
    ASSERT_ANY_THROW(CRS_Matrix matrix(mat));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

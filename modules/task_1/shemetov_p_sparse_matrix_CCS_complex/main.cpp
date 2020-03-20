#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "multi_matrix.h"

TEST(multi_matrix, TEST_FOR_FUN){
    SparseMatrixCCS test(5,5,10);
    mtxComplex vec = test.randomGenerateMatrix(0.8);
    test.Print(vec);
    vec = test.TransposeMatrix(vec);

    std::cout << "__________" << std::endl;

    test.TransposePrint(vec);
    SUCCEED();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
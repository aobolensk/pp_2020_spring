#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "multi_matrix.h"

TEST(multi_matrix, TEST_FOR_FUN){
    SparseMatrixCCS test(4,4,10);
    
    test.Print(test.randomGenerateMatrix(0.8));
    SUCCEED();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
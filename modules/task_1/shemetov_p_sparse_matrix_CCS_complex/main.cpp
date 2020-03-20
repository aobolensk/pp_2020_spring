#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "multi_matrix.h"

TEST(multi_matrix, TEST_FOR_FUN){
    
    mtxComplex vec = randomGenerateMatrix(5,5,0.8);
    SparseMatrixCCS test(vec);
    test.Print(vec);
    test.PrintCCS();
    

    std::cout << "__________" << std::endl;

    
    SUCCEED();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
// Copyright 2020 Isaev Ilya

#include <gtest/gtest.h>
#include <iostream>
#include "./matrix_mult.h"

TEST(Matrix_Mult, Matrix_Gen_Throws_On_Negative_Size) {
    ASSERT_ANY_THROW(getRandomMatrix(-1, 0));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

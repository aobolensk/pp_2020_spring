// Copyright 2020 Karin Timofey
#include <gtest/gtest.h>
#include "sparce_matrix.h"


int main(int argc, char **argv) {
    SparceMatrix Matrix(5, 15);
    Matrix.Print();
    SparceMatrix B = Matrix.Transpose();
    B.Print();
    SparceMatrix C = Matrix * B;
    C.Print();
    /*::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();*/
}

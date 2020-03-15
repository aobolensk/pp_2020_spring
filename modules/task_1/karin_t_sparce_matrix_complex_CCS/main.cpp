// Copyright 2020 Karin Timofey
#include <gtest/gtest.h>
#include "sparce_matrix.h"

int main(int argc, char **argv) {
   /* std::vector<std::complex<int>> val(7);
    val[0] = std::complex<int>(35, 0);
    val[1] = std::complex<int>(29, 0);
    val[2] = std::complex<int>(65, 0);
    val[3] = std::complex<int>(51, 0);
    val[4] = std::complex<int>(85, 0);
    val[5] = std::complex<int>(36, 0);
    val[6] = std::complex<int>(61, 0);
    SparceMatrix Matrix(3, 4, val, { 0, 1, 0, 1, 2, 0, 1}, {2, 5, 7});
    Matrix.Print();
    SparceMatrix B = Matrix.Transpose();
    B.Print();
    SparceMatrix C = Matrix * B;
    C.Print();*/
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
//{(35, 0), (29, 0), (65, 0), (51, 0), (85, 0), (36, 0), (61, 0)}
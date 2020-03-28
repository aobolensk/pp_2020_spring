// Copyright 2020 Iamshchikov Ivan
#include <gtest/gtest.h>
#include <omp.h>
#include <random>
#include <ctime>
#include <cmath>
#include "./sparse_matrix_mult.h"

TEST(sparse_matrix_mult_seq, can_create_matrix) {
    ASSERT_NO_THROW(CcsMatrix m(1, 1, 1));
}

TEST(sparse_matrix_mult_seq, throw_when_number_of_rows_are_not_positive) {
    ASSERT_ANY_THROW(CcsMatrix m(-3, 1, 1));
}

TEST(sparse_matrix_mult_seq, throw_when_number_of_columns_are_not_positive) {
    ASSERT_ANY_THROW(CcsMatrix m(1, 0, 1));
}

TEST(sparse_matrix_mult_seq, throw_when_number_of_elements_are_not_positive) {
    ASSERT_ANY_THROW(CcsMatrix m(1, 0, -3));
}

TEST(sparse_matrix_mult_seq, multiply_vector_by_vector) {
    CcsMatrix m1(5, 1, 2);
    m1.value = { 2, 1};
    m1.row = { 1, 2 };
    m1.colIndex = { 0, 2 };

    CcsMatrix m2(1, 4, 1);
    m2.value = { 3 };
    m2.row = { 0 };
    m2.colIndex = { 0, 0, 0, 1, 1};

    CcsMatrix m3(5, 4, 2);
    m3.value = { 6, 3};
    m3.row = { 1, 2 };
    m3.colIndex = { 0, 0, 0, 2, 2 };

    EXPECT_EQ(m3, matrixMultiplicate(&m1, &m2));
}

TEST(sparse_matrix_mult_seq, multiply_matrix_by_vector) {
    CcsMatrix m1(4, 5, 6);
    m1.value = { 1, 3, 2, 5, 4, 8};
    m1.row = { 0, 3, 1, 2, 3, 0};
    m1.colIndex = { 0, 1, 2, 3, 5, 6 };

    CcsMatrix m2(5, 1, 2);
    m2.value = { 2, 1 };
    m2.row = { 1, 2 };
    m2.colIndex = { 0, 2 };

    CcsMatrix m3(4, 1, 2);
    m3.value = { 2, 6 };
    m3.row = { 1, 3 };
    m3.colIndex = { 0, 2};

    EXPECT_EQ(m3, matrixMultiplicate(&m1, &m2));
}

TEST(sparse_matrix_mult_seq, multiply_vector_by_matrix) {
    CcsMatrix m1(1, 4, 2);
    m1.value = { 2, 1 };
    m1.row = { 0, 0 };
    m1.colIndex = { 0, 0, 1, 2, 2 };

    CcsMatrix m2(4, 5, 6);
    m2.value = { 1, 3, 2, 5, 4, 8 };
    m2.row = { 0, 3, 1, 2, 3, 0 };
    m2.colIndex = { 0, 1, 2, 3, 5, 6 };

    CcsMatrix m3(1, 5, 2);
    m3.value = { 4, 5 };
    m3.row = { 0 , 0 };
    m3.colIndex = { 0, 0, 0, 1, 2, 2 };

    EXPECT_EQ(m3, matrixMultiplicate(&m1, &m2));
}

TEST(sparse_matrix_mult_seq, multiply_matrix_by_matrix) {
    CcsMatrix m1(4, 5, 6);
    m1.value = { 1, 3, 2, 5, 4, 8 };
    m1.row = { 0, 3, 1, 2, 3, 0 };
    m1.colIndex = { 0, 1, 2, 3, 5, 6 };

    CcsMatrix m2(5, 3, 5);
    m2.value = { 1, 6, 3, 7, 2 };
    m2.row = { 0, 4, 3, 1, 4 };
    m2.colIndex = { 0, 2, 3, 5 };

    CcsMatrix m3(4, 3, 5);
    m3.value = { 49, 15, 12, 16, 21};
    m3.row = { 0, 2, 3, 0, 3 };
    m3.colIndex = { 0, 1, 3, 5 };

    EXPECT_EQ(m3, matrixMultiplicate(&m1, &m2));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Copyright 2020 Golubeva Anna

#include <gtest/gtest.h>
#include <omp.h>
#include "../../../modules/task_2/golubeva_a_fox_mult/fox.h"


TEST(Fox_Mult, cant_create_matrix_with_negative_size) {
    ASSERT_ANY_THROW(randMatrix(-10));
}

TEST(Fox_Mult, can_create_random_matrix) {
  ASSERT_NO_THROW(randMatrix(10));
}

TEST(Fox_Mult, cant_do_simple_mult_with_different_size) {
  Matrix A = randMatrix(9);
  Matrix B = randMatrix(10);

  ASSERT_ANY_THROW(simpleMult(A, B));
}

TEST(Fox_Mult, cant_do_fox_mult_with_different_size) {
  Matrix A = randMatrix(7);
  Matrix B = randMatrix(9);

ASSERT_ANY_THROW(foxMult(A, B, 3));
}

TEST(Fox_Mult, res_simple_mult_is_correct) {
  Matrix A = { {1.1, 1.2, 1.3},
               {2.4, 2.5, 2.6},
               {3.7, 3.8, 3.9} };
  Matrix B = { {4.1, 4.2, 4.3},
               {5.4, 5.5, 5.6},
               {6.7, 6.8, 6.9} };
  Matrix C = { {19.7, 20.06, 20.42},
               {40.76, 41.51, 42.26},
               {61.82, 62.96, 64.1} };
  Matrix res = simpleMult(A, B);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_NEAR(res[i][j], C[i][j], 0.001);
    }
  }
}

TEST(Fox_Mult, res_fox_mult_is_correct) {
  Matrix A = { {1.1, 1.2, 1.3},
               {2.4, 2.5, 2.6},
               {3.7, 3.8, 3.9} };
  Matrix B = { {4.1, 4.2, 4.3},
               {5.4, 5.5, 5.6},
               {6.7, 6.8, 6.9} };
  Matrix C = { {19.7, 20.06, 20.42},
               {40.76, 41.51, 42.26},
               {61.82, 62.96, 64.1} };
  Matrix res = foxMult(A, B, 2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_NEAR(res[i][j], C[i][j], 0.001);
    }
  }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

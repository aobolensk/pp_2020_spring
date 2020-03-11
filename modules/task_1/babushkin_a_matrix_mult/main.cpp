// Copyright 2020 Babushkin Alexey

#include <iostream>

#include "../../task_1/babushkin_a_matrix_mult/matrix_mult.h"

int main(int argc, char const *argv[]) {
  mtrxmult::Matrix test({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);

  std::cout << test.to_string() << std::endl;
  return 0;
}

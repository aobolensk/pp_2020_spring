// Copyright 2020 Golovanova Elena

#ifndef MODULES_TASK_2_GOLOVANOVA_E_SOBELE_OMP_SOBELE_H_
#define MODULES_TASK_2_GOLOVANOVA_E_SOBELE_OMP_SOBELE_H_

#include <algorithm>
#include <random>
#include <ctime>
#include <vector>
#include <iostream>

class image {
 public:
  int width = 0, height = 0;
  std::vector<int> matrix;
  image(int _width, int _height);
};

image getRandomMatrix(int _width, int _height);
image SequenceMainFunction(image Start);
image OmpMainFunction(image Start);

#endif  //  MODULES_TASK_2_GOLOVANOVA_E_SOBELE_OMP_SOBELE_H_

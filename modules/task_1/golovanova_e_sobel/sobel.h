// Copyright 2020 Golovanova Elena

#ifndef MODULES_TASK_1_GOLOVANOVA_E_SOBEL_SOBEL_H_
#define MODULES_TASK_1_GOLOVANOVA_E_SOBEL_SOBEL_H_

#include <vector>
#include <iostream>

class image {
 private:
  int width = 0, height = 0;
  std::vector<int> matrix;
 public:
  image(int _width, int _height, std::vector<int> _matrix);
  image(int _width, int _height);
  std::vector<int> GetMatrix()const;
  void GetRandom();
  virtual image& operator=(const image& Example);
  image SeqSobel();
};

#endif  // MODULES_TASK_1_GOLOVANOVA_E_SOBEL_SOBEL_H_

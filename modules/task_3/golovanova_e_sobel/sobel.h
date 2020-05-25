// Copyright 2020 Golovanova Elena

#ifndef MODULES_TASK_3_GOLOVANOVA_E_SOBEL_SOBEL_H_
#define MODULES_TASK_3_GOLOVANOVA_E_SOBEL_SOBEL_H_

#include <vector>
#include <iostream>

class image {
 private:
  int width = 0, height = 0;
  std::vector<int> matrix;
 public:
  image();
  image(int _width, int _height, std::vector<int> _matrix);
  image(int _width, int _height);
  std::vector<int> GetMatrix()const;
  image GetRandom(int _width, int _height);
  virtual image& operator=(const image& Example);
  image SeqSobel();
  image TbbSobel();
};

#endif  // MODULES_TASK_3_GOLOVANOVA_E_SOBEL_SOBEL_H_

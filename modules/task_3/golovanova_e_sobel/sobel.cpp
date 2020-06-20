// Copyright 2020 Golovanova Elena
#include <tbb/tbb.h>
#include <algorithm>
#include <random>
#include <vector>
#include <ctime>
#include <iostream>
#include "../../../modules/task_3/golovanova_e_sobel/sobel.h"

image::image(int _width, int _height, std::vector<int>_matrix) {
  if ((_width <= 0) || (_height <= 0))
    throw "Uncorrect size";
  width = _width;
  height = _height;
  matrix.resize(_width * _height);
  for (int i = 0; i < _width * _height; i++)
    matrix[i] = _matrix[i];
}

image::image(int _width, int _height) {
  if ((_width <= 0) || (_height <= 0))
    throw "Uncorrect size";
  width = _width;
  height = _height;
  matrix.resize(_width * _height, 0);
}

std::vector<int> image::GetMatrix()const {
  return matrix;
}

image image::GetRandom(int _width, int _height) {
  image random(_width, _height);
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  for (int i = 0; i < _width; i++)
    for (int j = 0; i < _height; i++)
      random.matrix[i * _width + j] = gen() % 256;
  return random;
}

image& image::operator=(const image& Example) {
  if (this != &Example) {
    width = Example.width;
    height = Example.height;
    for (int i = 0; i < height*width; i++)
      matrix[i] = Example.matrix[i];
  }
  return *this;
}


image image::SeqSobel() {
  std::vector<int> Gx, Gy;
  Gx.resize(9);
  Gy.resize(9);
  Gx = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
  Gy = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
  image result(width-2, height-2);
  int i = 0;
  while (i <= width-3) {
    int j = 0;
    while (j <= height-3) {
      int ind = i * height + j;
      int X = 0, Y = 0, Ind_G = 0;
      int a = 0;
      while (a < 3) {
        int b = 0;
        while (b < 3) {
          X = Gx[Ind_G] * matrix[(i + a) * height + j + b] + X;
          Y = Gy[Ind_G] * matrix[(i + a) * height + j + b] + Y;
          Ind_G++;
          b++;
        }
        a++;
      }
      if (sqrt(X * X + Y * Y) > 255)
        result.matrix[ind] = 255;
      else
        result.matrix[ind] = sqrt(X * X + Y * Y);
      j++;
    }
    i++;
  }
  return result;
}

image image::TbbSobel() {
  std::vector<int> Gx, Gy;
  Gx.resize(9);
  Gy.resize(9);
  Gx = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
  Gy = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
  image result(width - 2, height - 2);
  tbb::parallel_for(tbb::blocked_range<int>{0, width - 2}, [&](const tbb::blocked_range<int>& rows) {
    for (int i = rows.begin(); i < rows.end(); i++) {
      for (int j = 0; j <= height - 3; j++) {
        int ind = i * height + j;
        int X = 0, Y = 0, Ind_G = 0;
        for (int a = 0; a < 3; a++) {
          for (int b = 0; b < 3; b++) {
            X = Gx[Ind_G] * matrix[(i + a) * height + j + b] + X;
            Y = Gy[Ind_G] * matrix[(i + a) * height + j + b] + Y;
            Ind_G++;
          }
        }
        if (sqrt(X * X + Y * Y) > 255)
          result.matrix[ind] = 255;
        else
          result.matrix[ind] = sqrt(X * X + Y * Y);
        }
      }
  });
  return result;
}

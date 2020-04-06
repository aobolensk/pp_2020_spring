// Copyright 2020 Golovanova Elena
#include <algorithm>
#include <random>
#include <ctime>
#include <vector>
#include <iostream>
#include "../../../modules/task_1/golovanova_e_sobele/sobele.h"

image::image(int _width, int _height) {
  if ((_width <= 0) || (_height <= 0))
    throw "Uncorrect size";
  width = _width;
  height = _height;
  matrix.resize(_width * _height);
  for (int i = 0; i < _width * _height; i++)
    matrix[i] = 0;
}

image getRandomMatrix(int _width, int _height) {
  if ((_width <= 0) || (_height <= 0))
    throw "Uncorrect size";
  image Ex1(_width, _height);
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  for (int i = 0; i < _width; i++)
    for (int j = 0; i < _height; i++)
      Ex1.matrix[i * _width + j] = gen() % 256;
  return Ex1;
}

image MainFunction(image Start) {
  if ((Start.height <= 0) || (Start.matrix.empty()) || (Start.width <= 0))
    throw "Uncorrect image";
  std::vector<int> Gx, Gy;
  Gx.resize(9);
  Gy.resize(9);
  Gx = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
  Gy = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
  image result(Start.width, Start.height);
  int i = 1, j = 1;
  while (i < Start.width - 1) {
    while (j < Start.height - 1) {
      int ind = i * Start.height + j;
      int X = 0, Y = 0, Ind_G = 0;
      int a = -1, b = -1;
      while (a < 2) {
        while (b < 2) {
          X = Gx[Ind_G] * Start.matrix[(i + a) * Start.height + j + b] + X;
          Y = Gy[Ind_G] * Start.matrix[(i + a) * Start.height + j + b] + Y;
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

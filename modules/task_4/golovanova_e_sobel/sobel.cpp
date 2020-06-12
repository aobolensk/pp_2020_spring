// Copyright 2020 Golovanova Elena
#include <algorithm>
#include <random>
#include <vector>
#include <thread>
#include <ctime>
#include <iostream>
#include "../../../modules/task_4/golovanova_e_sobel/sobel.h"

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

void image::GetRandom() {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  for (int i = 0; i < this->width * this->height; i++)
    this->matrix[i] = gen() % 256;
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
  image result(this->width-2, this->height-2);
  int i = 0;
  while (i <= this->width-3) {
    int j = 0;
    while (j <= this->height-3) {
      int ind = i * (this->height-2) + j;
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

image image::ThreadSobel(int countThreads) {
  std::vector<int> Gx, Gy;
  Gx.resize(9);
  Gy.resize(9);
  Gx = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
  Gy = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
  image result(width - 2, height - 2);
  std::thread* threads = new std::thread[countThreads];
  if (countThreads < width - 3)
    throw "Uncorrert count threads";
  int delta = (width - 3) / countThreads;
  for (int idThread = 0; idThread < countThreads; idThread++) {
    threads[idThread] = std::thread([idThread, delta, &Gx, &Gy, &result, this, threads]() {
      for (int i = idThread * delta; i <= (idThread + 1) * delta; i++) {
        for (int j = 0; j <= height - 3; j++) {
          int ind = i * (height - 2) + j;
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
      threads[idThread].join();
      });
    delete[] threads;
    if (delta != 0) {
      for (int i = countThreads * delta; i <= (width - 3); i++)
        for (int j = 0; j <= height - 3; j++) {
          int ind = i * (height - 2) + j;
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
  }
  return result;
}


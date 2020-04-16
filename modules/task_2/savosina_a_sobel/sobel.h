// Copyright 2020 Savosina Aleksandra


#ifndef MODULES_TASK_2_SAVOSINA_A_SOBEL_SOBEL_H_
#define MODULES_TASK_2_SAVOSINA_A_SOBEL_SOBEL_H_


#include <vector>
#include <random>
#include <ctime>
#include <iostream>

struct img {
  std::vector<int> pict;
  int height;
  int width;
  int size;

  img() {
    height = width = size = 0;
  }

  img(int _height, int _width) {
    height = _height;
    width = _width;
    size = height * width;
    for (int i = 0; i < size; i++)
      pict[i] = 0;
  }

  img(int _height, int _width, std::vector<int> _pict) {
    height = _height;
    width = _width;
    size = height * width;
    pict = _pict;
  }

  img(const img& _img) {
    size = _img.size;
    height = _img.height;
    width = _img.width;
    pict = _img.pict;
  }

  bool operator== (const img& _img) const {
    if (pict == _img.pict && height == _img.height
      && width == _img.width && size == _img.size)
      return true;
    return false;
  }

  bool operator!= (const img& _img) const {
    return !(*this == _img);
  }

  void getRandom(int _height, int _width) {
    height = _height;
    width = _width;
    size = height * width;
    pict.resize(size);

    for (int i = 0; i < size; i++) {
      std::mt19937 gen;
      gen.seed(static_cast<unsigned int>(time(0)));
      for (int i = 0; i < size; i++) { pict[i] = gen() % 256; }
    }
  }
};

using mainImage = img;
using mask = img;

mask sobel(const mask& _img);
mask omp(const mask& _img);

#endif  // MODULES_TASK_2_SAVOSINA_A_SOBEL_SOBEL_H_

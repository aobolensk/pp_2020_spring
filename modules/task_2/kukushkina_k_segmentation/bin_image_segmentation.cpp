// Copyright 2020 Kukushkina Ksenia
#include "../../modules/task_2/kukushkina_k_segmentation/bin_image_segmentation.h"
#include <omp.h>
#include <vector>
#include <random>
#include <ctime>
#include <iostream>

static int offset = 0;

std::vector<int> Generate_pic(std::size_t w, std::size_t h) {
  if (h <= 0 || w <= 0) throw "Trying to generate negative-dim pic";
  std::vector<int> pic(h * w);
  std::mt19937 gen;
  gen.seed(static_cast<unsigned>(time(0)) + offset++);
  #pragma omp parallel for
  for (int i = 0; i < static_cast<int>(h * w); i++) {
    pic[i] = gen() % 2;
  }
  return pic;
}

std::vector<int> Segmentation(const std::vector<int> &source, std::size_t w) {
  std::vector<int> res;
  std::vector<int> segStart;  // first line of segment, for non-recursive recoloring
  segStart.push_back(-1);  // start of 0 seg
  segStart.push_back(-1);  // start of 1 seg
  for (size_t i = 0; i < source.size(); i++) {
    res.push_back(source[i]);
  }
  int color = 1;
  if (res[0] == 1) {
    res[0] = ++color;
    segStart.push_back(0);
  }
  for (size_t i = 1; i < w; i++) {  // first line segmentation
    if (res[i] == 0) continue;  // empty space skipping
    if (res[i - 1] != 0) {
      res[i] = res[i - 1];
    } else {
      res[i] = ++color;  // new segment starting
      segStart.push_back(0);
    }
  }
  #pragma omp parallel for
  for (int i = w; i < static_cast<int>(res.size()); i++) {
    if (res[i] == 0) continue;  // empty space skipping
    if (i % w == 0) {  // left edge segmentation
      if (res[i - w] != 0) {
        res[i] = res[i - w];  // adding to existing segment
      } else {
        #pragma omp critical(new_segment)
        {
          res[i] = ++color;  // new segment starting
          segStart.push_back(i / w);
        }
      }
    } else if (res[i - 1] == 0 && res[i - w] == 0) {
      #pragma omp critical(new_segment)
      {
        res[i] = ++color;  // new segment starting
        segStart.push_back(i / w);
      }
    } else if (res[i - 1] != 0 && res[i - w] == 0) {
      res[i] = res[i - 1];  // adding to left segment
    } else if (res[i - 1] == 0 && res[i - w] != 0) {
      res[i] = res[i - w];  // adding to upper segment
    } else if (res[i - 1] != 0 && res[i - w] != 0) {
      res[i] = res[i - 1];  // adding to left segment
      if (res[i - w] != res[i - 1]) {  // recoloring upper segment
        int oldColor = res[i - w];
        int newColor = res[i - 1];
        if (segStart[oldColor] < segStart[newColor])
          segStart[newColor] = segStart[oldColor];  // refreshing current seg start
        for (int j = static_cast<int>(w * segStart[oldColor]); j < i; j++) {
          if (res[j] == oldColor)
            res[j] = newColor;
        }
      }
    }
  }
  return res;
}

void Output(const std::vector<int>& source, std::size_t w) {
  for (size_t i = 0; i < source.size(); i++) {
    if (i % w == 0)
      std::cout << std::endl;
    std::cout << source[i] << " ";
  }
  std::cout << std::endl;
}

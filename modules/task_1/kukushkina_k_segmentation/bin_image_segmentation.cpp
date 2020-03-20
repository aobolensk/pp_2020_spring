// Copyright 2020 Kukushkina Ksenia
#include "../../modules/task_1/kukushkina_k_segmentation/bin_image_segmentation.h"
#include <vector>
#include <random>
#include <ctime>
#include <iostream>

static int offset = 0;

std::vector<int> Generate_pic(size_t w, size_t h) {
  if (h <= 0 || w <= 0) throw "Trying to generate negative-dim pic";
  std::vector<int> pic(h * w);
  std::mt19937 gen;
  gen.seed(static_cast<unsigned>(time(0)) + offset++);
  for (size_t i = 0; i < h * w; i++) {
    pic[i] = gen() % 2;
  }
  return pic;
}

void recolor(std::vector<int>* vec, size_t pix, int color, size_t w) {
  int old = (*vec)[pix];
  if (old == 0) throw "Trying to recolor empty space";
  (*vec)[pix] = color;
  if (pix % w != 0 && (*vec)[pix - 1] != 0 && (*vec)[pix - 1] != color)
    recolor(vec, pix - 1, color, w);
  if ((pix + 1) % w != 0 && (*vec)[pix + 1] != 0 && (*vec)[pix - 1] != color)
    recolor(vec, pix + 1, color, w);
  if (pix >= w && (*vec)[pix - w] != 0 && (*vec)[pix - 1] != color)
    recolor(vec, pix - w, color, w);
  if (pix <= (*vec).size() - w && (*vec)[pix + w] != 0 && (*vec)[pix - 1] != color)
    recolor(vec, pix + w, color, w);
}

std::vector<int> Segmentation(const std::vector<int> &source, size_t w) {
  std::vector<int> res;
  for (size_t i = 0; i < source.size(); i++) {
    res.push_back(source[i]);
  }
  int color = 1;
  if (res[0] == 1) res[0] = ++color;
  for (size_t i = 1; i < w; i++) {  // first line segmentation
    if (res[i] == 0) continue;  // empty space skipping
    if (res[i - 1] != 0)
      res[i] = res[i - 1];
    else
      res[i] = ++color;  // new segment starting
  }
  for (size_t i = w; i < res.size(); i++) {
    if (res[i] == 0) continue;  // empty space skipping
    if (i % w == 0) {  // left edge segmentation
      if (res[i - w] != 0)
        res[i] = res[i - w];  // adding to existing segment
      else
        res[i] = ++color;  // new segment starting
    } else if (res[i - 1] == 0 && res[i - w] == 0) {
      res[i] = ++color;  // new segment starting
    } else if (res[i - 1] != 0 && res[i - w] == 0) {
      res[i] = res[i - 1];  // adding to left segment
    } else if (res[i - 1] == 0 && res[i - w] != 0) {
      res[i] = res[i - w];  // adding to upper segment
    } else if (res[i - 1] != 0 && res[i - w] != 0) {
      res[i] = res[i - 1];  // adding to left segment
      if (res[i - w] != res[i - 1]) {
        //std::cout << "recolor " << i - w << std::endl;
        //recolor(&res, i - w, color, w);  // recoloring upper segment
      }
    }
  }
  return res;
}
void Output(const std::vector<int>& source, size_t w) {
  for (size_t i = 0; i < source.size(); i++) {
    if (i % w == 0)
      std::cout << std::endl;
    std::cout << source[i] << " ";
  }
  std::cout << std::endl;
}

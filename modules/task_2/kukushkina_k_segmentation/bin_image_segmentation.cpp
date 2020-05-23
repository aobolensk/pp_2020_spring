// Copyright 2020 Kukushkina Ksenia
#include "../../modules/task_2/kukushkina_k_segmentation/bin_image_segmentation.h"
#include <omp.h>
#include <vector>
#include <random>
#include <ctime>
#include <iostream>

static std::size_t offset = 0;

std::vector<std::size_t> Generate_pic(std::size_t w, std::size_t h) {
  if (h <= 0 || w <= 0) throw "Trying to generate negative-dim pic";
  std::vector<std::size_t> pic(h * w);
  std::mt19937 gen;
  gen.seed(static_cast<unsigned>(time(0)) + offset++);
  #pragma omp parallel for
  for (int i = 0; i < static_cast<int>(h * w); i++) {
    pic[i] = gen() % 2;
  }
  return pic;
}

std::vector<std::size_t> Segmentation(const std::vector<std::size_t> &source, std::size_t w) {
  std::vector<std::size_t> res(source);
  std::vector<std::size_t> tnc;
  tnc.push_back(0);
  tnc.push_back(1);
  std::size_t color = 1;

  //  Segmentation
  if (res[0] == 1) {  // first elem
    #pragma omp critical(segment)
    {
      color++;
      res[0] = color;
      tnc.push_back(color);
    }
  }

  for (std::size_t i = 1; i < w; i++) {  // first row
    if (res[i] == 0)  // empty cell
      continue;
    if (res[i - 1] == 0 || i % w == 0) {  // new seg
  #pragma omp critical(segment)
      {
        color++;
        res[i] = color;
        tnc.push_back(color);
      }
      continue;
    }
    res[i] = res[i - 1];
  }

  #pragma omp parallel for schedule(dynamic, w)
  for (int i = w; i < static_cast<int>(res.size()); i++) {  // other rows
    if (res[i] == 0)  // empty cell
      continue;
    if ((res[i - 1] < 2  || i % w == 0) && res[i - w] < 2) {  // new seg
    #pragma omp critical(segment)
      {
        color++;
        res[i] = color;
        tnc.push_back(color);
      }
      continue;
    }
    if (res[i - 1] < 2) {  // only upper is colored
      res[i] = res[i - w];
      continue;
    }
    if (res[i - w] < 2) {  // only left is colored
      res[i] = res[i - 1];
      continue;
    }
    // both upper & left are colored
    std::size_t leftcolor = res[i - 1];
    res[i] = leftcolor;
  }

  // Recoloring preprocessing
  for (std::size_t i = w; i < res.size(); i++) {
    if (res[i] == 0 || res[i - w] == 0)
      continue;
    std::size_t cur = tnc[res[i]];
    std::size_t up = tnc[res[i - w]];
    for (std::size_t j = 2; j < tnc.size(); j++) {
      if (tnc[j] == cur)
        tnc[j] = up;
    }
  }

  // Recoloring
  #pragma omp parallel for
  for (int i = 0; i < static_cast<int>(res.size()); i++)
    res[i] = tnc[res[i]];

  return res;
}

void Output(const std::vector<std::size_t>& source, std::size_t w) {
  for (size_t i = 0; i < source.size(); i++) {
    if (i % w == 0)
      std::cout << std::endl;
    std::cout << source[i] << " ";
  }
  std::cout << std::endl;
}

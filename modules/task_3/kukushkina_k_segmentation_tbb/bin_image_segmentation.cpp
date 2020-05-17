// Copyright 2020 Kukushkina Ksenia
#include "../../modules/task_3/kukushkina_k_segmentation_tbb/bin_image_segmentation.h"
#include <vector>
#include <random>
#include <ctime>
#include <iostream>

using namespace tbb;

static int offset = 0;

std::vector<int> Generate_pic(std::size_t w, std::size_t h) {
  if (h <= 0 || w <= 0) throw "Trying to generate negative-dim pic";
  std::vector<int> pic(h * w, 0);
  std::mt19937 gen;
  gen.seed(static_cast<unsigned>(time(0)) + offset++);
  int segcount = gen() % w + 1;
  segcount *= 2;
  for (size_t i = 0; i < segcount; i++) {
    int curx, cury;
    curx = gen() % w;
    cury = gen() % h;
    int segsize = gen() % (h * w / segcount);
    for (size_t j = 0; j < segsize; j++)
    {
      pic[curx + w * cury] = 1;
      int dir = gen() % 4;
      switch (dir) {
      case 0:
        if (cury != 0) {
          if (pic[curx + (w - 1) * cury] == 0) {
            cury--;
            break;
          }
        }
      case 1:
        if (curx != 0) {
          if (pic[curx - 1 + w * cury] == 0) {
            curx--;
            break;
          }
        }
      case 2:
        if (cury != h - 1) {
          if (pic[curx + (w + 1) * cury] == 0) {
            cury++;
            break;
          }
        }
      case 3:
        if (curx != w - 1) {
          if (pic[curx + 1 + w * cury] == 0) {
            curx++;
            break;
          }
        }
      }
    }
  }
  return pic;
}

void Segmentation::operator() (const tbb::blocked_range<int>& r) const {
  spin_mutex::scoped_lock lock;
  spin_mutex::scoped_lock lock1;
  (*workingThreads)++;
  int begin = r.begin();
  int end = r.end();

}

void Output(const std::vector<int>& source, std::size_t w) {
  for (size_t i = 0; i < source.size(); i++) {
    if (i % w == 0)
      std::cout << std::endl;
    std::cout << source[i] << " ";
  }
  std::cout << std::endl;
}

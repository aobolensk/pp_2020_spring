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
  int segcount = gen() % w;
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

  if ((*result)[begin] == 1) {  // first elem
    lock.acquire(mut_new_seg);
    (*color)++;
    (*newColor).push_back(*color + 2);
    (*result)[begin] = *color + 2;
    lock.release();
  }

  for (int i = 1; i < w; i++) {  // first line
    if ((*result)[begin * w + i] == 0)
      continue;
    if ((*result)[begin * w + i - 1] == 0) {
      lock.acquire(mut_new_seg);
      (*color)++;
      (*newColor).push_back(*color + 2);
      (*result)[begin * w + i] = *color + 2;
      lock.release();
      continue;
    }
    (*result)[begin * w + i] = (*result)[begin * w + i - 1];
  }
  
  for (int i = begin + 1; i != end; i++) {  // rows
    if ((*result)[i * w] != 0) {  // left pix is coloured
      if ((*result)[i * w - w] == 0) {  // upper is blank
        lock.acquire(mut_new_seg);
        (*color)++;
        (*newColor).push_back(*color + 2);
        (*result)[i * w] = *color + 2;
        lock.release();
      } else {  // upper is coloured
        (*result)[i * w] = (*result)[i * w - w];
      }
    }

    for (int j = 1; j < w; j++) {  // cols
      if ((*result)[i * w + j] == 0)
        continue;
      int upcolor = (*result)[i * w - w + j];
      int leftcolor = (*result)[i * w - 1 + j];
      if (leftcolor == 0 && upcolor == 0) {
        lock.acquire(mut_new_seg);
        (*color)++;
        (*newColor).push_back(*color + 2);
        (*result)[i * w + j] = *color + 2;
        lock.release();
        continue;
      }
      if (leftcolor == 0 && upcolor != 0
        || leftcolor == upcolor) {
        (*result)[i * w + j] = upcolor;
        continue;
      }
      if (leftcolor != 0 && upcolor == 0) {
        (*result)[i * w + j] = leftcolor;
        continue;
      }

      (*result)[i * w + j] = upcolor;  // recoloring preparing
      lock1.acquire(mut_recolor);
      leftcolor = (*newColor)[leftcolor];
      for (int k = 0; k < (*newColor).size(); k++)
        if ((*newColor)[k] == leftcolor)
          (*newColor)[k] = upcolor;
      lock1.release();
    }
  }

  if (end == h) return;

  for (int i = 0; i < w; i++) {  // first row of next block
    if ((*result)[end * w + i] == 0 || (*result)[end * w - w + i] == 0)
      continue;
    int curcolor = (*result)[end * w + i];
    int upcolor = (*result)[end * w - w + i];
    lock1.acquire(mut_recolor);
    curcolor = (*newColor)[curcolor];
    for (int k = 0; k < (*newColor).size(); k++)
      if ((*newColor)[k] == curcolor)
        (*newColor)[k] = upcolor;
    lock1.release();
  }

  (*workingThreads)--;

  while (*workingThreads) {}  // active waiting

  for (int i = w * begin; i < w * end; i++)  // recoloring
    (*result)[i] = (*newColor)[(*result)[i] - 2];
}

void Output(const std::vector<int>& source, std::size_t w) {
  for (size_t i = 0; i < source.size(); i++) {
    if (i % w == 0)
      std::cout << std::endl;
    std::cout << source[i] << " ";
  }
  std::cout << std::endl;
}

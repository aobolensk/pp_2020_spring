// Copyright 2020 Kolesova Kristina
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include <iterator>
#include "../../../modules/task_1/kolesova_k_shell_sort_batch/shell_sort_batch.h"

std::vector<int> randVec(int size) {
  std::mt19937 gen(time(0));
  std::uniform_int_distribution<> uid(0, 100);

  std::vector<int> vec(size);

  for (int i = 0; i < size; ++i) {
    vec[i] = uid(gen);
  }

  return vec;
}

std::vector<int> sortShell(std::vector<int>& vec, int l, int r) {
  int size, step;
  int i, j, tmp;
  std::vector<int> sortVec(vec);
  size = l + r;
  step = size / 2;
  while (step > 0) {
    for (i = step; i < size; i++) {
      j = i - step;
      while (j > 0 ) {
        if (sortVec[j] > sortVec[j + step]) {
          std::swap(sortVec[j], sortVec[j + step]);
          j = j - step;
        }
        else j = 0;
      }
    }
    step = step / 2;
  }
  return sortVec;
}

std::vector<int> shuffle(std::vector<int>& vec, int l, int r) {
  int half = (l + r) / 2;
  int size = vec.size();
  std::vector<int> tmp(size);
  int i, j;
  for (i = l, j = 0; i <= r; i += 2, j++) {
    tmp[i] = vec[l + j];
    tmp[i + 1] = vec[half + j + 1];
  }
  return tmp;
}

std::vector<int> unshuffle (std::vector<int>& vec, int l, int r) {
  int half = (l + r) / 2;
  int size = vec.size();
  std::vector<int> tmp(size);
  int i, j;
  for (i = l, j = 0; i <= r; i += 2, j++) {
    tmp[l + j] = vec[i];
    tmp[half + j + 1] = vec[i + 1];
  }
  return tmp;
}

void compexh(int& a, int& b) {
  if (b < a)
    std::swap(a, b);
}

std::vector<int> oneShellBetchSort(std::vector<int>& vec) {
  std::vector<int> tmp(vec);
  int size = vec.size();
  int r = size / 2;

  unshuffle(tmp, 0, size);
  tmp = sortShell(tmp, 0, r);
  tmp = sortShell(tmp, r, size);
  shuffle(tmp, 0, size); 


  for (int i = 0; i < r; i += 2) {
    compexh(tmp[i], tmp[i + 1]);
  }

  int halfSize = (r + 1) / 2 - 1;

  for (int i = 1; i + halfSize < r; i++) {
    compexh(tmp[i], tmp[i + halfSize]);
  }

  return tmp;
}
// Copyright 2020 Kolesova Kristina
#include <omp.h>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <utility>
#include "../../../modules/task_2/kolesova_k_shell_sort_batch/shell_sort_batch.h"

std::vector<int> randVec(int size) {
  std::mt19937 gen(time(0));
  std::uniform_int_distribution<> uid(0, 100);

  std::vector<int> vec(size);

  for (int i = 0; i < size; ++i) {
    vec[i] = uid(gen);
  }

  return vec;
}

std::vector<int> sortShell(const std::vector<int>& vec, int l, int r) {
  int size, step;
  int i, j;
  std::vector<int> sortVec(vec);
  size = l + r + 1;
  step = size / 2;

  while (step > 0) {
    for (i = step; i <= r; i++) {
      j = i - step;
      while (j >= l) {
        if (sortVec[j] > sortVec[j + step])
          std::swap(sortVec[j], sortVec[j + step]);
        j = j - step;
      }
    }
    step = step / 2;
  }
  return sortVec;
}

std::vector<int> shuffle(const std::vector<int>& vec, int l, int r) {
  int half = (l + r) / 2;
  int size = vec.size();
  std::vector<int> tmp(size);
  int i = l;
  int j = half + 1;

  int k = 0;
  while (i <= half && j <= r && k != (size - 1)) {
    if (vec[i] <= vec[j]) {
      tmp[k] = vec[i];
      i++;
      k++;
    } else {
      tmp[k] = vec[j];
      j++;
      k++;
    }
  }

  if (i <= half && k <= (size - 1)) {
    while (i <= half || k <= (size - 1)) {
      tmp[k] = vec[i];
      i++;
      k++;
    }
  }

  if (j <= r && k <= (size - 1)) {
    while (j <= r || k <= (size - 1)) {
      tmp[k] = vec[j];
      j++;
      k++;
    }
  }

  return tmp;
}

std::vector<int> unshuffle(const std::vector<int>& vec, int l, int r) {
  int half = (l + r) / 2;
  int size = vec.size();
  std::vector<int> tmp(size);
  int i, j;
  i = l;
  for (j = 0; i < r; i+=2, j++) {
    tmp[l + j] = vec[i];
    tmp[half + j + 1] = vec[i + 1];
  }
  return tmp;
}

std::vector<int> oneShellBetchSort(const std::vector<int>& vec) {
  std::vector<int> tmp(vec);
  int size = vec.size();
  int r = size / 2;

  tmp = unshuffle(tmp, 0, size-1);
  tmp = sortShell(tmp, 0, r-1);
  tmp = sortShell(tmp, r, size-1);
  tmp = shuffle(tmp, 0, size-1);
  return tmp;
}

std::vector<int> shellBetchSort_omp(const std::vector<int>& vec) {
  std::vector<int> tmp(vec);
  std::vector<int> tmp1, tmp2;
  int size = vec.size();
  int r = size / 2;
  int i;

  tmp = unshuffle(tmp, 0, size - 1);

#pragma omp parallel sections num_threads(1)
  {
#pragma omp section
    {
    tmp1 = sortShell(tmp, 0, r - 1);
    }
#pragma omp section
    {
    tmp2 = sortShell(tmp, r, size - 1);
    }
  }

#pragma omp parallel shared(tmp)
  {
#pragma omp for
    for (i = 0; i < r; i++) {
      tmp[i] = tmp1[i];
    }
  }

#pragma omp parallel shared(tmp)
  {
#pragma omp for
    for (i = r; i < size; i++) {
      tmp[i] = tmp2[i];
    }
  }

  tmp = shuffle(tmp, 0, size - 1);

  return tmp;
}

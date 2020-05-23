// Copyright 2020 Bandenkov Daniil
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <ctime>
#include <iterator>
#include <utility>
#include "../../../modules/task_4/bandenkov_d_shell_bancher/shell_batcher.h"

std::vector<int> getRandomVector(int sz) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::vector<int> vec(sz);
  for (int i = 0; i < sz; i++) { vec[i] = gen() % 100; }
  return vec;
}

std::vector<std::vector<int>> splitVector(const std::vector<int>& vec, size_t n) {
  std::vector<std::vector<int>> outVec;
  size_t length = vec.size() / n;
  size_t remain = vec.size() % n;
  size_t begin = 0;
  size_t end = 0;

  for (size_t i = 0; i < fmin(n, vec.size()); ++i) {
    end += (remain > 0) ? (length + !!(remain--)) : length;
    outVec.push_back(std::vector<int>(vec.begin() + begin, vec.begin() + end));
    begin = end;
  }
  return outVec;
}

std::vector<int> shellSort(const std::vector<int>& A, int size) {
  int step, i, j, tmp;
  std::vector<int>array(A);
  for (step = size / 2; step > 0; step /= 2) {
    for (i = step; i < size; i++) {
      for (j = i - step; j >= 0 && array[j] > array[j + step]; j -= step) {
        tmp = array[j];
        array[j] = array[j + step];
        array[j + step] = tmp;
      }
    }
  }
  return array;
}

std::vector<int> shellBatcher_seq(const std::vector<int>& A, const int n, int size) {
  std::vector<std::vector<int>> vec = splitVector(A, n);
  std::vector<int> res;
  for (int i = 0; i < static_cast<int> (vec.size()); ++i) {
    vec[i] = shellSort(vec[i], vec[i].size());
  }
  const int thread = n;
  res = oddevenMerge_seq(vec, thread, size);

  return res;
}

void shellSorter(std::vector<int>& array, int size) {
  int step, i, j, tmp;
  for (step = size / 2; step > 0; step /= 2) {
    for (i = step; i < size; i++) {
      for (j = i - step; j >= 0 && array[j] > array[j + step]; j -= step) {
        tmp = array[j];
        array[j] = array[j + step];
        array[j + step] = tmp;
      }
    }
  }
}

std::vector<int> shellBatcher_std(const std::vector<int>& A, const int n, int size) {
  std::vector<std::vector<int>> vec = splitVector(A, n);
  std::vector<std::thread> threads;
  int countOfTreads = vec.size();
  for (int i = 0; i < countOfTreads; ++i) {
    threads.push_back(std::thread(shellSorter, std::ref(vec[i]), vec[i].size()));
  }
  for (auto& t : threads)
    t.join();

  std::vector<int> res;
  res = oddevenMerge_seq(vec, n, size);

  return res;
}

std::vector<int> oddevenMerge_seq(const std::vector<std::vector<int>>& A, const int n, int size) {
  std::vector<int> res = A[0];
  std::vector<int> odd;
  std::vector<int> even;

  for (int i = 1; i < n; i++) {
    odd = oddBatcher(res, A[i]);
    even = evenBatcher(res, A[i]);
    res = mergeBatcher(even, odd);
  }
  return res;
}

std::vector<int> evenBatcher(const std::vector<int>& A, const std::vector<int>& B) {
  int size1 = A.size();
  int size2 = B.size();
  int size_res = size1 / 2 + size2 / 2 + size1 % 2 + size2 % 2;
  std::vector <int> mas_res(size_res);
  int it1 = 0;
  int it2 = 0;
  int i = 0;

  while ((it1 < size1) && (it2 < size2)) {
    if (A[it1] <= B[it2]) {
      mas_res[i] = A[it1];
      it1 += 2;
    } else {
      mas_res[i] = B[it2];
      it2 += 2;
    }
    i++;
  }

  if (it1 >= size1) {
    for (int j = it2; j < size2; j += 2) {
      mas_res[i] = B[j];
      i++;
    }
  } else {
    for (int j = it1; j < size1; j += 2) {
      mas_res[i] = A[j];
      i++;
    }
  }
  return mas_res;
}

std::vector<int> oddBatcher(const std::vector<int>& A, const std::vector<int>& B) {
  int size1 = A.size();
  int size2 = B.size();
  int size_res = size1 / 2 + size2 / 2;
  std::vector <int> mas_res(size_res);
  int it1 = 1;
  int it2 = 1;
  int i = 0;

  while ((it1 < size1) && (it2 < size2)) {
    if (A[it1] <= B[it2]) {
      mas_res[i] = A[it1];
      it1 += 2;
    } else {
      mas_res[i] = B[it2];
      it2 += 2;
    }
    i++;
  }

  if (it1 >= size1) {
    for (int j = it2; j < size2; j += 2) {
      mas_res[i] = B[j];
      i++;
    }
  } else {
    for (int j = it1; j < size1; j += 2) {
      mas_res[i] = A[j];
      i++;
    }
  }
  return mas_res;
}

std::vector<int> mergeBatcher(const std::vector<int>& A, const std::vector<int>& B) {
  int size1 = A.size();
  int size2 = B.size();
  int size = size1 + size2;
  std::vector<int> res(size);
  int i = 0, j = 0, k = 0;

  while ((j < size1) && (k < size2)) {
    res[i] = A[j];
    res[i + 1] = B[k];
    i += 2;
    j++;
    k++;
  }

  if ((k >= size2) && (j < size1)) {
    for (int l = i; l < size; l++) {
      res[l] = A[j];
      j++;
    }
  }

  for (int i = 0; i < size - 1; i++) {
    if (res[i] > res[i + 1]) {
      std::swap(res[i], res[i + 1]);
    }
  }

  return res;
}

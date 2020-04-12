// Copyright 2020 Bandenkov Daniil
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include <iterator>
#include "../../../modules/task_1/bandenkov_d_shell_batcher_sort/shell_batcher.h"

std::vector<int> getRandomVector(int sz) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::vector<int> vec(sz);
  for (int i = 0; i < sz; i++) { vec[i] = gen() % 100; }
  return vec;
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

std::vector<int> shellBatch(const std::vector<int>& A, int size) {
  int k = size / 2;
  std::vector<int>arr1;
  std::copy(A.begin(), A.end() - k, inserter(arr1, arr1.begin()));
  arr1 = shellSort(arr1, arr1.size());
  std::vector<int> arr2;
  std::copy(A.end() - k, A.end(), inserter(arr2, arr2.begin()));
  arr2 = shellSort(arr2, arr2.size());

  std::vector<int>even = evenBatcher(arr1, arr2);
  std::vector<int>odd = oddBatcher(arr1, arr2);
  std::vector<int>res = mergeBatcher(even, odd);
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
  int flag = 0;
  if (size1 - size2 == 2)
    flag = 1;
  if (size2 - size1 == 2)
    flag = 2;
  int size_res = A.size() + B.size();
  int size_min = size_res / 2 - 1;
  std::vector <int> mas_res(size_res);
  int buf;
  int i = 0;
  if (flag == 0) {
    for (i = 0; i < size1; i++) {
      mas_res[2 * i] = A[i];
      mas_res[2 * i + 1] = B[i];
    }
  }

  if ((flag == 1) || (flag == 2)) {
    for (i = 0; i < size_min; i++) {
      mas_res[2 * i] = A[i];
      mas_res[2 * i + 1] = B[i];
    }
  }

  if (flag == 1) {
    mas_res[2 * i] = A[i];
    mas_res[2 * i + 1] = A[i + 1];
  }

  if (flag == 2) {
    mas_res[2 * i] = B[i];
    mas_res[2 * i + 1] = B[i + 1];
  }

  for (int i = 1; i < size_res; i++) {
    if (mas_res[i] < mas_res[i - 1]) {
      buf = mas_res[i - 1];
      mas_res[i - 1] = mas_res[i];
      mas_res[i] = buf;
    }
  }

  return mas_res;
}

// Copyright 2020 Pauzin Leonid
#include "../../../modules/task_2/pauzin_l_shell_merge_omp/pauzin_l_shell_merge_omp.h"
#include <omp.h>
#include <ctime>
#include <random>
#include <vector>
#include <algorithm>

std::vector<int> getRandomVector(int n) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::vector<int> vec(n);
  for (int i = 0; i < n; i++) { vec[i] = gen() % 100; }
  return vec;
}

std::vector <int> ShellSort(const std::vector <int>& vec) {
  int step, i, j, tmp;
  int size = vec.size();
  std::vector <int> resulVec(vec);
  for (step = size / 2; step > 0; step /= 2)
    for (i = step; i < size; i++)
      for (j = i - step; j >= 0 && resulVec[j] > resulVec[j + step]; j -= step) {
        tmp = resulVec[j];
        resulVec[j] = resulVec[j + step];
        resulVec[j + step] = tmp;
      }
  return resulVec;
}


std::vector<int> myMerge(std::vector<int> vec1, std::vector<int> vec2) {
  int i = 0, j = 0;
  int k = 0;
  int size1 = vec1.size();
  int size2 = vec2.size();
  std::vector<int> result(size1+size2);

  while (size1 && size2) {
    if (vec1[i] < vec2[j]) {
      result[k] = vec1[i];
      i++;
      size1--;
    } else {
      result[k] = vec2[j];
      j++;
      size2--;
    }
    k++;
  }

  if (size1 == 0) {
    for (int z = j; z < j + size2; z++) {
      result[k] = vec2[z];
      k++;
    }
  } else if (size2 == 0) {
    for (int z = i; z < i + size1; z++) {
      result[k] = vec1[z];
      k++;
    }
  }

  return result;
}

std::vector <int> mySortOmp(std::vector<int> vec, std::size_t nthreads) {
  omp_set_num_threads(nthreads);
  std::vector<int> result = vec;
  int size = result.size();
  std::size_t delta = vec.size() / nthreads;
  std::size_t remainder = vec.size() % nthreads;
  std::vector<int> localVec;
  if (size == 1)
    return vec;
  if (size < 1)
    throw "Wrong vector size";

#pragma omp parallel shared(vec, remainder) private(localVec)
  {
    std::size_t tid = omp_get_thread_num();
    if (tid == 0) {
      localVec.resize(delta + remainder);
      std::copy(vec.begin(), vec.begin() + delta + remainder, localVec.begin());
    } else {
        localVec.resize(delta);
    }

    for (std::size_t i = 1; i < nthreads; i++) {
      if (tid == i) {
        std::copy(vec.begin() + delta * i + remainder, vec.end() - delta *(nthreads - i - 1), localVec.begin());
      }
    }

    localVec = ShellSort(localVec);

#pragma omp master
    result = localVec;
#pragma omp barrier
#pragma omp critical
    if (tid != 0) {
      result = myMerge(localVec, result);
    }
  }
  return result;
}

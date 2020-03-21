// Copyright 2020 Pauzin Leonid
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include "../../../modules/task_1/pauzin_l_shell_merge/pauzin_l_shell_merge.h"

std::vector<int> getRandomVector(int n) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::vector<int> vec(n);
  for (int i = 0; i < n; i++) { vec[i] = gen() % 100; }
  return vec;
}

std::vector <int> ShellSort(const std::vector <int> &vec) {
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

std::vector<int> myMerge(std::vector<int> vec1, std::vector<int> vec2, std::vector<int> result) {
  int i = 0, j = 0;
  int k = 0;
  int size1 = vec1.size();
  int size2 = vec2.size();
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
std::vector <int> mySort(std::vector<int> vec1) {
  std::vector<int> result = vec1;
  int size = result.size();
  if (size == 1)
    return vec1;
  if (size < 1)
    throw "Wrong vector size";
  std::vector<int> vec2;
  std::vector<int> vec3;

  if (size % 2 == 0) {
    vec2.resize(size / 2);
    vec3.resize(size / 2);
  } else {
    vec2.resize(size / 2);
    vec3.resize(size / 2 + 1);
  }

  std::copy(result.begin(), result.begin() + size / 2, vec2.begin());
  std::copy(result.begin() + size / 2, result.end(), vec3.begin());

  vec2 = ShellSort(vec2);
  vec3 = ShellSort(vec3);

  result = myMerge(vec2, vec3, result);
  return result;
}

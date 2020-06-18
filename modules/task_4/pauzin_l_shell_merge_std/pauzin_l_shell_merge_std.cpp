// Copyright 2020 Pauzin Leonid
#include "../../../modules/task_4/pauzin_l_shell_merge_std/pauzin_l_shell_merge_std.h"
#include <thread>
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

std::vector<std::vector<int>> splitVector(const std::vector<int>& vec, std::size_t nthreads) {
  std::vector<std::vector<int>> outVec;
  size_t length = vec.size() / nthreads;
  size_t remain = vec.size() % nthreads;
  size_t begin = 0;
  size_t end = 0;

  for (size_t i = 0; i < fmin(nthreads, vec.size()); ++i) {
    end += (remain > 0) ? (length + !!(remain--)) : length;
    outVec.push_back(std::vector<int>(vec.begin() + begin, vec.begin() + end));
    begin = end;
  }
  return outVec;
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

  if (size1 == 0)
    std::copy(vec2.begin() + j, vec2.end(), result.begin() + k);
  else if (size2 == 0)
    std::copy(vec1.begin() + i, vec1.end(), result.begin() + k);

  return result;
}

std::vector <int> mySortSTD(std::vector<int> vec, std::size_t nthreads) {
  std::size_t size = vec.size();
  if (size == 1)
    return vec;
  if (size < 1)
    throw "Wrong vector size";

  std::vector<std::vector<int>> splited = splitVector(vec, nthreads);
  std::vector<std::thread> threads;
  std::vector<int> resVec;

  for (std::size_t i = 0; i < nthreads; i++) {
    threads.push_back(std::thread([&splited, i]() {
      splited[i] = ShellSort(splited[i]);
    }));
  }

  for (auto& t : threads)
    t.join();

  resVec = splited[0];
  for (std::size_t i = 1; i < nthreads; i++) {
    resVec = myMerge(resVec, splited[i]);
  }

  return resVec;
}
// Copyright 2020 Pauzin Leonid
#include "../../../modules/task_3/pauzin_l_shell_merge_tbb/pauzin_l_shell_merge_tbb.h"
#include <tbb/tbb.h>
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

std::vector <int> ShellSort(const std::vector <int>& vec, int size) {
  int step, i, j;
  int tmp;
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

std::vector<int> mySortTbb(const std::vector<int>& vec, std::size_t nthreads) {
  std::size_t size = vec.size();
  if (size == 1)
        return vec;
  if (size < 1)
    throw "Wrong vector size";
  std::vector<std::vector<int>> splited = splitVector(vec, nthreads);
  std::vector<int> resVec;
  tbb::task_scheduler_init init(nthreads);
  tbb::parallel_for(tbb::blocked_range<size_t>(0, splited.size(), 1),
    [&splited](const tbb::blocked_range<size_t>& r) {
      int begin = r.begin(), end = r.end();
      for (int i = begin; i != end; ++i)
        splited[i] = ShellSort(splited[i], splited[i].size());
    }, tbb::simple_partitioner());

  init.terminate();
  resVec = splited[0];
  for (std::size_t i = 1; i < nthreads; i++) {
    resVec = myMerge(resVec, splited[i]);
  }
  return resVec;
}

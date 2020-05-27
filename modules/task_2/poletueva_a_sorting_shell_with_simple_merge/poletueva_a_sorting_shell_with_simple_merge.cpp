// Copyright 2020 Poletueva Anastasia

#include "../../../modules/task_2/poletueva_a_sorting_shell_with_simple_merge/poletueva_a_sorting_shell_with_simple_merge.h"
#include <omp.h>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <random>
#include <ctime>


std::vector<int> getRandom(int N, int seed) {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(seed));

  std::vector<int> v(N);

  for (int i = 0; i < N ; i++) { v[i] = gen() % 100; }

  return v;
}

std::vector<int> SortShell(const std::vector<int>& a, int size) {
  std::vector<int>m(a);

  for (int step = size / 2; step > 0; step /= 2) {
    for (int i = step; i < size; i++) {
      for (int j = i - step; j >= 0 && m[j] > m[j + step]; j -= step) {
        std::swap(m[j], m[j + step]);
      }
    }
  }

  return m;
}

std::vector<std::vector<int>> division(const std::vector<int>& a, unsigned int n) {
  std::vector<std::vector<int>> res;
  std::vector<int> v;
  std::vector<int> s(a);

  unsigned int k = s.size() / n;

  for (unsigned int i = 0; i < n; i++) {
    if ((n*k < s.size())&&(i == n-1)) {
      v.insert(v.end(), s.begin() + i*k, s.end());
    } else {
      v.insert(v.end(), s.begin() + i*k, s.begin() + (i + 1)*k);
    }
    res.push_back(v);
    v.clear();
  }

  return res;
}

std::vector<int> Merge(const std::vector<std::vector<int>>& a, int n, int size) {
  std::vector<int> res = a[0];

  for (int i = 1; i < n; i++) {
    res = Merge_of_two_vectors(res, a[i]);
  }
  return res;
}

std::vector<int> Merge_of_two_vectors(const std::vector<int>& a, const std::vector<int>& b) {
  std::vector<int> res;

  int size_a = a.size();
  int size_b = b.size();

  int it1 = 0;
  int it2 = 0;

  while (true) {
    if (a[it1] < b[it2]) {
      res.push_back(a[it1]);
      it1++;
    } else {
      res.push_back(b[it2]);
      it2++;
    }
    if (it1 == size_a) {
        for (int i = it2; i < size_b; i++) {
          res.push_back(b[i]);
        }
        break;
    }
    if (it2 == size_b) {
      for (int i = it1; i < size_a; i++) {
        res.push_back(a[i]);
      }
      break;
    }
  }
  return res;
  }

std::vector<int> Shell_with_merge(const std::vector<int>& a, int n, int size) {
  std::vector<int> res;

  std::vector<std::vector<int>> vec = division(a, n);

    for (int i = 0; i <static_cast<int> (vec.size()); i++) {
      vec[i] = SortShell(vec[i], vec[i].size());
    }

  res = Merge(vec, n, size);

  return res;
}


std::vector<int> Shell_with_merge_omp(const std::vector<int>& a, int n, int size) {
  std::vector<int> res;

  std::vector<std::vector<int>> vec = division(a, n);

  #pragma omp parallel shared(vec)
  {
  #pragma omp for
      for (int i = 0; i <static_cast<int> (vec.size()); i++) {
        vec[i] = SortShell(vec[i], vec[i].size());
    }
  }
  res = Merge(vec, n, size);

  return res;
}

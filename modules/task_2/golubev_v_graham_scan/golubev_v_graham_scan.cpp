// Copyright 2020 Golubev Vladislav

#include <omp.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include "../../../modules/task_2/golubev_v_graham_scan/golubev_v_graham_scan.h"

std::vector<double> mp_sort(std::vector<double> v) {
#pragma omp parallel
  {
    int step = v.size() / omp_get_num_threads();
    int n_thread = omp_get_thread_num();
    auto left = v.begin() + n_thread * step;
    auto right = left + step;
    std::sort(left, right);
  }
  std::vector<double> res(v);
  return res;
}

// Copyright 2020 Golubev Vladislav

#include <omp.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>
#include "../../../modules/task_2/golubev_v_graham_scan/golubev_v_graham_scan.h"

void mp_sort(std::vector<double>::iterator begin, std::vector<double>::iterator end) {
  int num_threads = 0;
#pragma omp parallel num_threads(2)
  {
    int n_thread = omp_get_thread_num();
    num_threads = omp_get_num_threads();
    int step = (end - begin) / num_threads;


    auto left = begin + n_thread * step;
    auto right = left + step;

    if (n_thread == num_threads - 1) {
      std::sort(left, right + (end - begin) % num_threads);
    } else {
      std::sort(left, right);
    }
  }
  /*num_threads = std::ceil(static_cast<double>(num_threads) / 2.0);
#pragma omp parallel num_threads(num_threads)
  {

  }*/
}

void merge(std::vector<double>::iterator left, std::vector<double>::iterator mid, std::vector<double>::iterator right) {
  auto lidx = left;
  auto ridx = mid;
  std::size_t idx = 0;
  std::vector<double> tmp(right - left);

  while (lidx != mid || ridx != right) {
    if (*lidx < *ridx) {
      tmp[idx++] = std::move(*lidx);
      lidx++;
    } else {
      tmp[idx++] = std::move(*ridx);
      ridx++;
    }

    if (lidx == mid) {
      std::copy(std::make_move_iterator(ridx),
        std::make_move_iterator(right),
        &tmp[idx]);
      break;
    }

    if (ridx == right) {
      std::copy(std::make_move_iterator(lidx),
        std::make_move_iterator(mid),
        &tmp[idx]);
      break;
    }
  }
  std::copy(tmp.begin(), tmp.end(), left);
}


/*void omp_sort(std::vector<double>::iterator first, std::vector<double>::iterator last) {
  auto i = first;
  auto j = last - 1;
  double pivot = *(first + (last - first) / 2);

  do {
    while (*i < pivot)
      i++;
    while (*j > pivot)
      j--;
    if (i <= j) {
      if (i < j) {
        std::swap(*i, *j);
      }
      i++;
      j--;
    }
  } while (i <= j);

  if (i < last)
    omp_sort(i, last);
  if (first < j)
    omp_sort(first, j + 1);
}*/

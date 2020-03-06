// Copyright 2020 Golubev Vladislav

#include <omp.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>
#include <random>
#include <stack>
#include "../../../modules/task_2/golubev_v_graham_scan/golubev_v_graham_scan.h"

std::vector<std::pair<double, double> > get_rand_set(std::size_t size) {
  std::mt19937 gen;

  std::vector<std::pair<double, double> > result(size);
  for (std::size_t i = 0; i < size; ++i) {
    result[i] = std::make_pair(gen() % 10000, gen() % 10000);
  }
  return result;
}
std::vector<std::pair<double, double> > generate_points(std::size_t size) {
  std::vector<std::pair<double, double> > result(size);
  result[0] = std::make_pair(0, 0);
  for (std::size_t i = 1; i < size; ++i) {
    result[i] = std::make_pair(i, 10);
  }

  return result;
}
std::vector<std::pair<double, double> > get_test_set_1() {
  std::vector<std::pair<double, double> > result(16);
  result[0] = std::make_pair(0, 0);
  result[1] = std::make_pair(1, -3);
  result[2] = std::make_pair(3, -2);
  result[3] = std::make_pair(6, -4);
  result[4] = std::make_pair(7, -2);
  result[5] = std::make_pair(5, 1);
  result[6] = std::make_pair(8, 3);
  result[7] = std::make_pair(2, 6);
  result[8] = std::make_pair(1, 3);
  result[9] = std::make_pair(2, 1);
  result[10] = std::make_pair(3, 3);
  result[11] = std::make_pair(5, 5);
  result[12] = std::make_pair(4, -1);
  result[13] = std::make_pair(5, -2);
  result[14] = std::make_pair(7, 1);
  result[15] = std::make_pair(5, 3);

  return result;
}
std::vector<std::pair<double, double> > get_test_set_2() {
  std::vector<std::pair<double, double> > result(22);
  result[0] = std::make_pair(0, 1);
  result[1] = std::make_pair(0, -5);
  result[2] = std::make_pair(0, -6);
  result[3] = std::make_pair(4, -6);
  result[4] = std::make_pair(2, -4);
  result[5] = std::make_pair(4, -2);
  result[6] = std::make_pair(7, -2);
  result[7] = std::make_pair(5, -1);
  result[8] = std::make_pair(5, 2);
  result[9] = std::make_pair(2, 1);
  result[10] = std::make_pair(3, 3);
  result[11] = std::make_pair(7, 2);
  result[12] = std::make_pair(9, 2);
  result[13] = std::make_pair(9, -4);
  result[14] = std::make_pair(8, 5);
  result[15] = std::make_pair(6, 4);
  result[16] = std::make_pair(3, 4);
  result[17] = std::make_pair(2, 5);
  result[18] = std::make_pair(1, 3);
  result[19] = std::make_pair(0, 2);
  result[20] = std::make_pair(0, 0);
  result[21] = std::make_pair(-1, 0);

  return result;
}
std::vector<std::pair<double, double> > get_test_set_3() {
  std::vector<std::pair<double, double> > result(17);
  result[0] = std::make_pair(-6, -2);
  result[1] = std::make_pair(-6, 2);
  result[2] = std::make_pair(-4, 1);
  result[3] = std::make_pair(-6, -6);
  result[4] = std::make_pair(-4, -1);
  result[5] = std::make_pair(-3, 3);
  result[6] = std::make_pair(-2, 2);
  result[7] = std::make_pair(-1, 1);
  result[8] = std::make_pair(-1, -1);
  result[9] = std::make_pair(-2, -2);
  result[10] = std::make_pair(-3, -3);
  result[11] = std::make_pair(1, 1);
  result[12] = std::make_pair(2, 2);
  result[13] = std::make_pair(3, 3);
  result[14] = std::make_pair(1, -1);
  result[15] = std::make_pair(2, -2);
  result[16] = std::make_pair(3, -3);
  return result;
}

bool is_less(const std::pair<double, double>& a, const std::pair<double, double>& b) {
  double grad_a = omp_get_polar_grad(a);
  double grad_b = omp_get_polar_grad(b);

  if (grad_a < grad_b) {
    return true;
  } else if ((std::abs(grad_a - grad_b) <= 1e-15) && (omp_get_polar_r(a) < omp_get_polar_r(b))) {
    return true;
  } else {
    return false;
  }
}
double omp_get_polar_r(const std::pair<double, double>& point) {
  return std::sqrt(point.second * point.second + point.first * point.first);
}
double omp_get_polar_grad(const std::pair<double, double>& point) {
  return std::atan(point.second / point.first);
}
double omp_get_det(const std::pair<double, double>& x,
  const std::pair<double, double>& y, const std::pair<double, double>& z) {
  return (y.first - x.first) * (z.second - x.second) - (z.first - x.first) * (y.second - x.second);
}
std::size_t omp_get_lex_min(std::vector<std::pair<double, double> > v, int num_threads) {
  std::vector<std::size_t> res(num_threads);

#pragma omp parallel num_threads(num_threads)
  {
    int n_thread = omp_get_thread_num();
    int size = v.size();
#pragma omp for
    for (int i = 1; i < size; ++i) {
      if (v[res[n_thread]] > v[i]) {
        res[n_thread] = i;
      }
    }
  }
  std::size_t min_idx = res[0];
  for (std::size_t i = 1; i < res.size(); ++i) {
    if (v[min_idx] > v[res[i]]) {
      min_idx = res[i];
    }
  }
  return min_idx;
}

void mp_sort(std::vector<std::pair<double, double> >::iterator begin,
            std::vector<std::pair<double, double> >::iterator end, int num_threads) {
  int st = std::log2(num_threads);
  num_threads = std::pow(2, st);

#pragma omp parallel num_threads(num_threads)
  {
    int n_thread = omp_get_thread_num();
    int step = (end - begin) / num_threads;

    auto left = begin + n_thread * step;
    auto right = left + step;

    std::sort(left, right, is_less);


    int log = std::log2(num_threads);
    int h = 2;
    int sorted_size;

    while (log != 0) {
      sorted_size = step;
      step += step;

#pragma omp barrier

      if (n_thread < num_threads / h) {
        merge(begin + step * n_thread,
          begin + n_thread * step + sorted_size,
          begin + n_thread * step + step);
      }
      --log;
      h *= 2;
    }
  }

  int ostatok = (end - begin) % num_threads;
  if (ostatok != 0) {
    std::sort(begin + (end - begin) / num_threads * num_threads, end, is_less);
    merge(begin, begin + (end - begin) / num_threads * num_threads, end);
  }
}

void merge(std::vector<std::pair<double, double> >::iterator left,
  std::vector<std::pair<double, double> >::iterator mid,
  std::vector<std::pair<double, double> >::iterator right) {
  auto lidx = left;
  auto ridx = mid;
  std::size_t idx = 0;
  std::vector<std::pair<double, double> > tmp(right - left);

  while (lidx != mid || ridx != right) {
    if (is_less((*lidx), (*ridx))) {
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
  std::copy(std::make_move_iterator(tmp.begin()),
    std::make_move_iterator(tmp.end()), left);
}



std::vector<std::pair<double, double> > omp_graham_scan(std::vector<std::pair<double, double> > points,
  int num_threads) {
  // lex_min
  std::size_t min_idx = omp_get_lex_min(points, num_threads);
  std::swap(points[0], points[min_idx]);
  auto lex_min = points[0];

  // sdvig koordinat
  int size = points.size();
#pragma omp parallel for /*if (size >= 10'000'000)*/
  for (int i = 0; i < size; ++i) {
    points[i].first -= lex_min.first;
    points[i].second -= lex_min.second;
  }

  // sort
  mp_sort(points.begin() + 1, points.end(), num_threads);

  // scan
  std::stack<std::pair<double, double> > res;
  std::size_t stack_size = res.size();
  res.push(points[0]);
  res.push(points[1]);

  std::pair<double, double> x, y, z;
  for (std::size_t i = 2; i < size; ++i) {
    stack_size = res.size();
    y = res.top();
    res.pop();
    x = res.top();
    z = points[i];
    double det = omp_get_det(x, y, z);

    if (det > 0) {
      res.push(y);
      res.push(points[i]);
    } else if (stack_size < 3) {
      res.push(points[i]);
    } else {
      --i;
    }
  }

  std::vector<std::pair<double, double> > res_vec(res.size());
  std::size_t i = res.size() - 1;
  while (!res.empty()) {
    res_vec[i] = res.top();
    res_vec[i].first += lex_min.first;
    res_vec[i].second += lex_min.second;
    res.pop();
    --i;
  }

  return res_vec;
}


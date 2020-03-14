// Copyright 2020 Golubev Vladislav

#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>
#include <random>
#include <stack>
#include <thread>
#include <mutex>
#include "../../../modules/task_4/golubev_v_graham_scan/golubev_v_graham_scan.h"

std::vector<std::pair<double, double> > get_rand_set(std::size_t size) {
  std::mt19937 gen;

  std::vector<std::pair<double, double> > result(size);
  for (std::size_t i = 0; i < size; ++i) {
    result[i] = std::make_pair(gen() % 10000, gen() % 10000);
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

double get_polar_r(const std::pair<double, double>& point) {
  return std::sqrt(point.second * point.second + point.first * point.first);
}

double get_polar_grad(const std::pair<double, double>& point) {
  return std::atan(point.second / point.first);
}

double get_det(const std::pair<double, double>& x,
  const std::pair<double, double>& y, const std::pair<double, double>& z) {
  return (y.first - x.first) * (z.second - x.second) - (z.first - x.first) * (y.second - x.second);
}

std::size_t get_lex_min(std::vector<std::pair<double, double> > v) {
  std::size_t min_idx = 0;
  for (std::size_t i = 1; i < v.size(); ++i) {
    if (v[min_idx] > v[i]) {
      min_idx = i;
    }
  }
  return min_idx;
}

bool is_less(const std::pair<double, double>& a, const std::pair<double, double>& b) {
  double grad_a = get_polar_grad(a);
  double grad_b = get_polar_grad(b);

  if (grad_a < grad_b) {
    return true;
  } else if ((std::abs(grad_a - grad_b) <= 1e-15) && (get_polar_r(a) < get_polar_r(b))) {
    return true;
  } else {
    return false;
  }
}

std::vector<std::pair<double, double> > graham_scan(
  std::vector<std::pair<double, double> >::iterator begin,
  std::vector<std::pair<double, double> >::iterator end) {
  std::vector<std::pair<double, double> > points(end - begin);
  std::copy(begin, end, points.begin());
  // lex_min
  std::size_t min_idx = get_lex_min(points);
  std::swap(points[0], points[min_idx]);
  auto lex_min = points[0];

  // sdvig koordinat
  for (std::size_t i = 0; i < points.size(); ++i) {
    points[i].first -= lex_min.first;
    points[i].second -= lex_min.second;
  }

  // sort
  std::sort(points.begin() + 1, points.end(), is_less);

  // scan
  std::stack<std::pair<double, double>> res;
  std::size_t stack_size = res.size();
  res.push(points[0]);
  res.push(points[1]);

  std::pair<double, double> x, y, z;
  for (std::size_t i = 2; i < points.size(); ++i) {
    stack_size = res.size();
    y = res.top();
    res.pop();
    x = res.top();
    z = points[i];
    double det = get_det(x, y, z);

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

std::vector<std::pair<double, double> > std_thread_graham_scan(
  std::vector<std::pair<double, double> >::iterator begin,
  std::vector<std::pair<double, double> >::iterator end,
  std::size_t n_threads) {
  if (n_threads == 0) {
    throw "incorrect number of threads";
  }
  std::thread* threads = new std::thread[n_threads];
  std::mutex m;

  int step = (end - begin) / n_threads;
  std::vector<std::pair<double, double> > last_points;

  for (std::size_t i = 0; i < n_threads - 1; ++i) {
    threads[i] = std::thread([&last_points, i, begin, step, &m]() {
      auto left = begin + step * i;
      auto right = begin + step * (i + 1);
      auto local_scan = graham_scan(left, right);
      for (std::size_t j = 0; j < local_scan.size(); ++j) {
        m.lock();
        last_points.push_back(local_scan[j]);
        m.unlock();
      }
      });
  }
  threads[n_threads - 1] = std::thread([&last_points, begin, end, n_threads, step, &m]() {
    auto local_scan = graham_scan(begin + step * (n_threads - 1), end);
    for (std::size_t j = 0; j < local_scan.size(); ++j) {
      m.lock();
      last_points.push_back(local_scan[j]);
      m.unlock();
    }
    });
  for (std::size_t i = 0; i < n_threads; ++i) {
    threads[i].join();
  }
  delete[] threads;
  return graham_scan(last_points.begin(), last_points.end());
}
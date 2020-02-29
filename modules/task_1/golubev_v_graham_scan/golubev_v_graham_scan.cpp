// Copyright 2020 Golubev Vladislav

#include "../../../modules/task_1/golubev_v_graham_scan/golubev_v_graham_scan.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>


std::vector<std::pair<double, double> > generate_points(std::size_t size) {
  std::vector<std::pair<double, double> > result(size);
  result[0] = std::make_pair(0, 0);
  for (std::size_t i = 1; i < size; ++i) {
    result[i] = std::make_pair(i, 10);
  }

  return result;
}

std::vector<std::pair<double, double> > get_test_set() {
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

double get_polar_r(const std::pair<double, double>& point) {
  return std::sqrt(point.second * point.second + point.first * point.first);
}

double get_polar_grad(const std::pair<double, double>& point) {
  return std::atan(point.second / point.first);
}

double get_det(const std::pair<double, double>& x,
                const std::pair<double, double>& y, const std::pair<double, double>& z) {
  return (x.first - y.first) * (z.second - x.second) - (z.first - x.first) * (x.second - y.second);
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

std::vector<std::pair<double, double> > polar_sort(std::vector<std::pair<double, double> > v) {
  std::sort(v.begin() + 1, v.end(),
    [&](const std::pair<double, double>& a, const std::pair<double, double>& b) {
      double grad_a = get_polar_grad(a);
      double grad_b = get_polar_grad(b);

      if (grad_a < grad_b) {
        return true;
      } else if ((std::abs(grad_a - grad_b) <= 1e-8) && (get_polar_r(a) < get_polar_r(b))) {
        return true;
      } else {
        return false;
      }
    });
  return v;
}

std::vector<std::pair<double, double> > graham_scan(std::vector<std::pair<double, double> > points) {
  // lex_min
  std::size_t min_idx = get_lex_min(points);
  std::swap(points[0], points[min_idx]);
  std::cout << min_idx << std::endl;

  // sdvig koordinat
  for (std::size_t i = points.size(); i > 0; --i) {
    points[i - 1].first -= points[0].first;
    points[i - 1].second -= points[0].second;
  }

  // sort
  auto sorted_points = polar_sort(points);

  // scan
  std::stack<std::pair<double, double>> res;
  res.push(sorted_points[0]);
  res.push(sorted_points[1]);

  std::pair<double, double> x, y, z;
  for (std::size_t i = 2; i < sorted_points.size(); ++i) {
    y = res.top();
    res.pop();
    x = res.top();
    z = sorted_points[i];
    double det = get_det(x, y, z);

    if (det > 0) {
      res.push(y);
      res.push(sorted_points[i]);
    } else if (res.size() < 3) {
    res.push(sorted_points[i]);
    } else {
    --i;
    }
  }

  std::vector<std::pair<double, double> > res_vec(res.size());
  for (std::size_t i = 0; i < res.size(); ++i) {
    res_vec[i] = res.top();
    res.pop();
  }

  return res_vec;
}

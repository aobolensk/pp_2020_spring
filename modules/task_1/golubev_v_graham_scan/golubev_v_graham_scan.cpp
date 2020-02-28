// Copyright 2020 Golubev Vladislav

#include "../../../modules/task_1/golubev_v_graham_scan/golubev_v_graham_scan.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>


std::vector<std::pair<double, double> > generate_points(std::size_t size) {
  std::vector<std::pair<double, double> > result(size);
  result[0] = std::make_pair(0, 0);
  for (std::size_t i = 1; i < size; ++i) {
    result[i] = std::make_pair(i, 10);
  }

  return result;
}

double get_polar_r(const std::pair<double, double>& point) {
  return std::sqrt(point.second * point.second + point.first * point.first);
}

double get_polar_grad(const std::pair<double, double>& point) {
  return std::atan(point.second / point.first);
}

std::pair<double, double> get_lex_min(std::vector<std::pair<double, double>> v) {
  std::pair<double, double> lex_min = v[0];
  for (std::size_t i = 1; i < v.size(); ++i) {
    lex_min = std::min(lex_min, v[i]);
  }
  return lex_min;
}

std::vector<std::pair<double, double> > polar_sort(std::vector<std::pair<double, double> > v) {
  std::sort(v.begin() + 1, v.end(),
    [&](const std::pair<double, double>& a, const std::pair<double, double>& b) {
      double grad_a = get_polar_grad(a);
      double grad_b = get_polar_grad(b);

      if (grad_a < grad_b) {
        return true;
      } else if ((std::abs(grad_a - grad_b) <= 1e-15) && (get_polar_r(a) <= get_polar_r(b))) {
        return true;
      } else {
        return false;
      }
    });
  return v;
}

std::vector<std::pair<double, double> > graham_scan(std::vector<std::pair<double, double> > points) {
  // lex_min
  std::pair<double, double> lex_min = points[0];
  for (std::size_t i = 1; i < points.size(); ++i) {
    lex_min = std::min(lex_min, points[i]);
  }
  return points;
}

// Copyright 2020 Golubev Vladislav

#include "../../../modules/task_1/golubev_v_graham_scan/golubev_v_graham_scan.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>


std::vector<std::pair<double, double> > generate_points(size_t size) {
  std::vector<std::pair<double, double> > result(size);
  result[0] = std::make_pair(0, 0);
  result[1] = std::make_pair(1, 5);
  result[2] = std::make_pair(2, 4);
  result[3] = std::make_pair(3, 3);
  result[4] = std::make_pair(4, 1);


  /*for (size_t i = 0; i < size; ++i) {
    result[i] = std::make_pair(i, i + 1);
  }*/

  return result;
}

double get_polar_r(const std::pair<double, double>& point) {
  return std::sqrt(point.second * point.second + point.first * point.first);
}

double get_polar_grad(const std::pair<double, double>& point) {
  return std::atan(point.second / point.first);
}

std::vector<std::pair<double, double> >& graham_scan(std::vector<std::pair<double, double> > points) {
  return points;
}

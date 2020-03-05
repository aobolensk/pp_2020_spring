// Copyright 2020 Golubev Vladislav
#ifndef MODULES_TASK_2_GOLUBEV_V_GRAHAM_SCAN_GOLUBEV_V_GRAHAM_SCAN_H_
#define MODULES_TASK_2_GOLUBEV_V_GRAHAM_SCAN_GOLUBEV_V_GRAHAM_SCAN_H_
#include <vector>
#include <utility>
#include <algorithm>

std::vector<std::pair<double, double> > get_rand_set(std::size_t size);

double get_polar_r(const std::pair<double, double>& point);
double get_polar_grad(const std::pair<double, double>& point);
double get_det(const std::pair<double, double>& x,
  const std::pair<double, double>& y, const std::pair<double, double>& z);

std::size_t get_lex_min(std::vector<std::pair<double, double> > v);

void mp_sort(std::vector<std::pair<double, double> >::iterator first,
  std::vector<std::pair<double, double> >::iterator last,
  int num_threads);

void merge(std::vector<std::pair<double, double> >::iterator left,
  std::vector<std::pair<double, double> >::iterator mid,
  std::vector<std::pair<double, double> >::iterator right);

#endif  // MODULES_TASK_2_GOLUBEV_V_GRAHAM_SCAN_GOLUBEV_V_GRAHAM_SCAN_H_

// Copyright 2020 Golubev Vladislav
#ifndef MODULES_TASK_2_GOLUBEV_V_GRAHAM_SCAN_GOLUBEV_V_GRAHAM_SCAN_H_
#define MODULES_TASK_2_GOLUBEV_V_GRAHAM_SCAN_GOLUBEV_V_GRAHAM_SCAN_H_
#include <vector>
#include <utility>
#include <algorithm>

std::vector<std::pair<double, double> > get_rand_set(std::size_t size);
std::vector<std::pair<double, double> > get_test_set_1();
std::vector<std::pair<double, double> > get_test_set_2();
std::vector<std::pair<double, double> > get_test_set_3();


bool is_less(const std::pair<double, double>& a, const std::pair<double, double>& b);

double get_polar_r(const std::pair<double, double>& point);
double get_polar_grad(const std::pair<double, double>& point);
double get_det(const std::pair<double, double>& x,
  const std::pair<double, double>& y, const std::pair<double, double>& z);
std::size_t get_lex_min(std::vector<std::pair<double, double> > v);

std::vector<std::pair<double, double> > graham_scan(std::vector<std::pair<double, double> >::iterator begin,
  std::vector<std::pair<double, double> >::iterator end);
std::vector<std::pair<double, double> > omp_graham_scan(
  std::vector<std::pair<double, double> >::iterator begin,
  std::vector<std::pair<double, double> >::iterator end,
  std::size_t n_threads = 2);

#endif  // MODULES_TASK_2_GOLUBEV_V_GRAHAM_SCAN_GOLUBEV_V_GRAHAM_SCAN_H_

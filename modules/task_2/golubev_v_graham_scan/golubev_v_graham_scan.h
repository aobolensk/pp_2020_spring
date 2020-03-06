// Copyright 2020 Golubev Vladislav
#ifndef MODULES_TASK_2_GOLUBEV_V_GRAHAM_SCAN_GOLUBEV_V_GRAHAM_SCAN_H_
#define MODULES_TASK_2_GOLUBEV_V_GRAHAM_SCAN_GOLUBEV_V_GRAHAM_SCAN_H_
#include <vector>
#include <utility>
#include <algorithm>

std::vector<std::pair<double, double> > get_rand_set(std::size_t size);
std::vector<std::pair<double, double> > generate_points(std::size_t size);
std::vector<std::pair<double, double> > get_test_set_1();
std::vector<std::pair<double, double> > get_test_set_2();
std::vector<std::pair<double, double> > get_test_set_3();


bool is_less(const std::pair<double, double>& a, const std::pair<double, double>& b);
double omp_get_polar_r(const std::pair<double, double>& point);
double omp_get_polar_grad(const std::pair<double, double>& point);
double omp_get_det(const std::pair<double, double>& x,
  const std::pair<double, double>& y, const std::pair<double, double>& z);
std::size_t omp_get_lex_min(std::vector<std::pair<double, double> > v, int num_threads);


void mp_sort(std::vector<std::pair<double, double> >::iterator first,
  std::vector<std::pair<double, double> >::iterator last,
  int num_threads);
void merge(std::vector<std::pair<double, double> >::iterator left,
  std::vector<std::pair<double, double> >::iterator mid,
  std::vector<std::pair<double, double> >::iterator right);


std::vector<std::pair<double, double> > omp_graham_scan(std::vector<std::pair<double, double> > points,
  int num_threads);

#endif  // MODULES_TASK_2_GOLUBEV_V_GRAHAM_SCAN_GOLUBEV_V_GRAHAM_SCAN_H_

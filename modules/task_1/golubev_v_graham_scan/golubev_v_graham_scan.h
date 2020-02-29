// Copyright 2020 Golubev Vladislav
#ifndef MODULES_TASK_1_GOLUBEV_V_GRAHAM_SCAN_GOLUBEV_V_GRAHAM_SCAN_H_
#define MODULES_TASK_1_GOLUBEV_V_GRAHAM_SCAN_GOLUBEV_V_GRAHAM_SCAN_H_
#include <vector>
#include <utility>


std::vector<std::pair<double, double> > generate_points(std::size_t size);
std::vector<std::pair<double, double> > get_test_set_1();
std::vector<std::pair<double, double> > get_test_set_2();
std::vector<std::pair<double, double> > get_test_set_3();

double get_polar_r(const std::pair<double, double>& point);
double get_polar_grad(const std::pair<double, double>& point);
double get_det(const std::pair<double, double>& x,
              const std::pair<double, double>& y, const std::pair<double, double>& z);

std::size_t get_lex_min(std::vector<std::pair<double, double> > v);
std::vector<std::pair<double, double> > polar_sort(std::vector<std::pair<double, double> > v);


std::vector<std::pair<double, double> > graham_scan(std::vector<std::pair<double, double> > points);


#endif  // MODULES_TASK_1_GOLUBEV_V_GRAHAM_SCAN_GOLUBEV_V_GRAHAM_SCAN_H_

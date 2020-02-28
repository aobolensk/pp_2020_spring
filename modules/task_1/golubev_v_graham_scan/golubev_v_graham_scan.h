// Copyright 2020 Golubev Vladislav
#ifndef MODULES_TASK_1_GOLUBEV_V_GRAHAM_SCAN_GOLUBEV_V_GRAHAM_SCAN_H_
#define MODULES_TASK_1_GOLUBEV_V_GRAHAM_SCAN_GOLUBEV_V_GRAHAM_SCAN_H_
#include <vector>
#include <utility>

double get_polar_r(const std::pair<double, double>& point);
double get_polar_grad(const std::pair<double, double>& point);

std::vector<std::pair<double, double> > polar_sort(std::vector<std::pair<double, double> > v);

std::vector<std::pair<double, double> > generate_points(size_t size);
std::vector<std::pair<double, double> >& graham_scan(std::vector<std::pair<double, double> > points);


#endif  // MODULES_TASK_1_GOLUBEV_V_GRAHAM_SCAN_GOLUBEV_V_GRAHAM_SCAN_H_

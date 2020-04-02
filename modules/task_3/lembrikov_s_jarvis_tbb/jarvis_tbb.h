// Copyright 2020 Lembrikov Stepan
#ifndef MODULES_TASK_3_LEMBRIKOV_S_JARVIS_TBB_JARVIS_TBB_H_
#define MODULES_TASK_3_LEMBRIKOV_S_JARVIS_TBB_JARVIS_TBB_H_

#include <tbb/tbb.h>
#include <iostream>
#include <random>
#include <vector>
#include <utility>

double length(std::pair<double, double> a, std::pair<double, double> b);
double value_of_cos(std::pair<double, double> prev, std::pair<double, double> cur, std::pair<double, double> next);

std::vector<std::pair<double, double>> getRandomPoints(int n);
std::vector<std::pair<double, double>> getNegativePoints(int n);
std::vector<std::pair<double, double>> Jarvis_Seq(std::vector<std::pair<double, double>> points);
std::vector<std::pair<double, double>> Jarvis_Tbb(std::vector<std::pair<double, double>> points, int num_thr);

#endif  // MODULES_TASK_3_LEMBRIKOV_S_JARVIS_TBB_JARVIS_TBB_H_

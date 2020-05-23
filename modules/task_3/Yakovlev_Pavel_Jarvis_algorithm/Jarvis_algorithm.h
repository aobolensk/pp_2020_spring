// Copyright 2020 Yakovlev Pavel
#ifndef MODULES_TASK_3_YAKOVLEV_PAVEL_JARVIS_ALGORITHM_JARVIS_ALGORITHM_H_
#define MODULES_TASK_3_YAKOVLEV_PAVEL_JARVIS_ALGORITHM_JARVIS_ALGORITHM_H_

#include <vector>
#include <string>
#include <utility>

std::vector<std::pair<double, double>> getRandomVectorOfPair(size_t sz);
std::vector<std::pair<double, double>> ConvexHull_Jarvis_seq(std::vector<std::pair<double, double>> points);
std::vector<std::pair<double, double>> ConvexHull_Jarvis_tbb(std::vector<std::pair<double, double>> points);

#endif  // MODULES_TASK_3_YAKOVLEV_PAVEL_JARVIS_ALGORITHM_JARVIS_ALGORITHM_H_

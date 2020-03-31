// Copyright 2020 Lembrikov Stepan
#ifndef MODULES_TASK_3_LEMBRIKOV_S_JARVIS_OMP_JARVIS_TBB_H_
#define MODULES_TASK_3_LEMBRIKOV_S_JARVIS_OMP_JARVIS_TBB_H_

#include <omp.h>
#include <iostream>
#include <random>
#include <vector>
#include <utility>
#include <tbb/tbb.h>

int func(std::vector<std::pair<double, double>> points);

void Proba_While_Tbb(std::vector<std::pair<double, double>> points);

std::vector<std::pair<double, double>> getRandomPoints(int n);
std::vector<std::pair<double, double>> getNegativePoints(int n);
std::vector<std::pair<double, double>> Jarvis_Seq(std::vector<std::pair<double, double>> points);
std::vector<std::pair<double, double>> Jarvis_Omp(std::vector<std::pair<double, double>> points, int num_threads);

#endif  // MODULES_TASK_3_LEMBRIKOV_S_JARVIS_TBB_JARVIS_TBB_H_

// Copyright 2020 Lembrikov Stepan
#ifndef MODULES_TASK_2_LEMBRIKOV_S_JARVIS_OMP_JARVIS_OMP_H_
#define MODULES_TASK_2_LEMBRIKOV_S_JARVIS_OMP_JARVIS_OMP_H_

#include <omp.h>
#include <iostream>
#include <random>
#include <vector>
#include <utility>

std::vector<std::pair<double, double>> getRandomPoints(int n);
std::vector<std::pair<double, double>> getNegativePoints(int n);
std::vector<std::pair<double, double>> Jarvis_Seq(std::vector<std::pair<double, double>> points);
std::vector<std::pair<double, double>> Jarvis_Omp(std::vector<std::pair<double, double>> points, int num_threads);

#endif  // MODULES_TASK_2_LEMBRIKOV_S_JARVIS_OMP_JARVIS_OMP_H_

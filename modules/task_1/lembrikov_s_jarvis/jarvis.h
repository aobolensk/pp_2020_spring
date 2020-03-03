// Copyright 2020 Lembrikov Stepan
#ifndef MODULES_TASK_1_LEMBRIKOV_S_JARVIS_JARVIS_H_
#define MODULES_TASK_1_LEMBRIKOV_S_JARVIS_JARVIS_H_

#include <iostream>
#include <random>
#include <vector>
#include <utility>

std::vector<std::pair<double, double>> getRandomPoints(int n);
std::vector<std::pair<double, double>> getNegativePoints(int n);
std::vector<std::pair<double, double>> Jarvis(std::vector<std::pair<double, double>> points);

#endif  // MODULES_TASK_1_LEMBRIKOV_S_JARVIS_JARVIS_H_

// Copyright 2020 Yakovlev Pavel
#include <omp.h>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <utility>
#include <iostream>
#include "../../../modules/task_1/Yakovlev_Pavel_Jarvis_algorithm/Jarvis_algorithm.h"

std::vector<std::pair<double, double>> getRandomVectorOfPair(size_t sz) {
    std::mt19937 gen(static_cast<unsigned int>(time(0)));
    std::uniform_real_distribution<> distr(100, 500);
    std::vector<std::pair<double, double>> vec(sz);
    for (size_t i = 0; i < sz; i++) { vec[i] = std::make_pair(distr(gen), distr(gen)); }
    return vec;
}

std::vector<std::pair<double, double>> ConvexHull_Jarvis(std::vector<std::pair<double, double>> points) {
    size_t sz = points.size();
    std::vector<std::pair<double, double>> convH;
    size_t firstP = 0;
    for (size_t i = 1; i < sz; i++) {
        if (points[i].second < points[firstP].second) {
            firstP = i;
        } else if (points[i].second == points[firstP].second) {
            if (points[i].first <= points[firstP].first) {
                firstP = i;
            }
        }
    }
    convH.push_back(std::make_pair(points[firstP].first, points[firstP].second));

    double maxCos = 0;
    size_t secondP = 0;
    for (size_t i = 0; i < sz; i++) {
        if (i == firstP) continue;
        double x0 = points[firstP].first;
        double y0 = points[firstP].second;
        double x1 = points[i].first;
        double y1 = points[i].second;
        double cos = (x1 - x0) / sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
        if (cos > maxCos) {
            secondP = i;
            maxCos = cos;
        }
    }
    if (secondP != firstP)
        convH.push_back(std::make_pair(points[secondP].first, points[secondP].second));

    size_t prev = firstP;
    size_t curr = secondP;
    size_t next = firstP;
    while (curr != firstP) {
        double prevX = points[prev].first;
        double prevY = points[prev].second;
        double currX = points[curr].first;
        double currY = points[curr].second;
        double minCos = 2.0;
        for (size_t i = 0; i < sz; i++) {
            if (i == curr) continue;

            double cos = ((prevX - currX) * (points[i].first - currX) + (prevY - currY) * (points[i].second - currY)) /
                sqrt(((prevX - currX) * (prevX - currX) + (prevY - currY) * (prevY - currY)) *
                ((points[i].first - currX) * (points[i].first - currX) +
                    (points[i].second - currY) * (points[i].second - currY)));

            if (cos >= -1.0 && cos <= 1.0 && cos <= minCos) {
                next = i;
                minCos = cos;
            }
        }
        if (minCos == 2.0) {
            convH.pop_back();
            break;
        }
        prev = curr;
        curr = next;
        if (next != firstP)
            convH.push_back(std::make_pair(points[next].first, points[next].second));
    }
    return convH;
}

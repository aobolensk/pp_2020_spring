// Copyright 2020 Yakovlev Pavel
#include <omp.h>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <utility>
#include <iostream>
#include "../../../modules/task_2/Yakovlev_Pavel_Jarvis_algorithm/Jarvis_algorithm.h"

#define NUM_THREADS 8

std::vector<std::pair<double, double>> getRandomVectorOfPair(size_t sz) {
    std::mt19937 gen(static_cast<unsigned int>(time(0)));
    std::uniform_real_distribution<> distr(100, 500);
    std::vector<std::pair<double, double>> vec(sz);
    for (size_t i = 0; i < sz; i++) { vec[i] = std::make_pair(distr(gen), distr(gen)); }
    return vec;
}

std::vector<std::pair<double, double>> ConvexHull_Jarvis_seq(std::vector<std::pair<double, double>> points) {
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

std::vector<std::pair<double, double>> ConvexHull_Jarvis_omp(std::vector<std::pair<double, double>> points) {
    int sz = static_cast<int>(points.size());
    std::vector<std::pair<double, double>> convH;
    omp_set_num_threads(NUM_THREADS);
    int* vecFirst = new int[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) { vecFirst[i] = 0; }
// *****************************************  FIND FIRST POINT  ******************************************
#pragma omp parallel num_threads(NUM_THREADS)
    {
        int thread = omp_get_thread_num();
#pragma omp parallel for
        for (int i = 1; i < sz; i++) {
            if (points[i].second < points[vecFirst[thread]].second) {
                vecFirst[thread] = i;
            } else if (points[i].second == points[vecFirst[thread]].second) {
                if (points[i].first <= points[vecFirst[thread]].first) {
                    vecFirst[thread] = i;
                }
            }
        }
    }

    int firstP = vecFirst[0];
    for (int i = 1; i < NUM_THREADS; i++) {
        if (points[vecFirst[i]].second < points[firstP].second) {
            firstP = i;
        } else if (points[vecFirst[i]].second == points[firstP].second) {
            if (points[vecFirst[i]].first <= points[firstP].first) {
                firstP = vecFirst[i];
            }
        }
    }
    convH.push_back(std::make_pair(points[firstP].first, points[firstP].second));

// *****************************************  FIND SECOND POINT  ******************************************
    double* vecMaxCos = new double[NUM_THREADS];
    int* vecSecondP = new int[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        vecMaxCos[i] = -2.0;
        vecSecondP[i] = 0;
    }
#pragma omp parallel num_threads(NUM_THREADS)
    {
        int thread = omp_get_thread_num();
#pragma omp parallel for
        for (int i = 0; i < sz; i++) {
            if (i == firstP) continue;
            double x0 = points[firstP].first;
            double y0 = points[firstP].second;
            double x1 = points[i].first;
            double y1 = points[i].second;
            double cos = (x1 - x0) / sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
            if (cos > vecMaxCos[thread]) {
                vecSecondP[thread] = i;
                vecMaxCos[thread] = cos;
            }
        }
    }
    int ind = 0;
    for (int i = 1; i < NUM_THREADS; i++) {
        if (vecMaxCos[ind] <= vecMaxCos[i]) {
            ind = i;
        }
    }
    int secondP = vecSecondP[ind];
    if (secondP != firstP)
        convH.push_back(std::make_pair(points[secondP].first, points[secondP].second));

// *****************************************  MAIN SCAN  ******************************************
    int prev = firstP;
    int curr = secondP;
    int next = firstP;
    double* vecMinCos = new double[NUM_THREADS];
    int* vecNext = new int[NUM_THREADS];
    while (curr != firstP) {
        double prevX = points[prev].first;
        double prevY = points[prev].second;
        double currX = points[curr].first;
        double currY = points[curr].second;
        double minCos = 2.0;

        for (int i = 0; i < NUM_THREADS; i++) {
            vecMinCos[i] = minCos;
            vecNext[i] = next;
        }
#pragma omp parallel num_threads(NUM_THREADS)
        {
            int thread = omp_get_thread_num();
#pragma omp for
            for (int i = 0; i < sz; i++) {
                if (i == curr) continue;

                double cos = ((prevX - currX) * (points[i].first - currX) +
                    (prevY - currY) * (points[i].second - currY)) /
                    sqrt(((prevX - currX) * (prevX - currX) + (prevY - currY) * (prevY - currY)) *
                    ((points[i].first - currX) * (points[i].first - currX) +
                        (points[i].second - currY) * (points[i].second - currY)));

                if (cos >= -1.0 && cos <= 1.0 && cos <= vecMinCos[thread]) {
                    vecNext[thread] = i;
                    vecMinCos[thread] = cos;
                }
            }
        }
        int ind = 0;
        for (int i = 1; i < NUM_THREADS; i++) {
            if (vecMinCos[ind] >= vecMinCos[i]) {
                ind = i;
            }
        }
        next = vecNext[ind];
        minCos = vecMinCos[ind];

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

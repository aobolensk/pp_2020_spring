// Copyright 2020 Yakovlev Pavel
#include <tbb/tbb.h>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <utility>
#include <iostream>
#include "../../../modules/task_3/Yakovlev_Pavel_Jarvis_algorithm/Jarvis_algorithm.h"

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

    double maxCos = -2.0;
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


std::vector<std::pair<double, double>> ConvexHull_Jarvis_tbb(std::vector<std::pair<double, double>> points) {
    int sz = static_cast<int>(points.size());
    if (sz == 1) return points;
    std::vector<std::pair<double, double>> convH;
// *****************************************  FIND FIRST POINT  ******************************************
    std::vector<int> vecFirst = tbb::parallel_reduce(tbb::blocked_range<int>(1, sz), std::vector<int>(),
        [&](const tbb::blocked_range<int>& r, std::vector<int> v) -> std::vector<int> {
            int firstP = 0;
            for (int i = r.begin(); i != r.end(); ++i) {
                if (points[i].second < points[firstP].second) {
                    firstP = i;
                } else if (points[i].second == points[firstP].second) {
                    if (points[i].first <= points[firstP].first) {
                        firstP = i;
                    }
                }
            }
            v.push_back(firstP);
            return v;
        },
        [](std::vector<int> v1, std::vector<int> v2) -> std::vector<int> {
            v1.insert(v1.end(), v2.cbegin(), v2.cend());
            return v1;
        });
    int firstP = vecFirst[0];
    for (int i = 1; i < static_cast<int>(vecFirst.size()); i++) {
        if (points[vecFirst[i]].second < points[firstP].second) {
            firstP = vecFirst[i];
        } else if (points[vecFirst[i]].second == points[firstP].second) {
            if (points[vecFirst[i]].first <= points[firstP].first) {
                firstP = vecFirst[i];
            }
        }
    }
    convH.push_back(std::make_pair(points[firstP].first, points[firstP].second));

// *****************************************  FIND SECOND POINT  ******************************************
    struct tmpStruct {
        std::vector<int> numP;
        std::vector<double> cos;
        tmpStruct() {}
    };

    std::vector<std::pair<int, double>> tmp(0);

    tmpStruct numCosSecondP = tbb::parallel_reduce(tbb::blocked_range<int>(0, sz), tmpStruct(),
        [&](const tbb::blocked_range<int>& r, tmpStruct v) ->tmpStruct {
        int secondP = 0;
        double maxCos = -2.0;
        for (int i = r.begin(); i != r.end(); ++i) {
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
        v.cos.push_back(maxCos);
        v.numP.push_back(secondP);
        return v;
    },
        [](tmpStruct v1, tmpStruct v2) -> tmpStruct {
        v1.cos.insert(v1.cos.end(), v2.cos.cbegin(), v2.cos.cend());
        v1.numP.insert(v1.numP.end(), v2.numP.cbegin(), v2.numP.cend());
        return v1;
    });

    int ind = 0;
    for (int i = 1; i < static_cast<int>(numCosSecondP.cos.size()); i++) {
        if (numCosSecondP.cos[ind] <= numCosSecondP.cos[i]) {
            ind = i;
        }
    }

    int secondP = numCosSecondP.numP[ind];
    if (secondP != firstP)
        convH.push_back(std::make_pair(points[secondP].first, points[secondP].second));

// *****************************************  MAIN SCAN  ******************************************
    int prev = firstP;
    int curr = secondP;
    int next = firstP;
    while (curr != firstP) {
        double minCos = 2.0;
        tmpStruct numCosNext = tbb::parallel_reduce(tbb::blocked_range<int>(0, sz), tmpStruct(),
            [&](const tbb::blocked_range<int>& r, tmpStruct v) ->tmpStruct {
            double prevX = points[prev].first;
            double prevY = points[prev].second;
            double currX = points[curr].first;
            double currY = points[curr].second;
            double tmpMinCos = 2.0;
            int copyNext = next;

            for (int i = r.begin(); i != r.end(); ++i) {
                if (i == curr) continue;

                double cos = ((prevX - currX) * (points[i].first - currX) +
                    (prevY - currY) * (points[i].second - currY)) /
                    sqrt(((prevX - currX) * (prevX - currX) + (prevY - currY) * (prevY - currY)) *
                        ((points[i].first - currX) * (points[i].first - currX) +
                            (points[i].second - currY) * (points[i].second - currY)));

                if (cos >= -1.0 && cos <= 1.0 && cos <= tmpMinCos) {
                    copyNext = i;
                    tmpMinCos = cos;
                }
            }
            v.cos.push_back(tmpMinCos);
            v.numP.push_back(copyNext);
            return v;
        },
            [](tmpStruct v1, tmpStruct v2) -> tmpStruct {
            v1.cos.insert(v1.cos.end(), v2.cos.cbegin(), v2.cos.cend());
            v1.numP.insert(v1.numP.end(), v2.numP.cbegin(), v2.numP.cend());
            return v1;
        });

        int ind = 0;
        for (int i = 1; i < static_cast<int>(numCosNext.cos.size()); i++) {
            if (numCosNext.cos[ind] >= numCosNext.cos[i]) {
                ind = i;
            }
        }
        next = numCosNext.numP[ind];
        minCos = numCosNext.cos[ind];

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

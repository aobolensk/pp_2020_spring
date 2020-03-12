// Copyright 2020 Yasakova Anastasia
#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <random>
#include <utility>
#include "../../../modules/task_1/yasakova_a_jarvis_alg/jarvis_alg.h"

std::vector < std::pair<int, int>> GetRandomPoints(int n) {
    std::vector<std::pair<int, int>> res(n);
    std::default_random_engine random;
    random.seed(static_cast<unsigned int>(std::time(0)));
    for (auto& val : res) {
        int x = random() % 199 + 1;
        int y = random() % 299 + 1;
        val = std::make_pair(x, y);
    }
    return res;
}

std::vector < std::pair<int, int>> JarvisAlg(const std::vector<std::pair<int, int>>& points) {
    std::vector<std::pair<int, int>> res;
    res.push_back(FindFirstPoint(points));
    std::pair<int, int> tmp = FindSecondPoint(points, res[0]);
    while (tmp != res[0]) {
        res.push_back(tmp);
        double min_cos = 1;
        for (const auto& val : points) {
            double curr_cos = CountCos(res[res.size() - 1], res[res.size() - 2], val);
            if (curr_cos < min_cos) {
                min_cos = curr_cos;
                tmp = val;
            } else if (curr_cos == min_cos && distance(res[res.size() - 1], val) > distance(res[res.size() - 1], tmp)) {
                tmp = val;
            }
        }
    }
    return res;
}

std::pair<int, int> FindFirstPoint(const std::vector<std::pair<int, int>>& points) {
    std::pair<int, int> res = std::make_pair(points[0].first, points[0].second);
    for (const auto& val : points) {
        if (val.second < res.second)
           res = std::make_pair(val.first, val.second);
        else if (val.second == res.second && val.first < res.first)
           res = std::make_pair(val.first, val.second);
    }
    return res;
}

std::pair<int, int> FindSecondPoint(const std::vector<std::pair<int, int>>& points, std::pair<int, int> tmp) {
    std::pair<int, int> res = std::make_pair(points[0].first, points[0].second);
    double min = 4;
    for (const auto& val : points) {
        if (val != tmp) {
            double angle = atan(static_cast<double>(val.second - tmp.second)
               / static_cast<double>(abs(val.first - tmp.first)));
            if (angle < min) {
                min = angle;
                res = val;
            } else if (angle == min && distance(tmp, val) > distance(tmp, res)) {
                res = val;
            }
        }
    }
    return res;
}

double CountCos(std::pair<int, int> a, std::pair<int, int> b, std::pair<int, int> c) {
    double res = ((b.first - a.first) * (c.first - a.first) + (b.second - a.second) * (c.second - a.second))
       / (sqrt((b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second))
            * sqrt((c.first - a.first) * (c.first - a.first) + (c.second - a.second) * (c.second - a.second)));
    return res;
}

double distance(std::pair<int, int> a, std::pair<int, int> b) {
    double res = sqrt((b.first - a.first) * (b.first - a.first) + (b.second - a.second) * (b.second - a.second));
    return res;
}

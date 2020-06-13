// Copyright 2020 Yasakova Anastasia
#include "../../../modules/task_2/yasakova_a_jarvis_alg/jarvis_alg.h"
#include <omp.h>
#include <ctime>
#include <algorithm>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

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

std::vector < std::pair<int, int>> omp_JarvisAlg(const std::vector<std::pair<int, int>>& points) {
    std::vector<std::pair<int, int>> res;
    int size = points.size();
    res.push_back(omp_FindFirstPoint(points));
    std::pair<int, int> tmp = omp_FindSecondPoint(points, res[0]);

    while (tmp != res[0]) {
        res.push_back(tmp);
        double min_cos = 1;
        int nthreads = 4;

        std::vector<std::pair<int, int>> tmp_(nthreads, tmp);
        std::vector <double> min_cos_(nthreads, min_cos);

#pragma omp parallel shared(tmp_, min_cos_) num_threads(nthreads)
        {
            int tid = omp_get_thread_num();
#pragma omp for
            for (int i = 0; i < size; ++i) {
                double curr_cos = CountCos(res[res.size() - 1], res[res.size() - 2], points[i]);
                if (curr_cos < min_cos_[tid]) {
                    min_cos_[tid] = curr_cos;
                    tmp_[tid] = points[i];
                } else if (curr_cos == min_cos_[tid] &&
                    distance(res[res.size() - 1], points[i]) > distance(res[res.size() - 1], tmp_[tid])) {
                    tmp_[tid] = points[i];
                }
            }
        }
        min_cos = min_cos_[0];
        for (int i = 0; i < nthreads; ++i) {
            if (min_cos_[i] < min_cos) {
                min_cos = min_cos_[i];
                tmp = tmp_[i];
            } else if (min_cos_[i] == min_cos
                && distance(res[res.size() - 1], tmp_[i]) > distance(res[res.size() - 1], tmp)) {
                tmp = tmp_[i];
            }
        }
    }
    return res;
}

std::pair<int, int> omp_FindFirstPoint(const std::vector<std::pair<int, int>>& points) {
    std::pair<int, int> res = points[0];
    int size = points.size();
    int nthreads = 4;
#pragma omp parallel shared(res) num_threads(nthreads)
#pragma omp for
    for (int i = 0; i < size; ++i) {
#pragma omp critical
        if (points[i].second < res.second)
            res = points[i];
        else if (points[i].second == res.second && points[i].first < res.first)
            res = points[i];
    }
    return res;
}

std::pair<int, int> omp_FindSecondPoint(const std::vector<std::pair<int, int>>& points, std::pair<int, int> tmp) {
    std::pair<int, int> res = points[0];
    double min = 4;
    int nthreads = 4;
    int size = points.size();
#pragma omp parallel shared(res, min) num_threads(nthreads)
#pragma omp for
    for (int i = 0; i < size; ++i) {
#pragma omp critical
        if (points[i] != tmp) {
            double angle = atan(static_cast<double>(points[i].second - tmp.second)
                / static_cast<double>(abs(points[i].first - tmp.first)));
            if (angle < min) {
                min = angle;
                res = points[i];
            } else if (angle == min && distance(tmp, points[i]) > distance(tmp, res)) {
                res = points[i];
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

std::vector < std::pair<int, int>> seq_JarvisAlg(const std::vector<std::pair<int, int>>& points) {
    std::vector<std::pair<int, int>> res;
    int size = points.size();
    res.push_back(seq_FindFirstPoint(points));
    std::pair<int, int> tmp = seq_FindSecondPoint(points, res[0]);
    while (tmp != res[0]) {
        res.push_back(tmp);
        double min_cos = 1;
        for (int i = 0; i < size; ++i) {
            double curr_cos = CountCos(res[res.size() - 1], res[res.size() - 2], points[i]);
            if (curr_cos < min_cos) {
                min_cos = curr_cos;
                tmp = points[i];
            } else if (curr_cos == min_cos
                && distance(res[res.size() - 1], points[i]) > distance(res[res.size() - 1], tmp)) {
                tmp = points[i];
            }
        }
    }
    return res;
}

std::pair<int, int> seq_FindFirstPoint(const std::vector<std::pair<int, int>>& points) {
    std::pair<int, int> res = points[0];
    int size = points.size();
    for (int i = 0; i < size; ++i) {
        if (points[i].second < res.second)
            res = points[i];
        else if (points[i].second == res.second && points[i].first < res.first)
            res = points[i];
    }
    return res;
}

std::pair<int, int> seq_FindSecondPoint(const std::vector<std::pair<int, int>>& points, std::pair<int, int> tmp) {
    std::pair<int, int> res = points[0];
    double min = 4;
    int size = points.size();
    for (int i = 0; i < size; ++i) {
        if (points[i] != tmp) {
            double angle = atan(static_cast<double>(points[i].second - tmp.second)
                / static_cast<double>(abs(points[i].first - tmp.first)));
            if (angle < min) {
                min = angle;
                res = points[i];
            } else if (angle == min && distance(tmp, points[i]) > distance(tmp, res)) {
                res = points[i];
            }
        }
    }
    return res;
}

// Copyright 2020 Yasakova Anastasia
#include "../../../modules/task_3/yasakova_a_jarvis_alg/jarvis_alg.h"
#include <ctime>
#include <algorithm>
#include <numeric>
#include <random>
#include <utility>
#include <vector>
#include "tbb/tbb.h"


class reduce_par {
    std::vector<std::pair<int, int>> points_;
    std::vector<std::pair<int, int>> res_;

 public:
    std::pair<int, int> res;
    double min_cos;

    reduce_par(std::vector<std::pair<int, int>> points, std::vector<std::pair<int, int>> res)
        : points_(points), res_(res), res(std::make_pair(0, 0)), min_cos(1) {}
    reduce_par(reduce_par& r, tbb::split) : points_(r.points_), res_(r.res_), res(std::make_pair(0, 0)), min_cos(1) {}

    void operator()(const tbb::blocked_range<size_t>& r) {
        std::pair<int, int> local_res = res;
        double local_min_cos = min_cos;
        std::vector<std::pair<int, int>> resloc = res_;
        std::vector<std::pair<int, int>> pointsloc = points_;
        size_t start = r.begin(), end = r.end();
            for (size_t i = start; i != end; ++i) {
            double curr_cos = CountCos(resloc[resloc.size() - 1], resloc[resloc.size() - 2], pointsloc[i]);
            if (curr_cos < local_min_cos) {
                local_min_cos = curr_cos;
                local_res = pointsloc[i];
            } else if (curr_cos == local_min_cos
                  && distance(resloc[resloc.size() - 1], pointsloc[i]) >
               distance(resloc[resloc.size() - 1], local_res)) {
                local_res = pointsloc[i];
            }
        }
        res = local_res;
        min_cos = local_min_cos;
    }

    void join(const reduce_par& r) {
        if (r.min_cos < min_cos) {
            min_cos = r.min_cos;
            res = r.res;
        } else if (r.min_cos == min_cos && distance(res_[res_.size() - 1], r.res) >
            distance(res_[res_.size() - 1], res)) {
            res = r.res;
        }
    }
};


std::vector < std::pair<int, int>> GetRandomPoints(int n) {
    std::vector<std::pair<int, int>> res(n);
    std::default_random_engine random;
    random.seed(static_cast<unsigned int>(std::time(0)));
    for (auto& val : res) {
        int x = random() % 199 + 1;
        int y = random() % 399 + 1;
        val = std::make_pair(x, y);
    }
    return res;
}


std::vector < std::pair<int, int>> tbb_JarvisAlg(const std::vector<std::pair<int, int>>& points) {
    std::vector<std::pair<int, int>> res;
    int size = points.size();
    res.push_back(seq_FindFirstPoint(points));
    std::pair<int, int> tmp = seq_FindSecondPoint(points, res[0]);

    while (tmp != res[0]) {
        res.push_back(tmp);
        reduce_par r(points, res);
        tbb::parallel_reduce(tbb::blocked_range<size_t>(0, size), r);
        tmp = r.res;
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

// Copyright 2020 Yasakova Anastasia
#include "../../../modules/task_3/yasakova_a_jarvis_alg/jarvis_alg.h"
#include <ctime>
#include <algorithm>
#include <numeric>
#include <random>
#include <utility>
#include <vector>
#include <iostream>
#include "tbb/tbb.h"


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
    tbb::concurrent_vector<std::pair<int, int>> res_;
    int size = points.size();
    int nth = 4;
    if (size - 2 < nth) {
         res = seq_JarvisAlg(points);
    } else {
        std::pair<int, int> tmp1 = tbb_FindFirstPoint(points);
        std::pair<int, int> tmp2 = tbb_FindSecondPoint(points, tmp1);
        size = points.size();
        tbb::task_scheduler_init init(nth);
        std::vector<std::pair<int, int>> res_ = tbb::parallel_reduce(tbb::blocked_range<int>(0, size,
            size / nth + size % nth), std::vector<std::pair<int, int>>(),
            [&](const tbb::blocked_range<int>& r, std::vector<std::pair<int, int>> res_general)
            -> std::vector<std::pair<int, int>> {
            std::vector<std::pair<int, int>> res_loc;
            res_loc.push_back(tmp1);
            std::pair<int, int> tmp = tmp2;
            while (tmp != res_loc[0]) {
                res_loc.push_back(tmp);
                double min_cos = 1, curr_cos = 1;
                for (int i = r.begin(); i < r.end(); ++i) {
                    curr_cos = CountCos(res_loc[res_loc.size() - 1], res_loc[res_loc.size() - 2], points[i]);
                    if (curr_cos < min_cos) {
                        min_cos = curr_cos;
                        tmp = points[i];
                    } else if (curr_cos == min_cos && distance(res_loc[res_loc.size() - 1],
                        points[i]) > distance(res_loc[res_loc.size() - 1], tmp)) {
                        tmp = points[i];
                    }
                }
                curr_cos = CountCos(res_loc[res_loc.size() - 1], res_loc[res_loc.size() - 2], res_loc[0]);
                if (curr_cos < min_cos) {
                    min_cos = curr_cos;
                    tmp = res_loc[0];
                } else if (curr_cos == min_cos
                    && distance(res_loc[res_loc.size() - 1], res_loc[0]) > distance(res_loc[res_loc.size() - 1], tmp)) {
                    tmp = res_loc[0];
                }
            }
            std::copy(res_loc.begin() + 2, res_loc.end(), std::back_inserter(res_general));
            return res_general;
        },
            [](std::vector<std::pair<int, int>> r1, std::vector<std::pair<int, int>> r2)
            -> std::vector<std::pair<int, int>> {
            std::copy(r2.begin(), r2.end(), std::back_inserter(r1));
            return r1;
        });
        init.terminate();
        res_.push_back(tmp1);
        res_.push_back(tmp2);
        int size_ = res_.size();
        res.push_back(tmp1);
        std::pair<int, int> tmp = tmp2;
        while (tmp != res[0]) {
            res.push_back(tmp);
            double min_cos = 1;
            for (int i = 0; i < size_; ++i) {
                double curr_cos = CountCos(res[res.size() - 1], res[res.size() - 2], res_[i]);
                if (curr_cos < min_cos) {
                    min_cos = curr_cos;
                    tmp = res_[i];
                } else if (curr_cos == min_cos
                    && distance(res[res.size() - 1], res_[i]) > distance(res[res.size() - 1], tmp)) {
                    tmp = res_[i];
                }
            }
        }
    }
    return res;
}

std::pair<int, int> tbb_FindFirstPoint(const std::vector<std::pair<int, int>>& points) {
    std::pair<int, int> res = points[0];
    int size = points.size();
    int nth = 4;
    tbb::task_scheduler_init init(nth);
    std::vector<std::pair<int, int>> res_ = tbb::parallel_reduce(tbb::blocked_range<int>(0,
        size, size / nth + size % nth), std::vector<std::pair<int, int>>(),
        [&](const tbb::blocked_range<int>& r, std::vector<std::pair<int, int>> res_general)
        -> std::vector<std::pair<int, int>> {
        std::pair<int, int> res_loc = points[r.begin()];
        for (int i = r.begin() + 1; i < r.end(); ++i) {
            if (points[i].second < res_loc.second)
                res_loc = points[i];
            else if (points[i].second == res_loc.second && points[i].first < res_loc.first)
                res_loc = points[i];
        }
        res_general.push_back(res_loc);
        return res_general;
    },
        [](std::vector<std::pair<int, int>> r1, std::vector<std::pair<int, int>> r2)
        -> std::vector<std::pair<int, int>> {
        std::copy(r2.begin(), r2.end(), std::back_inserter(r1));
        return r1;
    });
    init.terminate();
    res = res_[0];
    int size_ = res_.size();
    for (int i = 0; i < size_; ++i) {
        if (res_[i].second < res.second)
            res = res_[i];
        else if (res_[i].second == res.second && res_[i].first < res.first)
            res = res_[i];
    }
    return res;
}

std::pair<int, int> tbb_FindSecondPoint(const std::vector<std::pair<int, int>>& points, std::pair<int, int> tmp) {
    std::pair<int, int> res = points[0];
    double min = 4;
    int size = points.size();
    int nth = 4;
    tbb::task_scheduler_init init(nth);
    std::vector<std::pair<int, int>> res_ = tbb::parallel_reduce(tbb::blocked_range<int>(0, size,
        size / nth + size % nth), std::vector<std::pair<int, int>>(),
        [&](const tbb::blocked_range<int>& r, std::vector<std::pair<int, int>> res_general)
        -> std::vector<std::pair<int, int>> {
        std::pair<int, int> res_loc = points[r.begin()];
        double min_ = 4;
        for (int i = r.begin(); i < r.end(); ++i) {
            if (points[i] != tmp) {
                double angle = atan(static_cast<double>(points[i].second - tmp.second)
                    / static_cast<double>(abs(points[i].first - tmp.first)));
                if (angle < min_) {
                    min_ = angle;
                    res_loc = points[i];
                } else if (angle == min_ && distance(tmp, points[i]) > distance(tmp, res_loc)) {
                    res_loc = points[i];
                }
            }
        }
        res_general.push_back(res_loc);
        return res_general;
    },
        [](std::vector<std::pair<int, int>> r1, std::vector<std::pair<int, int>> r2)
        -> std::vector<std::pair<int, int>> {
        std::copy(r2.begin(), r2.end(), std::back_inserter(r1));
        return r1;
    });
    init.terminate();
    res = res_[0];
    min = 4;
    int size_ = res_.size();
    for (int i = 0; i < size_; ++i) {
        double angle = atan(static_cast<double>(res_[i].second - tmp.second)
            / static_cast<double>(abs(res_[i].first - tmp.first)));
        if (angle < min) {
            min = angle;
            res = res_[i];
        } else if (angle == min && distance(tmp, res_[i]) > distance(tmp, res)) {
            res = res_[i];
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

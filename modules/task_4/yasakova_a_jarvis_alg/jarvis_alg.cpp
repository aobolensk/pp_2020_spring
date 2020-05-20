// Copyright 2020 Yasakova Anastasia
#include "../../../modules/task_4/yasakova_a_jarvis_alg/jarvis_alg.h"
#include <ctime>
#include <algorithm>
#include <numeric>
#include <random>
#include <utility>
#include <vector>
#include <thread>
#include <iostream>
#include <mutex>



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

std::vector < std::pair<int, int>> std_JarvisAlg(const std::vector<std::pair<int, int>>& points) {
    std::vector<std::pair<int, int>> res;
    int size = points.size();
    res.push_back(std_FindFirstPoint(points));
    std::pair<int, int> tmp = seq_FindSecondPoint(points, res[0]);
    int nth = std::min(8, size);
    std::vector<std::thread> t(nth);
    while (tmp != res[0]) {
        res.push_back(tmp);
        std::vector<std::pair<int, int>> tmp_(nth, res[0]);
        std::vector<double> min_cos_(nth, 1);
        int num = 0, cnt = size / nth, rest = size - cnt * nth;
        for (int i = 0; i < nth; ++i) {
            int count = cnt;
            if (i == nth - 1)
                count += rest;
            t[i] = std::thread([&](int cnt, int num, int j) {
                for (int i = num; i < num + cnt; ++i) {
                     double curr_cos = CountCos(res[res.size() - 1], res[res.size() - 2], points[i]);
                     if (curr_cos < min_cos_[j]) {
                         min_cos_[j] = curr_cos;
                         tmp_[j] = points[i];
                     } else if (curr_cos == min_cos_[j]
                          && distance(res[res.size() - 1], points[i]) > distance(res[res.size() - 1], tmp_[j])) {
                          tmp_[j] = points[i];
                     }
                }
            }, count, num, i);
            num += cnt;
        }
        double min_cos = min_cos_[0];
        tmp = tmp_[0];
        for (int i = 0; i < nth; ++i) {
            t[i].join();
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

std::pair<int, int> std_FindFirstPoint(const std::vector<std::pair<int, int>>& points) {
    int size = points.size();
    int nth = std::min(8, size);
    std::vector<std::thread> t(nth);
    std::pair<int, int> res = points[0];
    std::vector<std::pair<int, int>> res_(nth, points[0]);
    int cnt = size / nth, num = 0, rest = size - nth * cnt;
    for (int i = 0; i < nth; ++i) {
        int count = cnt;
        if (i == nth - 1)
            count += rest;
        t[i] = std::thread([&](int cnt, int num, int j) {
           for (int k = num; k < num + cnt; ++k) {
               if (points[k].second < res_[j].second)
                    res_[j] = points[k];
               else if (points[k].second == res_[j].second && points[k].first < res_[j].first)
                    res_[j] = points[k];
           }
        }, count, num, i);
        num += cnt;
    }
    res = res_[0];
    for (int i = 0; i < nth; ++i) {
        t[i].join();
        if (res_[i].second < res.second)
            res = res_[i];
        else if (res_[i].second == res.second && res_[i].first < res.first)
            res = res_[i];
    }
    return res;
}

std::pair<int, int> std_FindSecondPoint(const std::vector<std::pair<int, int>>& points, std::pair<int, int> tmp) {
    std::pair<int, int> res = points[0];
    double min = 4;
    int size = points.size();
    int nth = std::min(8, size);
    std::vector<std::thread> t(nth);
    std::vector<std::pair<int, int>> res_(nth, points[0]);
    int cnt = size / nth, num = 0, rest = size - nth * cnt;
    for (int i = 0; i < nth; ++i) {
        int count = cnt;
        if (i == nth - 1)
            count += rest;
        t[i] = std::thread([&](int cnt, int num, int j) {
            for (int i = num; i < num + cnt; ++i) {
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
        }, count, num, i);
        num += cnt;
    }
    min = 4;
    for (int i = 0; i < nth; ++i) {
        t[i].join();
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

std::vector <std::pair<int, int>> seq_JarvisAlg(const std::vector<std::pair<int, int>>& points) {
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

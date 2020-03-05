// Copyright 2020 Lembrikov Stepan
#include <../../../modules/task_1/lembrikov_s_jarvis/jarvis.h>
#include <omp.h>
#include <vector>
#include <utility>

std::vector<std::pair<double, double>> getRandomPoints(int n) {
    std::mt19937 engine;
    std::vector<std::pair<double, double>> a(n);
    engine.seed(n);
    for (int i = 0; i < n; i++) {
        a[i].first = engine() % 100;
        a[i].second = engine() % 100;
    }
    return a;
}

std::vector<std::pair<double, double>> getNegativePoints(int n) {
    std::mt19937 engine;
    std::vector<std::pair<double, double>> a(n);
    engine.seed(n);
    for (int i = 0; i < n; i++) {
        a[i].first = engine() % 100;
        a[i].second = engine() % 100;
        a[i].first *= -1;
        a[i].second *= -1;
    }
    return a;
}

std::vector<std::pair<double, double>> Jarvis(std::vector<std::pair<double, double>> points) {
    size_t size = points.size();
    size_t base_id = 0;
    std::vector<std::pair<double, double>> Convex_Hull(1);
    std::pair<double, double> cur_p;
    std::pair<double, double> prev_p;

    for (size_t i = 1; i < size; i++) {
        if (points[i].second < points[base_id].second) {
            base_id = i;
        } else if ((points[i].second == points[base_id].second) && (points[i].first < points[base_id].first)) {
            base_id = i;
        }
    }

    Convex_Hull[0] = points[base_id];
    cur_p = Convex_Hull[0];
    prev_p.first = Convex_Hull[0].first - 1;
    prev_p.second = Convex_Hull[0].second;

    double len1;
    double len2;
    double max_len = 0;
    double scalar;
    double cur_cos;
    double min_cos = 1.1;
    size_t next = 0;
    size_t flag_h = 1;

    do {
        min_cos = 1.1;
        for (size_t i = 0; i < size; i++) {
            len1 = sqrt(pow((prev_p.first - cur_p.first), 2) + pow((prev_p.second - cur_p.second), 2));
            len2 = sqrt(pow((points[i].first - cur_p.first), 2) + pow((points[i].second - cur_p.second), 2));
            scalar = ((prev_p.first - cur_p.first) * (points[i].first - cur_p.first) +
                (prev_p.second - cur_p.second) * (points[i].second - cur_p.second));
            cur_cos = scalar / len1 / len2;
            if (cur_cos < min_cos) {
                min_cos = cur_cos;
                max_len = len2;
                next = i;
            } else if (cur_cos == min_cos) {
                if (max_len < len2) {
                    next = i;
                    max_len = len2;
                }
            }
        }
        Convex_Hull.push_back(points[next]);
        flag_h++;
        prev_p.first = cur_p.first;
        prev_p.second = cur_p.second;
        cur_p = points[next];
    } while (cur_p != Convex_Hull[0]);

    if (flag_h > 1) {
        flag_h--;
        Convex_Hull.pop_back();
    }

    return Convex_Hull;
}

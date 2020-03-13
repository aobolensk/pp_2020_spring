// Copyright 2020 Lembrikov Stepan
#include <../../../modules/task_2/lembrikov_s_jarvis_omp/jarvis_omp.h>
#include <omp.h>
#include <vector>
#include <utility>
#include <ctime>

std::vector<std::pair<double, double>> getRandomPoints(int n) {
    std::vector<std::pair<double, double>> a(n);
    std::mt19937 gen(n);
    std::uniform_real_distribution<> urd(0, 100);
    for (int i = 0; i < n; i++) {
        a[i].first = urd(gen);
        a[i].second = urd(gen);
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

std::vector<std::pair<double, double>> Jarvis_Seq(std::vector<std::pair<double, double>> points) {
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

std::vector<std::pair<double, double>> Jarvis_Omp(std::vector<std::pair<double, double>> points, int num_thr) {
    size_t size = points.size();
    size_t base_id = 0;
    std::vector<std::pair<double, double>> Convex_Hull(1);
    std::vector<std::vector<int>> Local_Convex_Hulls(num_thr);
    std::pair<double, double> base_p;
    std::pair<double, double> cur_p;
    std::pair<double, double> prev_p;
    int tid;
    int k;
    int ostatok;

    k = size / num_thr;

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
    base_p = Convex_Hull[0];

    double len1;
    double len2;
    double max_len = 0;
    double scalar;
    double cur_cos;
    double min_cos = 1.1;
    int ost_for_last;
    size_t next = 0;
    size_t flag_h = 1;
    std::vector<std::pair<double, double>> part_of_points;

    if (size == 1) {
        return Convex_Hull;
    } else if (size == 2) {
        if (points[0] == points[1]) {
            return Convex_Hull;
        } else if (points[0] != points[1]) {
            return points;
        }
    }

#pragma omp parallel private(tid, min_cos, len1, len2, scalar, cur_cos, next, max_len, part_of_points, ostatok, \
prev_p, cur_p, flag_h) shared(size, Local_Convex_Hulls, points, base_id, k) num_threads(num_thr)
    {
        tid = omp_get_thread_num();
        next = 0;
        flag_h = 1;
        cur_p = Convex_Hull[0];
        prev_p.first = Convex_Hull[0].first - 1;
        prev_p.second = Convex_Hull[0].second;

        if (tid == num_thr - 1) {
            ostatok = size % num_thr;
        } else {
            ostatok = 0;
        }

        do {
            min_cos = 1.1;

            for (size_t i = tid * k; i < ((tid + 1) * k) + ostatok; i++) {
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

            len1 = sqrt(pow((prev_p.first - cur_p.first), 2) + pow((prev_p.second - cur_p.second), 2));
            len2 = sqrt(pow((base_p.first - cur_p.first), 2) + pow((base_p.second - cur_p.second), 2));
            scalar = ((prev_p.first - cur_p.first) * (base_p.first - cur_p.first) +
                (prev_p.second - cur_p.second) * (base_p.second - cur_p.second));
            cur_cos = scalar / len1 / len2;

            if (cur_cos < min_cos) {
                next = base_id;
            } else if (cur_cos == min_cos) {
                if (max_len < len2) {
                    next = base_id;
                }
            }

            if (next == base_id)
                break;
            Local_Convex_Hulls[tid].push_back(next);
            prev_p.first = cur_p.first;
            prev_p.second = cur_p.second;
            cur_p = points[next];
        } while (base_id != next);
    }

    std::vector<std::pair<double, double>> points_last;
    int razmer_mas_i;
    int razmer_mas = 1;

    points_last.push_back(base_p);
    for (size_t i = 0; i < num_thr; i++) {
        razmer_mas_i = Local_Convex_Hulls[i].size();
        points_last.resize(razmer_mas + razmer_mas_i);
        for (size_t j = 0; j < razmer_mas_i; j++) {
            cur_p = points[Local_Convex_Hulls[i][j]];
            points_last[razmer_mas + j] = cur_p;
        }
        razmer_mas += razmer_mas_i;
    }

    next = 0;
    flag_h = 1;
    max_len = 0;
    cur_p = Convex_Hull[0];
    prev_p.first = Convex_Hull[0].first - 1;
    prev_p.second = Convex_Hull[0].second;

    do {
        min_cos = 1.1;
        for (size_t i = 0; i < razmer_mas; i++) {
            len1 = sqrt(pow((prev_p.first - cur_p.first), 2) + pow((prev_p.second - cur_p.second), 2));
            len2 = sqrt(pow((points_last[i].first - cur_p.first), 2) + pow((points_last[i].second - cur_p.second), 2));
            scalar = ((prev_p.first - cur_p.first) * (points_last[i].first - cur_p.first) +
                (prev_p.second - cur_p.second) * (points_last[i].second - cur_p.second));
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
        Convex_Hull.push_back(points_last[next]);
        flag_h++;
        prev_p.first = cur_p.first;
        prev_p.second = cur_p.second;
        cur_p = points_last[next];
    } while (cur_p != Convex_Hull[0]);

    if (flag_h > 1) {
        flag_h--;
        Convex_Hull.pop_back();
    }

    return Convex_Hull;
}

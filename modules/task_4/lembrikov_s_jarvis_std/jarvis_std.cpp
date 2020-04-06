// Copyright 2020 Lembrikov Stepan
#include <../../../modules/task_4/lembrikov_s_jarvis_std/jarvis_std.h>
#include <thread>
#include <mutex>
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

std::vector<std::pair<double, double>> Jarvis_Std(std::vector<std::pair<double, double>> points, int nu_th) {
    size_t size = points.size();
    size_t base_id = 0;
    std::vector<std::pair<double, double>> Convex_Hull(1);
    std::vector<std::vector<int>> Local_Convex_Hulls(nu_th);
    std::pair<double, double> base_p;
    std::pair<double, double> cur_p;
    std::pair<double, double> pr_p;
    std::thread* threads = new std::thread[nu_th];
    int k;
    int ost = size % nu_th;;

    k = size / nu_th;

    for (size_t i = 1; i < size; i++) {
        if (points[i].second < points[base_id].second) {
            base_id = i;
        } else if ((points[i].second == points[base_id].second) && (points[i].first < points[base_id].first)) {
            base_id = i;
        }
    }

    Convex_Hull[0] = points[base_id];
    cur_p = Convex_Hull[0];
    pr_p.first = Convex_Hull[0].first - 1;
    pr_p.second = Convex_Hull[0].second;
    base_p = Convex_Hull[0];

    double len1;
    double len2;
    double mx_ln;
    double scalar;
    double cur_cos;
    double mn_cs = 1.1;
    size_t next = 0;
    size_t flag_h = 1;

    if (size == 1) {
        return Convex_Hull;
    } else if (size == 2) {
        if (points[0] == points[1]) {
            return Convex_Hull;
        } else if (points[0] != points[1]) {
            return points;
        }
    }
    std::mutex _lock;
    for (int i = 0; i < nu_th; i++) {
        threads[i] = std::thread([&](int begin, int end, const int tid) {
            int base_idd;
            std::pair<double, double> cur_p;
            std::pair<double, double> pr_p;
            double len1;
            double len2;
            double scalar;
            double cur_cos;
            int next = 0;
            double mn_cs;
            double mx_ln = 0;
            _lock.lock();
            base_idd = base_id;
            cur_p = Convex_Hull[0];
            pr_p.first = Convex_Hull[0].first - 1;
            pr_p.second = Convex_Hull[0].second;
            _lock.unlock();
            if (tid == nu_th - 1)
                end += ost;

            do {
                mn_cs = 1.1;

                for (int i = begin; i < end; ++i) {
                    len1 = sqrt(pow((pr_p.first - cur_p.first), 2) + pow((pr_p.second - cur_p.second), 2));
                    len2 = sqrt(pow((points[i].first - cur_p.first), 2) + pow((points[i].second - cur_p.second), 2));
                    scalar = ((pr_p.first - cur_p.first) * (points[i].first - cur_p.first) +
                        (pr_p.second - cur_p.second) * (points[i].second - cur_p.second));
                    cur_cos = scalar / len1 / len2;

                    if (cur_cos < mn_cs) {
                        mn_cs = cur_cos;
                        mx_ln = len2;
                        next = i;
                    }
                    else if (cur_cos == mn_cs) {
                        if (mx_ln < len2) {
                            next = i;
                            mx_ln = len2;
                        }
                    }
                }

                len1 = sqrt(pow((pr_p.first - cur_p.first), 2) + pow((pr_p.second - cur_p.second), 2));
                len2 = sqrt(pow((base_p.first - cur_p.first), 2) + pow((base_p.second - cur_p.second), 2));
                scalar = ((pr_p.first - cur_p.first) * (base_p.first - cur_p.first) +
                    (pr_p.second - cur_p.second) * (base_p.second - cur_p.second));
                cur_cos = scalar / len1 / len2;

                if (cur_cos < mn_cs) {
                    next = base_idd;
                }
                else if (cur_cos == mn_cs) {
                    if (mx_ln < len2) {
                        next = base_idd;
                    }
                }

                if (next == base_idd)
                    break;
                _lock.lock();
                Local_Convex_Hulls[tid].push_back(next);
                _lock.unlock();
                pr_p.first = cur_p.first;
                pr_p.second = cur_p.second;
                cur_p = points[next];
            } while (base_idd != next);
        }, i * k, i * k + k, i);
    }

    for (int i = 0; i < nu_th; ++i) {
        threads[i].join();
    }

    std::vector<std::pair<double, double>> points_last;
    int razmer_mas_i;
    int razmer_mas = 1;

    points_last.push_back(base_p);
    for (int i = 0; i < nu_th; i++) {
        razmer_mas_i = Local_Convex_Hulls[i].size();
        points_last.resize(razmer_mas + razmer_mas_i);
        for (int j = 0; j < razmer_mas_i; j++) {
            cur_p = points[Local_Convex_Hulls[i][j]];
            points_last[razmer_mas + j] = cur_p;
        }
        razmer_mas += razmer_mas_i;
    }

    next = 0;
    flag_h = 1;
    mx_ln = 0;
    cur_p = Convex_Hull[0];
    pr_p.first = Convex_Hull[0].first - 1;
    pr_p.second = Convex_Hull[0].second;

    do {
        mn_cs = 1.1;
        for (int i = 0; i < razmer_mas; i++) {
            len1 = sqrt(pow((pr_p.first - cur_p.first), 2) + pow((pr_p.second - cur_p.second), 2));
            len2 = sqrt(pow((points_last[i].first - cur_p.first), 2) + pow((points_last[i].second - cur_p.second), 2));
            scalar = ((pr_p.first - cur_p.first) * (points_last[i].first - cur_p.first) +
                (pr_p.second - cur_p.second) * (points_last[i].second - cur_p.second));
            cur_cos = scalar / len1 / len2;
            if (cur_cos < mn_cs) {
                mn_cs = cur_cos;
                mx_ln = len2;
                next = i;
            } else if (cur_cos == mn_cs) {
                if (mx_ln < len2) {
                    next = i;
                    mx_ln = len2;
                }
            }
        }
        Convex_Hull.push_back(points_last[next]);
        flag_h++;
        pr_p.first = cur_p.first;
        pr_p.second = cur_p.second;
        cur_p = points_last[next];
    } while (cur_p != Convex_Hull[0]);

    if (flag_h > 1) {
        flag_h--;
        Convex_Hull.pop_back();
    }

    return Convex_Hull;
}
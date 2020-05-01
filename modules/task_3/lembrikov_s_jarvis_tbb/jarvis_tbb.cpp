// Copyright 2020 Lembrikov Stepan
#include <../../../modules/task_3/lembrikov_s_jarvis_tbb/jarvis_tbb.h>
#include <vector>
#include <utility>
#include <ctime>
#include <algorithm>

std::vector<std::pair<double, double>> getRandomPoints(int n) {
    std::vector<std::pair<double, double>> a(n);
    std::mt19937 gen(n);
    std::uniform_int_distribution<int> urd(0, 1000000);
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

double length(std::pair<double, double> a, std::pair<double, double> b) {
    std::pair<double, double> fst_p;
    std::pair<double, double> sec_p;
    double len;
    fst_p = a;
    sec_p = b;

    len = sqrt(pow((a.first - b.first), 2) + pow((a.second - b.second), 2));

    return len;
}

double value_of_cos(std::pair<double, double> prev, std::pair<double, double> cur, std::pair<double, double> next) {
    double len1;
    double len2;
    double scalar;
    double cos;
    std::pair<double, double> cur_p;
    std::pair<double, double> prev_p;
    std::pair<double, double> next_p;

    cur_p = cur;
    prev_p = prev;
    next_p = next;

    len1 = length(prev_p, cur_p);
    len2 = length(next_p, cur_p);
    scalar = ((prev_p.first - cur_p.first) * (next_p.first - cur_p.first) +
        (prev_p.second - cur_p.second) * (next_p.second - cur_p.second));
    if ((len1 == 0) || (len2 == 0))
        cos = 1.1;
    else
        cos = scalar / len1 / len2;

    return cos;
}

class reduce_par {
 public:
    int next;
    double len;
    std::vector<std::pair<double, double>> points;
    tbb::concurrent_vector<std::pair<double, double>> Convex_Hull;
    std::pair<double, double > pr_p;
    std::pair<double, double > cur_p;
    int base_id;
    std::pair<double, double> base_po;

    void operator()(const tbb::blocked_range<size_t> &r) {
        double cos = 1.1;
        double min_local = cos;
        double len1 = 0;
        double len2 = 0;
        double scalar = 0;
        double cur_cos = 0;
        int flag_h = 1;
        std::vector<std::pair<double, double>> xloc = points;
        std::vector<std::pair<double, double>> Convex_Hull_Local;

        std::pair<double, double> base_p = base_po;
        std::pair<double, double> prev_p = pr_p;

        Convex_Hull_Local.push_back(base_p);
        size_t begin = r.begin();
        size_t end = r.end();
        do {
            min_local = 1.1;
            for (size_t i = begin; i != end; ++i) {
                len1 = sqrt(pow((prev_p.first - cur_p.first), 2) + pow((prev_p.second - cur_p.second), 2));
                len2 = sqrt(pow((xloc[i].first - cur_p.first), 2) + pow((xloc[i].second - cur_p.second), 2));
                scalar = ((prev_p.first - cur_p.first) * (xloc[i].first - cur_p.first) +
                    (prev_p.second - cur_p.second) * (xloc[i].second - cur_p.second));

                if ((len1 == 0) || (len2 == 0))
                    cur_cos = 1.1;
                else
                    cur_cos = scalar / len1 / len2;

                if (cur_cos < min_local) {
                    min_local = cur_cos;
                    len = len2;
                    next = i;
                } else if (cur_cos == min_local) {
                    if (len < len2) {
                        next = i;
                        len = len2;
                    }
                }
            }
            cur_cos = value_of_cos(prev_p, cur_p, base_p);
            if (cur_cos < min_local) {
                next = base_id;
            } else if (cur_cos == min_local) {
                if (len < len2) {
                    next = base_id;
                }
            }
            Convex_Hull_Local.push_back(xloc[next]);
            flag_h++;
            prev_p.first = cur_p.first;
            prev_p.second = cur_p.second;
            cur_p = xloc[next];
        } while (cur_p != Convex_Hull_Local[0]);

        if (flag_h > 1) {
            flag_h--;
            Convex_Hull_Local.pop_back();
        }

        std::copy(Convex_Hull_Local.begin(), Convex_Hull_Local.end(), std::back_inserter(Convex_Hull));
    }

    reduce_par(const reduce_par& r, tbb::split) :
        points(r.points), Convex_Hull(r.Convex_Hull),
        pr_p(r.pr_p), cur_p(r.cur_p), base_id(r.base_id), base_po(r.base_po) {}

    void join(const reduce_par& r) {
        std::copy(r.Convex_Hull.begin(), r.Convex_Hull.end(), std::back_inserter(Convex_Hull));
    }

    reduce_par(std::vector<std::pair<double, double>> x, tbb::concurrent_vector<std::pair<double, double>> l,
        std::pair<double, double> y, std::pair<double, double> z, int id, std::pair<double, double> p) :
        next(0), len(0), points(x), Convex_Hull(l), pr_p(y), cur_p(z), base_id(id), base_po(p) {}
};

tbb::concurrent_vector<std::pair<double, double>> Jarvis_Tbb(std::vector<std::pair<double, double>> points,
    int num_thr) {
    size_t size = points.size();
    size_t base_id = 0;
    tbb::concurrent_vector<std::pair<double, double>> Convex_Hull(1);
    std::pair<double, double> cur_p;
    std::pair<double, double> prev_p;

    if (size < 3) {
        std::vector<std::pair<double, double>> Convex_Hull_Seq;
        Convex_Hull_Seq = Jarvis_Seq(points);
        std::copy(Convex_Hull_Seq.begin(), Convex_Hull_Seq.end(), Convex_Hull.begin());
    } else {
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
        int flag_h = 1;
        std::pair<double, double> base_p = cur_p;
        reduce_par r(points, Convex_Hull, prev_p, cur_p, base_id, base_p);
        tbb::task_scheduler_init init(num_thr);
        int grainsize = size / num_thr + size % num_thr;
        tbb::parallel_reduce(tbb::blocked_range<size_t>(0, size, grainsize), r);
        init.terminate();

        std::vector<std::pair<double, double>> points_last;
        int razmer_mas = 1;

        razmer_mas = r.Convex_Hull.size();
        points_last.resize(razmer_mas);
        for (int j = 0; j < razmer_mas; j++) {
            points_last[j] = r.Convex_Hull[j];
        }

        std::pair<double, double > pr_p;
        int next = 0;
        flag_h = 1;
        double mx_ln = 0;
        double mn_cs;
        double len1;
        double len2;
        double scalar;
        double cur_cos;
        double buf;
        cur_p = r.Convex_Hull[0];
        pr_p.first = Convex_Hull[0].first - 1;
        pr_p.second = Convex_Hull[0].second;
        do {
            mn_cs = 1.1;
            for (int i = 0; i < razmer_mas; i++) {
                len1 = sqrt(pow((pr_p.first - cur_p.first), 2) + pow((pr_p.second - cur_p.second), 2));
                buf = pow((points_last[i].first - cur_p.first), 2) + pow((points_last[i].second - cur_p.second), 2);
                len2 = sqrt(buf);
                scalar = ((pr_p.first - cur_p.first) * (points_last[i].first - cur_p.first) +
                    (pr_p.second - cur_p.second) * (points_last[i].second - cur_p.second));
                if ((len1 == 0) || (len2 == 0))
                    cur_cos = 1.1;
                else
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
    }

    return Convex_Hull;
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

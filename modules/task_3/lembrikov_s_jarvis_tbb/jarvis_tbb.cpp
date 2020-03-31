// Copyright 2020 Lembrikov Stepan
#include <../../../modules/task_3/lembrikov_s_jarvis_tbb/jarvis_tbb.h>
#include <omp.h>
#include <vector>
#include <utility>
#include <ctime>
#include <algorithm>

using namespace tbb;

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

class reduce_par {
public:
    double cos;
    int next;
    double len;

    void operator()(const blocked_range<size_t> &r)
    {
        double min_local = cos;
        double len1;
        double len2;
        double scalar;
        double cur_cos;
        std::vector<std::pair<double, double>> xloc = points;
        size_t end = r.end();
        for (size_t i = r.begin(); i != end; ++i) {
            len1 = sqrt(pow((prev_p.first - cur_p.first), 2) + pow((prev_p.second - cur_p.second), 2));
            len2 = sqrt(pow((points[i].first - cur_p.first), 2) + pow((points[i].second - cur_p.second), 2));
            scalar = ((prev_p.first - cur_p.first) * (points[i].first - cur_p.first) +
                (prev_p.second - cur_p.second) * (points[i].second - cur_p.second));
            cur_cos = scalar / len1 / len2;
            if (cur_cos < min_local) {
                min_local = cur_cos;
                len = len2;
                next = i;
            }
            else if (cur_cos == min_local) {
                if (len < len2) {
                    next = i;
                    len = len2;
                }
            }

            //if (min_local > xloc[i].first)
              //  min_local = xloc[i].first;
        }
        cos = min_local;
    }
    // Splitting constructor: вызывается при порождении новой задачи
    reduce_par(reduce_par& r, split) : cos(1.1), next(0), len(0), points(r.points), prev_p(r.prev_p), cur_p(r.cur_p) {}
    // Join: объединяет результаты двух задач (текущей и r)

    void join(const reduce_par& r) {
        if (cos > r.cos) {
            cos = r.cos;
            len = r.len;
            next = r.next;
        }
        else if (cos == r.cos) {
            if (len > r.len) {
                next = r.next;
                len = r.len;
            }
        }
    }
        //min_cos = std::min(min_cos, r.sum); }
    reduce_par(std::vector<std::pair<double, double>> x, std::pair<double, double> y, std::pair<double, double> z) :
        cos(1.1), next(0), len(0), points(x), prev_p(y), cur_p(z) {}
private:
    std::vector<std::pair<double, double>> points;
    std::pair<double, double > prev_p;
    std::pair<double, double > cur_p;
};

int func(std::vector<std::pair<double, double>> points)
{
    size_t size = points.size();
    size_t base_id = 0;
    std::vector<std::pair<double, double>> Convex_Hull(1);
    std::pair<double, double> cur_p;
    std::pair<double, double> prev_p;

    for (size_t i = 1; i < size; i++) {
        if (points[i].second < points[base_id].second) {
            base_id = i;
        }
        else if ((points[i].second == points[base_id].second) && (points[i].first < points[base_id].first)) {
            base_id = i;
        }
    }

    Convex_Hull[0] = points[base_id];
    cur_p = Convex_Hull[0];
    prev_p.first = Convex_Hull[0].first - 1;
    prev_p.second = Convex_Hull[0].second;
    int flag_h = 1;
    do {
        tick_count t0 = tick_count::now();
        reduce_par r(points, prev_p, cur_p);
        parallel_reduce(blocked_range<size_t>(0, size), r);
        tick_count t1 = tick_count::now();
        Convex_Hull.push_back(points[r.next]);
        flag_h++;
        prev_p.first = cur_p.first;
        prev_p.second = cur_p.second;
        cur_p = points[r.next];
        std::cout << "Reduce: " << r.cos << " " << r.len << "\n";
    } while (cur_p != Convex_Hull[0]);

    if (flag_h > 1) {
        flag_h--;
        Convex_Hull.pop_back();
    }

    for (int i = 0; i < Convex_Hull.size(); i++) {
        std::cout << Convex_Hull[i].first << " ";
        std::cout << Convex_Hull[i].second << "\n";

    }
    //std::cout << "Reduce: " << r.cos << " " << r.len << "\n";
    //std::cout << "Time: " << (t1 - t0).seconds() << " sec.\n";
    //delete[] x;
    return 0;
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
        }
        else if ((points[i].second == points[base_id].second) && (points[i].first < points[base_id].first)) {
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
            }
            else if (cur_cos == min_cos) {
                if (max_len < len2) {
                    next = i;
                    max_len = len2;
                }
            }
            //std::cout << flag_h << "\n";
            //std::cout << min_cos << " " << max_len << "\n";
            //std::cout << "\n";
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

    for (int i = 0; i < Convex_Hull.size(); i++) {
        std::cout << Convex_Hull[i].first << " ";
        std::cout << Convex_Hull[i].second << "\n";

    }

    return Convex_Hull;
}

/*std::vector<std::pair<double, double>> Jarvis_Seq(std::vector<std::pair<double, double>> points) {
    size_t size = points.size();
    size_t base_id = 0;
    std::vector<std::pair<double, double>> Convex_Hull(1);
    std::pair<double, double> cur_p;
    std::pair<double, double> prev_p;

    for (size_t i = 1; i < size; i++) {
        if (points[i].second < points[base_id].second) {
            base_id = i;
        }
        else if ((points[i].second == points[base_id].second) && (points[i].first < points[base_id].first)) {
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
    int kolvo = 0;
    task_scheduler_init init(2);

    parallel_for(
        blocked_range<int>(0, size),
        [&](const blocked_range<int>& t) {
        int begin = t.begin(), end = t.end();
        for (int p = begin; p != end; p++) {
            //do {
            if (kolvo == 0) {
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
                    }
                    else if (cur_cos == min_cos) {
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
                //std::cout << Convex_Hull.back().first << " " << Convex_Hull.back().second << "\n";
                //} while (cur_p != Convex_Hull[0]);
                if (cur_p == Convex_Hull[0]) {
                    p = size;
                    kolvo = Convex_Hull.size();
                    //Convex_Hull.push_back(Convex_Hull[0]);
                    break;
                }
            }
        }
    });

    init.terminate();
    //std::cout << kolvo;
    if (flag_h > 1) {
        flag_h--;
        Convex_Hull.pop_back();
    }

    return Convex_Hull;
}

/*
/*parallel_for(blocked_range<size_t>(0, size, 2),
    [&](const blocked_range<size_t>& r)

 void parallel_for(const Range& range, const Body& body[, partitioner]);

void ParallelDo(const std::vector<int>& root_set) { tbb::parallel_do(root_set.begin(), root_set.end(), Body()); }

void Proba_While_Tbb(std::vector<std::pair<double, double>> points) {
    int i = 0;
    int size = 1000;
    //tbb::task_group gruppe;
    task_scheduler_init init(1);
    parallel_do(blocked_range<size_t>(0, size),
        [&](const blocked_range<size_t>& r)
    {
        int begin = r.begin(), end = r.end();
        do {
            i++;
        } while (i != 1000);
    },
        task_group_context group
        //simple_partitioner()
        );
    std::cout << i << "\n";

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
        }
        else if ((points[i].second == points[base_id].second) && (points[i].first < points[base_id].first)) {
            base_id = i;
        }
    }

    Convex_Hull[0] = points[base_id];
    cur_p = Convex_Hull[0];
    prev_p.first = Convex_Hull[0].first - 1;
    prev_p.second = Convex_Hull[0].second;

    if (size == 1) {
        return Convex_Hull;
    }
    else if (size == 2) {
        if (points[0] == points[1]) {
            return Convex_Hull;
        }
        else if (points[0] != points[1]) {
            return points;
        }
    }

    double len1;
    double len2;
    double max_len = 0;
    double scalar;
    //double cur_cos;
    double min_cos;
    size_t next = 0;
    size_t flag_h = 1;
    task_scheduler_init init(1);
    std::vector<std::vector<double>> cur_cos(size, std::vector<double>(3, 0));

    do {
        parallel_for(blocked_range<size_t>(0, size, 2),
            [&](const blocked_range<size_t>& r)
        {
            int begin = r.begin(), end = r.end();

            for (int i = begin; i != end; i++) {
                len1 = sqrt(pow((prev_p.first - cur_p.first), 2) + pow((prev_p.second - cur_p.second), 2));
                len2 = sqrt(pow((points[i].first - cur_p.first), 2) + pow((points[i].second - cur_p.second), 2));
                scalar = ((prev_p.first - cur_p.first) * (points[i].first - cur_p.first) +
                    (prev_p.second - cur_p.second) * (points[i].second - cur_p.second));
                if (len2 == 0)
                    cur_cos[i][0] = 1.1;
                else
                    cur_cos[i][0] = scalar / len1 / len2;
                cur_cos[i][2] = i;
                cur_cos[i][1] = len2;
            }
        },
            simple_partitioner()
            );
        std::sort(cur_cos.begin(), cur_cos.end());
        //min_cos = cur_cos[0].first;
        int i = 0;
        while (cur_cos[0][0] == cur_cos[i + 1][0]) {
            if (cur_cos[0][1] < cur_cos[i + 1][1]) {
                cur_cos[0] = cur_cos[i + 1];
            }
            i++;
        }
        next = cur_cos[0][2];
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
}*/

std::vector<std::pair<double, double>> Jarvis_Omp(std::vector<std::pair<double, double>> points, int nu_th) {
    size_t size = points.size();
    size_t base_id = 0;
    std::vector<std::pair<double, double>> Convex_Hull(1);
    std::vector<std::vector<int>> Local_Convex_Hulls(nu_th);
    std::pair<double, double> base_p;
    std::pair<double, double> cur_p;
    std::pair<double, double> pr_p;
    int tid;
    int k;
    int ost;

    k = size / nu_th;

    for (size_t i = 1; i < size; i++) {
        if (points[i].second < points[base_id].second) {
            base_id = i;
        }
        else if ((points[i].second == points[base_id].second) && (points[i].first < points[base_id].first)) {
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
    }
    else if (size == 2) {
        if (points[0] == points[1]) {
            return Convex_Hull;
        }
        else if (points[0] != points[1]) {
            return points;
        }
    }

#pragma omp parallel private(tid, mn_cs, len1, len2, scalar, cur_cos, next, mx_ln, ost, pr_p, cur_p) num_threads(nu_th)
    {
        tid = omp_get_thread_num();
        next = 0;
        mx_ln = 0;
        cur_p = Convex_Hull[0];
        pr_p.first = Convex_Hull[0].first - 1;
        pr_p.second = Convex_Hull[0].second;

        if (tid == nu_th - 1) {
            ost = size % nu_th;
        }
        else {
            ost = 0;
        }

        do {
            mn_cs = 1.1;

            for (int i = tid * k; i < ((tid + 1) * k) + ost; i++) {
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
                next = base_id;
            }
            else if (cur_cos == mn_cs) {
                if (mx_ln < len2) {
                    next = base_id;
                }
            }

            if (next == base_id)
                break;
            Local_Convex_Hulls[tid].push_back(next);
            pr_p.first = cur_p.first;
            pr_p.second = cur_p.second;
            cur_p = points[next];
        } while (base_id != next);
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
            }
            else if (cur_cos == mn_cs) {
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
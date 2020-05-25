// Copyright 2020 Trenina Elizaveta

#include <tbb/tbb.h>
#include <algorithm>
#include <utility>
#include <random>
#include <vector>
#include <ctime>
#include "../../../modules/task_3/trenina_e_convex_hull_graham/convex_hull_graham.h"


std::vector<point> Graham_TBB(std::vector<point> Q, std::size_t threads_num) {
    if (threads_num == 0) throw - 1;

    std::vector<point> last_points;
    int step = Q.size() / threads_num;

    tbb::task_scheduler_init init(static_cast<int>(threads_num));

    tbb::spin_mutex mutex;
    tbb::task_group g;

    auto begin = Q.begin();
    auto end = Q.end();

    for (std::size_t i = 0; i < threads_num - 1; ++i) {
        g.run([&last_points, &mutex, i, begin, step]() {
            auto left = begin + step * i;
            auto right = begin + step * (i + 1);
            auto local_scan = Graham_Seq(left, right);
            for (std::size_t j = 0; j < local_scan.size(); ++j) {
                tbb::spin_mutex::scoped_lock lock;
                lock.acquire(mutex);
                last_points.push_back(local_scan[j]);
                lock.release();
            }
            });
    }
    g.run([&last_points, begin, end, step, threads_num, &mutex]() {
        auto local_scan = Graham_Seq(begin + step * (threads_num - 1), end);
        for (std::size_t j = 0; j < local_scan.size(); ++j) {
            tbb::spin_mutex::scoped_lock lock;
            lock.acquire(mutex);
            last_points.push_back(local_scan[j]);
            lock.release();
        }
        });
    g.wait();
    return Graham_Seq(last_points.begin(), last_points.end());
}


bool rotate(const point& A, const point& B, const point& C) {
    return (B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x) >= 0;
}

bool cmp(const point& B, const point& C) {
    return
        C.x * (B.y - C.y) - C.y * (B.x - C.x) < 0 ||
        (C.x * (B.y - C.y) - C.y * (B.x - C.x) == 0 &&
            B.x * B.x + B.y * B.y < C.x* C.x + C.y * C.y);
}


std::vector<point> Graham_Seq(std::vector<point>::iterator begin, std::vector<point>::iterator end) {
    if (end-begin < 3) throw "|Q|<3";
    std::vector<point> Q(end - begin);
    std::copy(begin, end, Q.begin());
    int index = 0;
    for (size_t i = 1; i < Q.size(); i++) {
        if ((Q[i].y < Q[index].y) || ((Q[i].y == Q[index].y) && (Q[i].x < Q[index].x)))
            index = i;
    }
    std::swap(Q[0], Q[index]);
    point p0 = Q[0];

    for (size_t i = 0; i < Q.size(); i++) {
        Q[i].x -= p0.x;
        Q[i].y -= p0.y;
    }
    std::sort(Q.begin()+1, Q.end(), &cmp);

    std::vector<point> hull;
    hull.push_back(Q[0]);
    hull.push_back(Q[1]);

    size_t i = 2, k = 0;
    do {
        point t = Q[i];

        while (!rotate(hull[k], hull[k + 1], t)) {
            hull.pop_back();
            --k;
        }
        hull.push_back(t);
        ++k; ++i;
    } while (i < Q.size());

    for (size_t k = 0; k < hull.size(); k++) {
        hull[k].x += p0.x;
        hull[k].y += p0.y;
    }

    return hull;
}


std::vector<point> GetRandSet(int n) {
    if (n < 3) throw;
    std::vector<point> result(n);
    std::mt19937 gen(time(0));
    std::uniform_real_distribution<> uid(-100, 100);

    for (int i = 0; i < n; i++) {
        result[i].x = uid(gen);
        result[i].y = uid(gen);
    }
    return result;
}



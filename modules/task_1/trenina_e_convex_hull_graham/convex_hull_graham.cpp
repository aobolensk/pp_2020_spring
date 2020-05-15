// Copyright 2020 Trenina Elizaveta

#include <algorithm>
#include <utility>
#include <random>
#include <vector>
#include <ctime>
#include "../../../modules/task_1/trenina_e_convex_hull_graham/convex_hull_graham.h"

bool rotate(const point& A, const point& B, const point& C) {  // left?
    return (B.x - A.x) * (C.y - B.y) - (B.y - A.y) * (C.x - B.x) >= 0;
}

bool cmp(const point& B, const point& C) {  // B<C?
    return
        C.x * (B.y - C.y) - C.y * (B.x - C.x) < 0 ||
        (C.x * (B.y - C.y) - C.y * (B.x - C.x) == 0 &&
            B.x * B.x + B.y * B.y < C.x* C.x + C.y * C.y);
}


std::vector<point> Graham(std::vector<point> Q) {
    if (Q.size() < 3) throw "|Q|<3";

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



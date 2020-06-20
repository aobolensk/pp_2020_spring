// Copyright 2020 Trenina Elizaveta
#ifndef MODULES_TASK_1_TRENINA_E_CONVEX_HULL_GRAHAM_CONVEX_HULL_GRAHAM_H_
#define MODULES_TASK_1_TRENINA_E_CONVEX_HULL_GRAHAM_CONVEX_HULL_GRAHAM_H_

#include <vector>

struct point {
    double x, y;
    point() {
        x = 0.0;
        y = 0.0;
    }

    point(double _x, double _y) : x(_x), y(_y) {}

    friend bool operator==(const point& a, const point& b) {
        return (a.x == b.x) && (a.y == b.y);
    }
};

bool cmp(const point& B, const point& C);  // B<C?

bool rotate(const point& A, const point& B, const point& C);

std::vector<point> GetRandSet(int n);

std::vector<point> Graham(std::vector<point> Q);

#endif  // MODULES_TASK_1_TRENINA_E_CONVEX_HULL_GRAHAM_CONVEX_HULL_GRAHAM_H_

// Copyright 2020 Kondrina Tatyana

#ifndef MODULES_TASK_1_KONDRINA_T_JARVIS_JARVIS_H_
#define MODULES_TASK_1_KONDRINA_T_JARVIS_JARVIS_H_

#include <vector>

struct Point {
  double x, y;

  friend bool operator!=(const Point& a, const Point& b) {
    return !(a == b);
  }
  friend bool operator==(const Point& a, const Point& b) {
    return (a.x == b.x) && (a.y == b.y);
  }

  friend bool operator<(const Point& a, const Point& b) {
    return a.x < b.x;
  }
};

std::vector<Point> randomSet(int point_count);
std::vector<Point> buildHull(std::vector<Point> m_set);

#endif  // MODULES_TASK_1_KONDRINA_T_JARVIS_JARVIS_H_

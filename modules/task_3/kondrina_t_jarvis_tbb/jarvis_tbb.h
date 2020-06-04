// Copyright 2020 Kondrina Tatyana

#ifndef MODULES_TASK_3_KONDRINA_T_JARVIS_TBB_JARVIS_TBB_H_
#define MODULES_TASK_3_KONDRINA_T_JARVIS_TBB_JARVIS_TBB_H_

#include <vector>


struct Point {
  double x, y;

  friend bool operator!=(const Point& a, const Point& b) { return !(a == b); }
  friend bool operator==(const Point& a, const Point& b) {
    return (a.x == b.x) && (a.y == b.y);
  }

  friend bool operator<(const Point& a, const Point& b) {
    return (a.y < b.y) || (a.y == b.y && a.x < b.x);
  }
};

std::vector<Point> randomSet(int point_count);
std::vector<Point> buildHull_seq(std::vector<Point> m_set);
std::vector<Point> buildHull_tbb(std::vector<Point> m_set);

#endif  // MODULES_TASK_3_KONDRINA_T_JARVIS_TBB_JARVIS_TBB_H_

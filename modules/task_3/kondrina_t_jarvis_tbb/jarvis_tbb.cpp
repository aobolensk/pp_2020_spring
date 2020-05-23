// Copyright 2020 Kondrina Tatyana

#include "../../../modules/task_3/kondrina_t_jarvis_tbb/jarvis_tbb.h"

#include <tbb/tbb.h>

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>


double rotate(const Point& p, const Point& q, const Point& i) {
  return (q.x - p.x) * (i.y - q.y) - (q.y - p.y) * (i.x - q.x);
}

std::vector<Point> buildHull_seq(std::vector<Point> m_set) {
  if (m_set.size() < 3) throw - 1;
  Point left_point =
      *std::min_element(m_set.begin(), m_set.end(), [](Point a, Point b) {
        return (a.y < b.y) || (a.y == b.y && a.x < b.x);
      });

  std::vector<Point> hull;
  Point end_point;

  do {
    hull.push_back(left_point);
    end_point = m_set[0];
    for (auto i : m_set) {
      if (rotate(hull.back(), end_point, i) < 0 || end_point == left_point) {
        end_point = i;
      }
    }
    left_point = end_point;
  } while (end_point != hull[0]);
  return hull;
}

class reduce_ {
  std::vector<Point> m_set_;
  std::vector<Point> hull_;
  Point left_point_;
  Point res;

 public:
  reduce_(std::vector<Point> m_set, std::vector<Point> hull)
      : m_set_(m_set), hull_(hull), left_point_(hull.back()), res(m_set[0]) {}
  reduce_(reduce_& r, tbb::split)
      : m_set_(r.m_set_),
        hull_(r.hull_),
        left_point_(r.left_point_),
        res(r.res) {}

  void operator()(const tbb::blocked_range<size_t>& r) {
    for (auto i = r.begin(); i != r.end(); i++) {
      if (rotate(hull_.back(), res, m_set_[i]) < 0 || res == left_point_) {
        res = m_set_[i];
      }
    }
  }

  void join(const reduce_& r) {
    if (rotate(hull_.back(), res, r.res) < 0 || res == left_point_) {
      res = r.res;
    }
  }

  Point getPoint() { return res; }
};

std::vector<Point> buildHull_tbb(std::vector<Point> m_set) {
  int size = m_set.size();
  if (size < 3) throw - 1;
  Point left_point;

#pragma omp parallel shared(left_point)
  left_point =
      *std::min_element(m_set.begin(), m_set.end(), [](Point a, Point b) {
        return (a.y < b.y) || (a.y == b.y && a.x < b.x);
      });

  std::vector<Point> hull;
  Point end_point;

  do {
    hull.push_back(left_point);
    end_point = m_set[0];
    reduce_ r(m_set, hull);
    tbb::parallel_reduce(tbb::blocked_range<size_t>(0, size), r);
    end_point = r.getPoint();
    left_point = end_point;
  } while (end_point != hull[0]);
  return hull;
}

std::vector<Point> randomSet(int point_count) {
  if (point_count < 3) throw - 1;
  std::srand(std::time(nullptr));
  std::vector<Point> result(point_count);

  std::generate(result.begin(), result.end(), []() {
    return Point{static_cast<double>(std::rand() % 100 - 50),
                 static_cast<double>(std::rand() % 100 - 50)};
  });
  return result;
}

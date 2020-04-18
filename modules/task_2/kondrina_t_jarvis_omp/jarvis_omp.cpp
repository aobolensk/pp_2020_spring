// Copyright 2020 Kondrina Tatyana

#include "../../../modules/task_2/kondrina_t_jarvis_omp/jarvis_omp.h"

#include <omp.h>

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>


#define NUM_THREADS 4

int rotate(const Point& p, const Point& q, const Point& i) {
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

std::vector<Point> buildHull_omp(std::vector<Point> m_set) {
  int size = m_set.size();
  if (size < 3) throw - 1;
  Point left_point;
#pragma omp parallel shared(left_point) num_threads(NUM_THREADS)
  left_point =
      *std::min_element(m_set.begin(), m_set.end(), [](Point a, Point b) {
        return (a.y < b.y) || (a.y == b.y && a.x < b.x);
      });
  std::vector<Point> hull;
  Point end_point;

  do {
    hull.push_back(left_point);
    end_point = m_set[0];

#pragma omp parallel shared(end_point) num_threads(NUM_THREADS)
    {
      Point local = end_point;
#pragma omp for nowait
      for (int i = 0; i < size; i++) {
        if (rotate(hull.back(), local, m_set[i]) < 0 || local == left_point) {
          local = m_set[i];
        }
      }
#pragma omp critical
      {
        if (rotate(hull.back(), end_point, local) < 0 ||
            end_point == left_point) {
          end_point = local;
        }
      }
    }
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

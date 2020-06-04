// Copyright 2020 Makarikhin Semen

#include <tbb/tbb.h>
#include <random>
#include <algorithm>
#include <ctime>
#include <vector>
#include "../../../modules/task_3/makarikhin_semen_dijkstra_algorithm/dijkstra_algorithm.h"

Graph::Graph(int vertex_n) :vertex_num(vertex_n) {
  weight_list.resize(vertex_n);
  std::vector<int> v(vertex_n, 0);
  for (auto& list : weight_list) {
    list = v;
  }
}
tbb::mutex ChangeMinMutex;

Graph get_Random_Graph(const int& vertex_n, const int& edge_n) {
  if (edge_n > (vertex_n * (vertex_n - 1) / 2)) {
    throw std::out_of_range("out of range edges");
  }

  if (edge_n < 0 || vertex_n < 0) {
    throw std::out_of_range("out of range edges or vertex_n");
  }

  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  std::uniform_real_distribution<> dis(0.0, 1.0);

  Graph g(vertex_n);

  int edge = edge_n;
  int remaining_edge = vertex_n * (vertex_n - 1) / 2;

  for (int i = 0; i < vertex_n; ++i) {
    for (int j = i + 1; j < vertex_n; ++j) {
      if (dis(gen) < static_cast<double>(edge) / remaining_edge) {
        g.weight_list[i][j] = g.weight_list[j][i] = gen() % 100;
        --edge;
      }
      --remaining_edge;
    }
  }
  return g;
}

std::vector<int> Dijkstra_Tbb(const Graph& g, int selected_vertex) {
  if (selected_vertex < 0 || selected_vertex > g.vertex_num - 1) {
    throw std::out_of_range("out of range selected vertex");
  }

  std::vector<int> distance(g.vertex_num, INT8_MAX);
  distance[selected_vertex] = 0;
  std::vector <bool> visit(g.vertex_num, false);
  int count;

  struct min { int val; int index; };
  min current = { INT8_MAX , 0 };
  for (count = 0; count < g.vertex_num - 1; count++) {
    current.val = INT8_MAX;
    current = tbb::parallel_reduce(
      tbb::blocked_range<int>(0, g.vertex_num),
      current,
      [&](const tbb::blocked_range<int>& range, min cur) ->min {
      for (int i = range.begin(); i != range.end(); ++i) {
        if (!visit[i] && distance[i] <= cur.val) {
          cur.val = distance[i];
          cur.index = i;
        }
      }
      return cur;
    }, [](min a, min b) {
      return a.val < b.val ? a : b;
    });
    visit[current.index] = true;

    tbb::parallel_for(
      tbb::blocked_range<int>(0, g.vertex_num),
      [&](const tbb::blocked_range<int>& range) {
      for (int i = range.begin(); i != range.end(); ++i) {
        if (!visit[i] && g.weight_list[current.index][i] && distance[current.index] != INT8_MAX &&
          distance[current.index] + g.weight_list[current.index][i] < distance[i])
          distance[i] = distance[current.index] + g.weight_list[current.index][i];
      }
    });
  }
  return distance;
}

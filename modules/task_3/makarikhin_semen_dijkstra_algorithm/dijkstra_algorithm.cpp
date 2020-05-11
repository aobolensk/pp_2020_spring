// Copyright 2020 Makarikhin Semen
#include <tbb/task_scheduler_init.h>
#include <tbb/task_group.h>
#include <tbb/task.h>
#include <tbb/mutex.h>
#include <random>
#include <ctime>
#include <vector>
#include <stdexcept>
#include <iostream>
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

std::vector<int> Dijkstra(const Graph& g, int selected_vertex) {
  if (selected_vertex < 0 || selected_vertex > g.vertex_num - 1) {
    throw std::out_of_range("out of range selected vertex");
  }

  tbb::task_scheduler_init init;
  tbb::task_list tl;

  std::vector<int> distance(g.vertex_num, INT8_MAX);
  distance[selected_vertex] = 0;
  std::vector <bool> visit(g.vertex_num, false);
  int v_num, cur_vert;
  for (v_num = 0; v_num < g.vertex_num - 1; v_num++) {
    tl.push_back(*new (tbb::task::allocate_root()) RooTaskDujkstra(&distance, g, &visit));
  }

  tbb::task::spawn_root_and_wait(tl);
  return distance;
}

tbb::task* RooTaskDujkstra::execute() {
  tbb::mutex::scoped_lock lock;
  int local_min = INT8_MAX;
  int local_ind = 0;
  int vertex_num = 0;

  for (int i = 0; i < g.vertex_num; ++i) {
    if (!(*visit)[i] && (*distance)[i] <= local_min) {
      local_min = (*distance)[i];
      local_ind = i;
    }
  }
  vertex_num = local_ind;

  lock.acquire(ChangeMinMutex);
  (*visit)[vertex_num] = true;
  lock.release();

  for (int i = 0; i < g.vertex_num; i++) {
    if (!(*visit)[i] && g.weight_list[vertex_num][i] && (*distance)[vertex_num] != INT8_MAX &&
      (*distance)[vertex_num] + g.weight_list[vertex_num][i] < (*distance)[i]) {
      lock.acquire(ChangeMinMutex);
      (*distance)[i] = (*distance)[vertex_num] + g.weight_list[vertex_num][i];
      lock.release();
    }
  }
  return NULL;
}

// Copyright 2020 Makarikhin Semen
#include <random>
#include <ctime>
#include <vector>
#include <iostream>
#include <deque>
#include "../../../modules/task_1/makarikhin_semen_dijkstra_algorithm/dijkstra_algorithm.h"

Graph::Graph(int vertex_n) :vertex_num(vertex_n) {
  weight_list.resize(vertex_n);
  std::vector<int> v(vertex_n, 0);
  for (auto& list : weight_list) {
    list = v;
  }
}

Graph get_Random_Graph(const int& vertex_n, const int& edge_n) {
  if (edge_n > (vertex_n * (vertex_n - 1) / 2)) {
    throw std::out_of_range("out of range edges");
  }

  if (edge_n < 0 || vertex_n < 0) {
    throw std::out_of_range("out of range edges or vertex_n");
  }

  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  Graph g(vertex_n);
  std::deque <std::vector<int>> list_uncertain((vertex_n * (vertex_n - 1) / 2));

  int k = 0;
  for (int i = 0; i < vertex_n; i++) {
    for (int j = i + 1; j < vertex_n; j++) {
      list_uncertain[k].resize(2);
      list_uncertain[k][0] = i;
      list_uncertain[k++][1] = j;
    }
  }

  int rand_vertex;
  for (int i = 0; i < edge_n; i++) {
    rand_vertex = gen() % list_uncertain.size();
    g.weight_list[list_uncertain[rand_vertex][0]][list_uncertain[rand_vertex][1]] =
      g.weight_list[list_uncertain[rand_vertex][1]][list_uncertain[rand_vertex][0]] = gen() % 100;
    list_uncertain.erase(list_uncertain.begin() + rand_vertex);
  }
  return g;
}

std::vector<int> Dijkstra(const Graph& g, int selected_vertex) {
  if (selected_vertex < 0 || selected_vertex > g.vertex_num-1) {
    throw std::out_of_range("out of range selected vertex");
  }

  std::vector<int> distance(g.vertex_num, INT8_MAX);
  distance[selected_vertex] = 0;
  std::vector <bool> visit(g.vertex_num, false);
  int count, index = 0, cur_vert;

  for (count = 0; count < g.vertex_num - 1; count++) {
    int min = INT8_MAX;
    for (int i = 0; i < g.vertex_num; i++)
      if (!visit[i] && distance[i] <= min) {
        min = distance[i];
        index = i;
      }
    cur_vert = index;
    visit[cur_vert] = true;
    for (int i = 0; i < g.vertex_num; i++)
      if (!visit[i] && g.weight_list[cur_vert][i] && distance[cur_vert] != INT8_MAX &&
        distance[cur_vert] + g.weight_list[cur_vert][i] < distance[i])
        distance[i] = distance[cur_vert] + g.weight_list[cur_vert][i];
  }

  return distance;
}


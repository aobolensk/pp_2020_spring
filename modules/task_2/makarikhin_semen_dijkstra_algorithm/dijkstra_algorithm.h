// Copyright 2020 Makarikhin Semen
#ifndef MODULES_TASK_2_MAKARIKHIN_SEMEN_DIJKSTRA_ALGORITHM_DIJKSTRA_ALGORITHM_H_
#define MODULES_TASK_2_MAKARIKHIN_SEMEN_DIJKSTRA_ALGORITHM_DIJKSTRA_ALGORITHM_H_
#include <vector>

struct Graph {
    std::vector <std::vector<int>> weight_list;
    int vertex_num;

    explicit Graph(int vertex_n);
};

Graph get_Random_Graph(const int& vertex_n, const int& edge_n);
std::vector<int> Dijkstra(const Graph& g, int selected_vertex);

#endif  // MODULES_TASK_2_MAKARIKHIN_SEMEN_DIJKSTRA_ALGORITHM_DIJKSTRA_ALGORITHM_H_

// Copyright 2020 Makarikhin Semen
#include <omp.h>
#include <random>
#include <ctime>
#include <vector>
#include <stdexcept>
#include "../../../modules/task_2/makarikhin_semen_dijkstra_algorithm/dijkstra_algorithm.h"

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

    std::vector<int> distance(g.vertex_num, INT8_MAX);
    distance[selected_vertex] = 0;
    std::vector <bool> visit(g.vertex_num, false);
    int count, cur_vert;

    for (count = 0; count < g.vertex_num - 1; count++) {
        int min = INT8_MAX;
#pragma omp parallel
        {
            int local_min = INT8_MAX;
            int local_ind = 0;
#pragma omp for
            for (int i = 0; i < g.vertex_num; ++i)
                if (!visit[i] && distance[i] <= local_min) {
                    local_min = distance[i];
                    local_ind = i;
                }

#pragma omp critical
            {
                if (local_min < min) {
                    min = local_min;
                    cur_vert = local_ind;
                }
            }

#pragma omp barrier

#pragma omp single
            {
                visit[cur_vert] = true;
            }

#pragma omp for
            for (int i = 0; i < g.vertex_num; i++)
                if (!visit[i] && g.weight_list[cur_vert][i] && distance[cur_vert] != INT8_MAX &&
                    distance[cur_vert] + g.weight_list[cur_vert][i] < distance[i])
                    distance[i] = distance[cur_vert] + g.weight_list[cur_vert][i];
        }
    }
    return distance;
}

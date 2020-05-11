// Copyright 2020 Makarikhin Semen
#ifndef MODULES_TASK_3_MAKARIKHIN_SEMEN_DIJKSTRA_ALGORITHM_DIJKSTRA_ALGORITHM_H_
#define MODULES_TASK_3_MAKARIKHIN_SEMEN_DIJKSTRA_ALGORITHM_DIJKSTRA_ALGORITHM_H_
#include <vector>
#include "tbb/task.h"

struct Graph {
  std::vector <std::vector<int>> weight_list;
  int vertex_num;

  explicit Graph(int vertex_n);
};
class RooTaskDujkstra : public tbb::task {
 public:
  RooTaskDujkstra(std::vector<int>* _distance, const Graph& _g,
    std::vector <bool>* _visit) : distance(_distance),
    visit(_visit), g(_g) {
  }
  tbb::task* execute();

 private:
  std::vector<int>* distance;
  std::vector <bool>* visit;
  const Graph& g;
};
Graph get_Random_Graph(const int& vertex_n, const int& edge_n);
std::vector<int> Dijkstra(const Graph& g, int selected_vertex);

#endif  // MODULES_TASK_3_MAKARIKHIN_SEMEN_DIJKSTRA_ALGORITHM_DIJKSTRA_ALGORITHM_H_

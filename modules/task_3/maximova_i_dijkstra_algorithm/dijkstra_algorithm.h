// Copyright 2020 Maximova Irina
#ifndef MODULES_TASK_3_MAXIMOVA_I_DIJKSTRA_ALGORITHM_DIJKSTRA_ALGORITHM_H_
#define MODULES_TASK_3_MAXIMOVA_I_DIJKSTRA_ALGORITHM_DIJKSTRA_ALGORITHM_H_

#include <tbb/tbb.h>
#include <vector>

class Graph {
 private:
  std::vector<int> linkedList;
  int numVertex;
  int numEdges;

 public:
  explicit Graph(int _numVertex, int _numEdges);
  void createRandGraph();
  void putEdge(int a, int b, int weightEdge);
  int getNumEdges() const { return numEdges; }
  int getNumVertex() const { return numVertex; }
  const int& operator[](const int index) const { return linkedList[index]; }
};

std::vector<int> TBB_Dijkstra_Alg(const Graph& graph, int sourceVertex);

#endif  // MODULES_TASK_3_MAXIMOVA_I_DIJKSTRA_ALGORITHM_DIJKSTRA_ALGORITHM_H_

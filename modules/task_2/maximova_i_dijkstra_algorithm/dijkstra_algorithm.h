// Copyright 2020 Maximova Irina
#ifndef MODULES_TASK_2_MAXIMOVA_I_DIJKSTRA_ALGORITHM_DIJKSTRA_ALGORITHM_H_
#define MODULES_TASK_2_MAXIMOVA_I_DIJKSTRA_ALGORITHM_DIJKSTRA_ALGORITHM_H_

#include <vector>

class Graph {
 private:
  std::vector<std::vector<int>> linkedList;
  int numVertex;
  int numEdges;

 public:
  explicit Graph(int _numVertex, int _numEdges);
  void createRandGraph();
  int getNumEdges() { return numEdges; }
  void putEdge(int a, int b, int weightEdge);
  std::vector<std::vector<int>> getLinkedList() const;
};

std::vector<int> DijkstraAlg(const Graph& graph, int sourceVertex);

#endif  // MODULES_TASK_2_MAXIMOVA_I_DIJKSTRA_ALGORITHM_DIJKSTRA_ALGORITHM_H_

// Copyright 2020 Maximova Irina
#ifndef MODULES_TASK_1_MAXIMOVA_I_DIJKSTA_ALGORITHM_DIJKSTA_ALGORITHM_H_
#define MODULES_TASK_1_MAXIMOVA_I_DIJKSTA_ALGORITHM_DIJKSTA_ALGORITHM_H_

#include <vector>

class graph {
 private:
  std::vector<std::vector<std::pair<int, int>>> edges;
  int numVertex;
  int numEdges;

  void getTree();
  void getRandEdges();

 public:
  graph(int _numVertex = 0, int _numEdges = 0);
  void getRandLinkGraph();
};

#endif  // MODULES_TASK_1_MAXIMOVA_I_DIJKSTA_ALGORITHM_DIJKSTA_ALGORITHM_H_

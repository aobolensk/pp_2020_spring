// Copyright 2020 Maximova Irina
#include "../../../modules/task_1/maximova_i_dijkstra_algorithm/dijkstra_algorithm.h"
#include <omp.h>
#include <ctime>
#include <random>
#include <stdexcept>
#include <utility>

graph::graph(int _numVertex, int _numEdges) {
  if (_numVertex <= 0)
    throw std::runtime_error("The number of vertex must be > 0");
  numVertex = _numVertex;

  if (_numEdges < numVertex - 1)
    throw std::runtime_error("The graph is not connected");
  if (_numEdges > (numVertex * (numVertex - 1)) / 2)
    throw std::runtime_error("Too many edges in the graph");
  numEdges = _numEdges;

  edges.resize(numVertex);
}

void graph::getTree() {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));
  int weightEdge, nextVertex;

  for (int i = 0; i < numVertex - 1; ++i) {
    weightEdge = gen() % 100;
    nextVertex = i + 1;
    edges[i].push_back(std::make_pair(nextVertex, weightEdge));
    edges[nextVertex].push_back(std::make_pair(i, weightEdge));
  }
}

void graph::getRandEdges() {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));

  int weightEdge;
  int numEdgesNow = numVertex - 1;
  double numEdgestNeedAdd = numEdges - numEdgesNow;
  double maxEdges = (numVertex * (numVertex - 1)) / 2;
  double genMax = static_cast<double>(gen.max());

  double probability = numEdgestNeedAdd / maxEdges;
  double randProbability;

  for (int i = 0; i < numVertex; ++i)
    for (int j = i + 2; j < numVertex; ++j) {
      randProbability = static_cast<double>(gen()) / genMax;
      if (randProbability <= probability && numEdgesNow < numEdges) {
        weightEdge = gen() % 100;
        edges[i].push_back(std::make_pair(j, weightEdge));
        edges[j].push_back(std::make_pair(i, weightEdge));
        ++numEdgesNow;
      }
    }

  numEdges = numEdgesNow;
}

void graph::getRandLinkGraph() {
  this->getTree();
  if (numEdges > numVertex - 1) this->getRandEdges();
}

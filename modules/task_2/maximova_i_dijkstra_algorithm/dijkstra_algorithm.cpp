// Copyright 2020 Maximova Irina
#include "../../../modules/task_2/maximova_i_dijkstra_algorithm/dijkstra_algorithm.h"
#include <omp.h>
#include <ctime>
#include <iomanip>
#include <random>
#include <stdexcept>
#include <utility>
#include <vector>

Graph::Graph(int _numVertex, int _numEdges) {
  if (_numVertex <= 0)
    throw std::runtime_error("The number of vertex must be > 0");
  numVertex = _numVertex;

  if (_numEdges > (numVertex * (numVertex - 1)) / 2)
    throw std::runtime_error("Too many edges in the graph");
  numEdges = _numEdges;

  std::vector<int> vecEx(numVertex, INT8_MAX);
  linkedList.resize(numVertex);
  for (int i = 0; i < numVertex; ++i) linkedList[i] = vecEx;
}

void Graph::putEdge(int a, int b, int weightEdge) {
  linkedList[a][b] = linkedList[b][a] = weightEdge;
}

void Graph::createRandGraph() {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));

  double maxEdges = (numVertex * (numVertex - 1)) / 2;
  double probability = static_cast<double>(numEdges) / maxEdges;
  double randProbability;
  double genMax = static_cast<double>(gen.max());
  double numEdgesNow = 0;
  int weightEdge;

  for (int i = 0; i < numVertex; ++i)
    for (int j = i + 1; j < numVertex; ++j) {
      randProbability = static_cast<double>(gen()) / genMax;
      if (randProbability <= probability && numEdgesNow < numEdges) {
        weightEdge = gen() % 100 + 1;
        this->putEdge(i, j, weightEdge);
        ++numEdgesNow;
      }
    }

  numEdges = numEdgesNow;
}

std::vector<std::vector<int>> Graph::getLinkedList() const {
  return linkedList;
}

int minDistVertex(const std::vector<int>& dist, const std::vector<int>& mark) {
  int resMinDist = INT8_MAX;
  int resV = -1;
  int all_dist = dist.size();

#pragma omp parallel
  {
    int i;
    int minDist = INT8_MAX;
    int minDistV = -1;

#pragma omp for
    for (i = 0; i < all_dist; ++i)
      if (mark[i] == false && dist[i] < minDist) {
        minDist = dist[i];
        minDistV = i;
      }

#pragma omp critical
    if (minDist < resMinDist) {
      resMinDist = minDist;
      resV = minDistV;
    }
  }

  return resV;
}

std::vector<int> DijkstraAlg(const Graph& graph, int sourceVertex) {
  std::vector<std::vector<int>> linkedList = graph.getLinkedList();
  int numVertex = linkedList.size();

  std::vector<int> dist(numVertex, INT8_MAX);
  std::vector<int> mark(numVertex, false);
  int vertex;
  dist[sourceVertex] = 0;

  for (int i = 0; i < numVertex - 1; ++i) {
    vertex = minDistVertex(dist, mark);
    if (vertex == -1) break;
    mark[vertex] = true;
#pragma omp parallel for
    for (int j = 0; j < numVertex; ++j)
      if (!mark[j] && linkedList[vertex][j] != INT8_MAX &&
          (dist[j] > dist[vertex] + linkedList[vertex][j]))
        dist[j] = dist[vertex] + linkedList[vertex][j];
  }

  return dist;
}

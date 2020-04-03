// Copyright 2020 Maximova Irina
#include "../../../modules/task_3/maximova_i_dijkstra_algorithm/dijkstra_algorithm.h"
#include <tbb/tbb.h>
#include <ctime>
#include <iomanip>
#include <random>
#include <stdexcept>
#include <utility>
#include <vector>
#include <queue>

Graph::Graph(int _numVertex, int _numEdges) {
  if (_numVertex <= 0)
    throw std::runtime_error("The number of vertex must be > 0");
  numVertex = _numVertex;

  if (_numEdges > (numVertex * (numVertex - 1)) / 2)
    throw std::runtime_error("Too many edges in the graph");
  numEdges = _numEdges;

  std::vector<int> v(numVertex * numVertex, INT8_MAX);
  linkedList = v;
}

void Graph::putEdge(int a, int b, int weightEdge) {
  linkedList[a * numVertex + b] = linkedList[b * numVertex + a] = weightEdge;
}

void Graph::createRandGraph() {
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)));

  double maxEdges = (numVertex * (numVertex - 1)) / 2;
  double probability = static_cast<double>(numEdges) / maxEdges;
  double randProbability;
  double genMax = static_cast<double>(UINT_MAX);
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

std::vector<int> TBB_Dijkstra_Alg(const Graph& graph, int sourceVertex) {
  int count_vertex = graph.getNumVertex();
  int cur_vertex;
  int cur_dist;
  tbb::mutex mutex;
  std::vector<int> dist(count_vertex, INT8_MAX);
  std::priority_queue<std::pair<int, int>> queue;

  dist[sourceVertex] = 0;
  queue.push(std::make_pair(0, sourceVertex));
  while (!queue.empty()) {
    cur_vertex = queue.top().second;
    cur_dist = (-1) * queue.top().first;
    queue.pop();
    if (cur_dist > dist[cur_vertex]) continue;

    tbb::parallel_for(
        tbb::blocked_range<int>(0, count_vertex),
        [&](const tbb::blocked_range<int>& r) {
          for (int v = r.begin(); v != r.end(); ++v) {
            int dist_curV_V = graph[cur_vertex * count_vertex + v];
            if (dist[cur_vertex] + dist_curV_V < dist[v]) {
              dist[v] = dist[cur_vertex] + dist_curV_V;
              std::pair<int, int> pair = std::make_pair((-1) * dist[v], v);
              mutex.lock();
              queue.push(pair);
              mutex.unlock();
            }
          }
        });
  }

  return dist;
}

// Copyright 2020 Maximova Irina
#include "../../../modules/task_4/maximova_i_dijkstra_algorithm/dijkstra_algorithm.h"
#include <ctime>
#include <iomanip>
#include <mutex>
#include <queue>
#include <random>
#include <limits.h>
#include <stdexcept>
#include <thread>
#include <utility>
#include <vector>

static const int count_threads = 2;

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
  int numEdgesNow = 0;
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

std::vector<int> STD_Dijkstra_Alg(const Graph& graph, int sourceVertex) {
  int count_vertex = graph.getNumVertex();
  int count_th = count_threads;
  int cur_vertex;
  int cur_dist;
  std::vector<int> dist(count_vertex, INT8_MAX);
  std::priority_queue<std::pair<int, int>> queue;

  std::mutex mtx;
  std::thread th[count_threads];
  int dose = count_vertex / count_threads;
  int rest[count_threads] = {0};
  rest[count_th - 1] += count_vertex % count_threads;

  dist[sourceVertex] = 0;
  queue.push(std::make_pair(0, sourceVertex));
  while (!queue.empty()) {
    cur_vertex = queue.top().second;
    cur_dist = (-1) * queue.top().first;
    queue.pop();
    if (cur_dist > dist[cur_vertex]) continue;

    for (int i = 0; i < count_threads; ++i) {
      th[i] = std::thread(
          [&](int numth, int r) {
            for (int v = numth * dose; v < (numth + 1) * dose + r; ++v)
              if (dist[v] > cur_dist + graph[cur_vertex * count_vertex + v]) {
                dist[v] = cur_dist + graph[cur_vertex * count_vertex + v];
                std::lock_guard<std::mutex> locker(mtx);
                queue.push(std::make_pair((-1) * dist[v], v));
              }
          },
          i, rest[i]);
    }
    for (int i = 0; i < count_threads; ++i) th[i].join();
  }

  return dist;
}

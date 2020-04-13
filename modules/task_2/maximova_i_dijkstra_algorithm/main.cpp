// Copyright 2020 Maximova Irina
#include <gtest/gtest.h>
#include <vector>
#include "./dijkstra_algorithm.h"

TEST(Dijkstra_Algorithm_OpenMP, Test_Constructor_Graph_Error_Zero_Vertex) {
  int numVertex = 0;
  int numEdges = 45;

  ASSERT_ANY_THROW(Graph graph(numVertex, numEdges));
}

TEST(Dijkstra_Algorithm_OpenMP, Test_Constructor_Graph_Error_Negative_Vertex) {
  int numVertex = -3;
  int numEdges = 45;

  ASSERT_ANY_THROW(Graph graph(numVertex, numEdges));
}

TEST(Dijkstra_Algorithm_OpenMP, Test_Constructor_Graph_Error_Too_Many_Edges) {
  int numVertex = 10;
  int numEdges = 50;

  ASSERT_ANY_THROW(Graph graph(numVertex, numEdges));
}

TEST(Dijkstra_Algorithm_OpenMP, Test_Can_Create_Random_Graph) {
  int numVertex = 5;
  int numEdges = 9;

  Graph graph(numVertex, numEdges);

  ASSERT_NO_THROW(graph.createRandGraph());
}

TEST(Dijkstra_Algorithm_OpenMP, Test_Can_Create_Random_Graph_Min_Edges) {
  int numVertex = 5;
  int numEdges = 4;

  Graph graph(numVertex, numEdges);

  ASSERT_NO_THROW(graph.createRandGraph());
}

TEST(Dijkstra_Algorithm_OpenMP, Test_Can_Create_Random_Graph_Max_Edges) {
  int numVertex = 5;
  int numEdges = 10;
  Graph graph(numVertex, numEdges);

  ASSERT_NO_THROW(graph.createRandGraph());
}

TEST(Dijkstra_Algorithm_OpenMP, Test_No_Throw_Execute_Dijkstra_Alg) {
  int numVertex = 5;
  int numEdges = 9;
  int sourceVertex = 0;

  Graph graph(numVertex, numEdges);
  graph.createRandGraph();

  ASSERT_NO_THROW(DijkstraAlg(graph, sourceVertex));
}

TEST(Dijkstra_Algorithm_OpenMP, Test_Right_Execute_Dijkstra_Alg_Linked_Graph) {
  int numVertex = 5;
  int numEdges = 5;
  int sourceVertex = 1;

  Graph graph(numVertex, numEdges);
  graph.putEdge(0, 1, 3);
  graph.putEdge(4, 1, 2);
  graph.putEdge(4, 2, 1);
  graph.putEdge(4, 3, 1);
  graph.putEdge(3, 2, 4);
  std::vector<int> algRes = DijkstraAlg(graph, sourceVertex);
  std::vector<int> currentRes = {3, 0, 3, 3, 2};

  ASSERT_EQ(algRes, currentRes);
}

TEST(Dijkstra_Algorithm_OpenMP, Test_Execute_Dijkstra_Alg_Unlinked_Graph) {
  int numVertex = 5;
  int numEdges = 5;
  int sourceVertex = 1;

  Graph graph(numVertex, numEdges);
  graph.putEdge(4, 1, 2);
  graph.putEdge(4, 2, 1);
  graph.putEdge(4, 3, 1);
  graph.putEdge(3, 2, 4);
  std::vector<int> algRes = DijkstraAlg(graph, sourceVertex);
  std::vector<int> currentRes = {INT8_MAX, 0, 3, 3, 2};

  ASSERT_EQ(algRes, currentRes);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

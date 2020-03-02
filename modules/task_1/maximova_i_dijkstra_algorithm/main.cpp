// Copyright 2020 Maximova Irina
#include <gtest/gtest.h>
#include <vector>
#include "./dijkstra_algorithm.h"

TEST(Dijkstra_Algorithm, Test_Create_Graph_Error_Zero_Vertex) {
  int numVertex = 0;
  int numEdges = 45;

  ASSERT_ANY_THROW(graph Graph(numVertex, numEdges));
}

TEST(Dijkstra_Algorithm, Test_Create_Graph_Error_Negative_Vertex) {
  int numVertex = -3;
  int numEdges = 45;

  ASSERT_ANY_THROW(graph Graph(numVertex, numEdges));
}

TEST(Dijkstra_Algorithm, Test_Create_Graph_Error_Graph_Is_Not_Connected) {
  int numVertex = 10;
  int numEdges = 8;

  ASSERT_ANY_THROW(graph Graph(numVertex, numEdges));
}

TEST(Dijkstra_Algorithm, Test_Create_Graph_Too_Many_Edges) {
  int numVertex = 10;
  int numEdges = 50;

  ASSERT_ANY_THROW(graph Graph(numVertex, numEdges));
}

TEST(Dijkstra_Algorithm, Test_Get_Random_Linked_Graph) {
  int numVertex = 10;
  int numEdges = 30;
  graph Graph(numVertex, numEdges);

  ASSERT_NO_THROW(Graph.getRandLinkGraph());
}

TEST(Dijkstra_Algorithm, Test_Min_Edges_Get_Tree) {
  int numVertex = 10;
  int numEdges = 9;
  graph Graph(numVertex, numEdges);

  ASSERT_NO_THROW(Graph.getRandLinkGraph());
}

TEST(Dijkstra_Algorithm, Test_Max_Edges_Generate_Random_Linked_Graph) {
  int numVertex = 10;
  int numEdges = 45;
  graph Graph(numVertex, numEdges);

  ASSERT_NO_THROW(Graph.getRandLinkGraph());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

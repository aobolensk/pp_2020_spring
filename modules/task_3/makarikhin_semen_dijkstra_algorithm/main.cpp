// Copyright 2020 Makarikhin Semen
#include <gtest/gtest.h>
#include <vector>
#include "./dijkstra_algorithm.h"

TEST(Dijkstra_Algorithm, Test_En_Exception) {
  int vertex = 5;
  int edge = 8;
  Graph g = get_Random_Graph(vertex, edge);
  ASSERT_NO_THROW(Dijkstra_Tbb(g, 0));
}

TEST(Dijkstra_Algorithm, Test_Out_Max_Num_Edge) {
  int vertex = 5;
  int edge = 11;

  ASSERT_ANY_THROW(get_Random_Graph(vertex, edge));
}

TEST(Dijkstra_Algorithm, Test_Out_Min_Num_Edge) {
  int vertex = 5;
  int edge = -1;

  ASSERT_ANY_THROW(get_Random_Graph(vertex, edge));
}

TEST(Dijkstra_Algorithm, Test_Const_Six_Vertex_Graph) {
  int vertex = 6;
  Graph g(vertex);
  std::vector <int> res = { 0, 1, 4, 10, 2, 10 };
  g.weight_list = {
                    {0, 1, 4, 0, 2, 0},
                    {1, 0, 0, 9, 0, 0},
                    {4, 0, 0, 7, 0, 0},
                    {0, 9, 7, 0, 0, 2},
                    {2, 0, 0, 0, 0, 8},
                    {0, 0, 0, 2, 8, 0} };

  ASSERT_EQ(Dijkstra_Tbb(g, 0), res);
}

TEST(Dijkstra_Algorithm, Test_Const_Four_Vertex_Graph) {
  int vertex = 4;
  Graph g(vertex);
  std::vector <int> res = { 0, 12, 8, 7, };
  g.weight_list = { {0, 19, 0, 7},
                    {19, 0, 4, 32},
                    {0, 4, 0, 1},
                    {7, 32, 1, 0} };

  ASSERT_EQ(Dijkstra_Tbb(g, 0), res);
}

TEST(Dijkstra_Algorithm, Test_One_Element_Graph) {
  int vertex = 1;
  int edge = 0;
  Graph g = get_Random_Graph(vertex, edge);
  std::vector<int> res{ 0 };

  ASSERT_EQ(Dijkstra_Tbb(g, 0), res);
}

TEST(Dijkstra_Algorithm, Test_Out_Serch_Vertex) {
  int vertex = 10;
  int edge = 24;
  Graph g = get_Random_Graph(vertex, edge);

  ASSERT_ANY_THROW(Dijkstra_Tbb(g, 14));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  return 0;
}

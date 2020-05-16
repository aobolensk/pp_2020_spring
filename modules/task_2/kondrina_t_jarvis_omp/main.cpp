// Copyright 2020 Kondrina Tatyana

#include <gtest/gtest.h>
#include <omp.h>

#include <iostream>
#include <vector>

#include "../../../modules/task_2/kondrina_t_jarvis_omp/jarvis_omp.h"


TEST(Jarvis_Algorithm, Hull_Test_Seq) {
  std::vector<Point> set{{-1, 3}, {2, 5}, {4, 2},  {2, 0}, {-2, -1},
                         {-4, 1}, {2, 3}, {-1, 2}, {0, 1}, {1, 2}};
  std::vector<Point> hull = buildHull_seq(set);
  std::vector<Point> exp_hull{{-2, -1}, {2, 0},  {4, 2},
                              {2, 5},   {-1, 3}, {-4, 1}};

  ASSERT_EQ(hull, exp_hull);
}

TEST(Jarvis_Algorithm, Hull_Test_OMP) {
  std::vector<Point> set{{-1, 3}, {2, 5}, {4, 2},  {2, 0}, {-2, -1},
                         {-4, 1}, {2, 3}, {-1, 2}, {0, 1}, {1, 2}};
  std::vector<Point> hull = buildHull_omp(set);
  std::vector<Point> exp_hull{{-2, -1}, {2, 0},  {4, 2},
                              {2, 5},   {-1, 3}, {-4, 1}};

  ASSERT_EQ(hull, exp_hull);
}

TEST(Jarvis_Algorithm, Eq_Seq_OMP) {
  std::vector<Point> set = randomSet(10);
  std::vector<Point> hull_s = buildHull_seq(set);
  std::vector<Point> hull_omp = buildHull_omp(set);
  ASSERT_EQ(hull_s, hull_omp);
}

TEST(Jarvis_Algorithm, Hull_Test_100) {
  std::vector<Point> set = randomSet(100);
  ASSERT_NO_THROW(std::vector<Point> hull = buildHull_omp(set));
}

TEST(Jarvis_Algorithm, Set_Wrong_Test) {
  ASSERT_ANY_THROW(std::vector<Point> set = randomSet(2));
}

TEST(Jarvis_Algorithm, Hull_Wrong_Test) {
  std::vector<Point> set = {{0, 1}, {2, 3}};
  ASSERT_ANY_THROW(buildHull_omp(set));
}

TEST(Jarvis_Algorithm, DISABLED_Test_Eff) {
  std::vector<Point> set = randomSet(10000);
  double s_s = omp_get_wtime();
  std::vector<Point> hull_s = buildHull_seq(set);
  double e_s = omp_get_wtime();
  std::cout << "Time seq: " << (e_s - s_s) * 10000 << std::endl;
  double s_omp = omp_get_wtime();
  std::vector<Point> hull_omp = buildHull_omp(set);
  double e_omp = omp_get_wtime();
  std::cout << "Time omp: " << (e_omp - s_omp) * 10000 << std::endl;
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

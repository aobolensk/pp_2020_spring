// Copyright 2020 Kondrina Tatyana

#include <gtest/gtest.h>
#include <tbb/tbb.h>

#include <iostream>
#include <vector>

#include "../../../modules/task_3/kondrina_t_jarvis_tbb/jarvis_tbb.h"


TEST(Jarvis_Algorithm, Hull_Test_Seq) {
  std::vector<Point> set{{-1, 3}, {2, 5}, {4, 2},  {2, 0}, {-2, -1},
                         {-4, 1}, {2, 3}, {-1, 2}, {0, 1}, {1, 2}};
  std::vector<Point> hull = buildHull_seq(set);
  std::vector<Point> exp_hull{{-2, -1}, {2, 0},  {4, 2},
                              {2, 5},   {-1, 3}, {-4, 1}};

  ASSERT_EQ(hull, exp_hull);
}

TEST(Jarvis_Algorithm, Hull_Test_TBB) {
  std::vector<Point> set{{-1, 3}, {2, 5}, {4, 2},  {2, 0}, {-2, -1},
                         {-4, 1}, {2, 3}, {-1, 2}, {0, 1}, {1, 2}};
  std::vector<Point> hull = buildHull_tbb(set);
  std::vector<Point> exp_hull{{-2, -1}, {2, 0},  {4, 2},
                              {2, 5},   {-1, 3}, {-4, 1}};

  ASSERT_EQ(hull, exp_hull);
}

TEST(Jarvis_Algorithm, Eq_Seq_TBB) {
  std::vector<Point> set = randomSet(10);
  std::vector<Point> hull_s = buildHull_seq(set);
  std::vector<Point> hull_tbb = buildHull_tbb(set);
  ASSERT_EQ(hull_s, hull_tbb);
}

TEST(Jarvis_Algorithm, Hull_Test_100) {
  std::vector<Point> set = randomSet(100);
  ASSERT_NO_THROW(std::vector<Point> hull = buildHull_tbb(set));
}

TEST(Jarvis_Algorithm, Set_Wrong_Test) {
  ASSERT_ANY_THROW(std::vector<Point> set = randomSet(2));
}

TEST(Jarvis_Algorithm, Hull_Wrong_Test) {
  std::vector<Point> set = {{0, 1}, {2, 3}};
  ASSERT_ANY_THROW(buildHull_tbb(set));
}

TEST(Jarvis_Algorithm, DISABLED_Test_Eff) {
  std::vector<Point> set = randomSet(100000);
  tbb::tick_count start1 = tbb::tick_count::now();
  std::vector<Point> hull_s = buildHull_seq(set);
  tbb::tick_count end1 = tbb::tick_count::now();
  std::cout << "Time seq: " << (end1 - start1).seconds() << std::endl;
  tbb::tick_count start2 = tbb::tick_count::now();
  std::vector<Point> hull_tbb = buildHull_tbb(set);
  tbb::tick_count end2 = tbb::tick_count::now();
  std::cout << "Time tbb: " << (end2 - start2).seconds() << std::endl;
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

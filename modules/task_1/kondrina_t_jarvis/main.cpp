// Copyright 2020 Kondrina Tatyana

#include <gtest/gtest.h>
#include <vector>
#include <iostream>

#include "../../../modules/task_1/kondrina_t_jarvis/jarvis.h"

TEST(Jarvis_Algorithm, Hull_Test) {
    std::vector<Point> set{{-1, 3}, {2, 5}, {4, 2},  {2, 0}, {-2, -1},
                           {-4, 1}, {2, 3}, {-1, 2}, {0, 1}, {1, 2}};
    std::vector<Point> hull = buildHull(set);
    std::vector<Point> exp_hull{{-2, -1}, {2, 0}, {4, 2}, {2, 5}, {-1, 3}, {-4, 1}};

    ASSERT_EQ(hull, exp_hull);
}

TEST(Jarvis_Algorithm, Random_Set_Test_10) {
    std::vector<Point> set = randomSet(10);
    ASSERT_NO_THROW(std::vector<Point> hull = buildHull(set));
}

TEST(Jarvis_Algorithm, Hull_Test_100) {
    std::vector<Point> set = randomSet(100);
    ASSERT_NO_THROW(std::vector<Point> hull = buildHull(set));
}

TEST(Jarvis_Algorithm, Set_Wrong_Test) {
    ASSERT_ANY_THROW(std::vector<Point> set = randomSet(2));
}

TEST(Jarvis_Algirithm, Hull_Wrong_Test) {
    std::vector<Point> set = {{0, 1}, {2, 3}};
    ASSERT_ANY_THROW(buildHull(set));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

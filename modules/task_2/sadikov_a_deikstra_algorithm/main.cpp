// Copyright 2020 Sadikov Artem
#include <gtest/gtest.h>
#include <vector>
#include "./deikstra_algorithm.h"

TEST(Deikstra_Algorithm_Seq, Test_On_Six_Points_Graph) {
    std::vector<int> g = {0, 7, 9, 0, 0, 14,
                          7, 0, 10, 15, 0, 0,
                          9, 10, 0, 11, 0, 2,
                          0, 15, 11, 0, 6, 0,
                          0, 0, 0, 6, 0, 9,
                          14, 0, 2, 0, 9, 0};

    std::vector<int> res = {5, 6, 3, 1};

    EXPECT_EQ(getMinRange(g, 1, 5), res);
}

TEST(Deikstra_Algorithm_Seq, Test_On_Three_Points) {
    std::vector<int> g = {0, 2, 3,
                          2, 0, 5,
                          3, 5, 0};

    std::vector<int> res = {3, 1};
    EXPECT_EQ(getMinRange(g, 1, 3), res);
}

TEST(Deikstra_Algorithm_Seq, Test_On_Wrong_Arguments) {
    std::vector<int> g = {0, 7, 9, 0, 0, 14,
                          7, 0, 10, 15, 0, 0,
                          9, 10, 0, 11, 0, 2,
                          0, 15, 11, 0, 6, 0,
                          0, 0, 0, 6, 0, 9,
                          14, 0, 2, 0, 9, 0};

    std::vector<int> res = {5, 6, 3, 1};
    EXPECT_EQ(getMinRange(g, 5, 1), res);
}

TEST(Deikstra_Algorithm_Seq, Test_Return_0_If_Equal_Start_And_End) {
    std::vector<int> g = {0, 2, 3,
                          2, 0, 1,
                          3, 1, 0};

    EXPECT_EQ(getMinRange(g, 3, 3), std::vector<int>(1, 0));
}

TEST(Deikstra_Algorithm_Seq, Test_On_Six_Points_Graph_Another_Way) {
    std::vector<int> g = {0, 7, 9, 0, 0, 14,
                          7, 0, 10, 15, 0, 0,
                          9, 10, 0, 11, 0, 2,
                          0, 15, 11, 0, 6, 0,
                          0, 0, 0, 6, 0, 9,
                          14, 0, 2, 0, 9, 0};

    std::vector<int> res = {6, 3, 2};

    EXPECT_EQ(getMinRange(g, 2, 6), res);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

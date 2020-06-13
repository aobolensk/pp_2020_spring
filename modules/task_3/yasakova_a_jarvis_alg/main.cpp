// Copyright 2020 Yasakova Anastasia
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <utility>
#include "tbb/tbb.h"
#include "../../../modules/task_3/yasakova_a_jarvis_alg/jarvis_alg.h"



TEST(TBB_Test, test1) {
    std::vector<std::pair<int, int>> points = { {2, 2}, {7, 3}, {4, 7} };
    std::vector<std::pair<int, int>> res_ = { {2, 2}, {7, 3}, {4, 7} };

    std::vector<std::pair<int, int>> res = tbb_JarvisAlg(points);

     ASSERT_EQ(res, res_);
}

TEST(TBB_Test, test2) {
    std::vector<std::pair<int, int>> points = { {0, 0}, {10, 0}, {10, 10}, {0, 10}, {4, 5}, {3, 1}, {3, 3}, {2, 4} };
    std::vector<std::pair<int, int>> res_ = { {0, 0}, {10, 0}, {10, 10}, {0, 10} };

    std::vector<std::pair<int, int>> res = tbb_JarvisAlg(points);

    ASSERT_EQ(res, res_);
}

TEST(TBB_Test, test3) {
    std::vector<std::pair<int, int>> points = { {0, 0}, {3, 2}, {3, 6}, {9, 6}, {1, 4} };
    std::vector<std::pair<int, int>> res_ = { {0, 0}, {9, 6}, {3, 6}, {1, 4} };

    std::vector<std::pair<int, int>> res = tbb_JarvisAlg(points);

    ASSERT_EQ(res, res_);
}

TEST(TBB_Test, test4) {
    std::vector<std::pair<int, int>> points = { {2, 2}, {5, 3}, {8, 2}, {1, 5},
                                             {3, 6}, {6, 6}, {7, 8}, {9, 9}, {5, 10} };
    std::vector<std::pair<int, int>> res_ = { {2, 2}, {8, 2}, {9, 9}, {5, 10}, {1, 5} };

    std::vector<std::pair<int, int>> res = tbb_JarvisAlg(points);

    ASSERT_EQ(res, res_);
}

TEST(TBB_Test, test5) {
    std::vector<std::pair<int, int>> points = { {2, 0}, {0, 2}, {0, 6}, {2, 8}, {5, 3}, {2, 3} };
    std::vector<std::pair<int, int>> res_ = { {2, 0}, {5, 3}, {2, 8}, {0, 6}, {0, 2} };

    std::vector<std::pair<int, int>> res = tbb_JarvisAlg(points);

    ASSERT_EQ(res, res_);
}

TEST(TBB_Test, test6) {
    std::vector<std::pair<int, int>> points = GetRandomPoints(100);

    // tbb::tick_count start1 =tbb:: tick_count::now();
    std::vector<std::pair<int, int>> res_omp = tbb_JarvisAlg(points);
    // tbb::tick_count end1 = tbb::tick_count::now();

    // tbb::tick_count start2 = tbb::tick_count::now();
    std::vector<std::pair<int, int>> res_seq = seq_JarvisAlg(points);
    // tbb::tick_count end2 = tbb::tick_count::now();


    // std::cout << "Sequential: " << (end1 - start1).seconds() << std::endl;
    // std::cout << "Parallel:   " << (end2 - start2).seconds() << std::endl;

    ASSERT_EQ(res_omp, res_seq);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

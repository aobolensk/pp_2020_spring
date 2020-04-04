// Copyright 2020 Lembrikov Stepan
#include <tbb/tbb.h>
#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include "./jarvis_tbb.h"

TEST(Jarvis_TBB, Test_On_3_Points_EQ) {
    size_t size = 3;
    int num_thr = 2;
    std::vector<std::pair<double, double>> answer_seq;
    std::vector<std::pair<double, double>> answer_tbb;
    std::vector<std::pair<double, double>> pr(size);

    pr[0].first = 0;
    pr[0].second = 0;
    pr[1].first = 3;
    pr[1].second = 4;
    pr[2].first = 4;
    pr[2].second = 3;

    answer_tbb = Jarvis_Tbb(pr, num_thr);
    answer_seq = Jarvis_Seq(pr);

    EXPECT_EQ(answer_tbb, answer_seq);
}

TEST(Jarvis_TBB, Test_On_7_Points_EQ) {
    size_t size = 8;
    int num_thr = 2;
    std::vector<std::pair<double, double>> answer_tbb;
    std::vector<std::pair<double, double>> answer_seq;
    std::vector<std::pair<double, double>> pr(size);

    pr[0].first = 0;
    pr[0].second = 0;
    pr[1].first = 5;
    pr[1].second = 0;
    pr[2].first = 3;
    pr[2].second = 0;
    pr[3].first = 5;
    pr[3].second = 3;
    pr[4].first = 3;
    pr[4].second = 4;
    pr[5].first = 1;
    pr[5].second = 5;
    pr[6].first = 3;
    pr[6].second = 6;
    pr[7].first = 1;
    pr[7].second = 1;
    answer_tbb = Jarvis_Tbb(pr, num_thr);
    answer_seq = Jarvis_Seq(pr);

    EXPECT_EQ(answer_tbb, answer_seq);
}

TEST(Jarvis_TBB, Test_On_1_Point_EQ) {
    size_t size = 1;
    int num_thr = 2;
    std::vector<std::pair<double, double>> answer_tbb;
    std::vector<std::pair<double, double>> answer_seq;
    std::vector<std::pair<double, double>> pr(size);

    pr[0].first = 3;
    pr[0].second = 4;
    answer_tbb = Jarvis_Tbb(pr, num_thr);
    answer_seq = Jarvis_Seq(pr);

    EXPECT_EQ(answer_tbb, answer_seq);
}

TEST(Jarvis_TBB, Test_On_2_Equal_Points_EQ) {
    size_t size = 2;
    int num_thr = 2;
    std::vector<std::pair<double, double>> answer_tbb;
    std::vector<std::pair<double, double>> answer_seq;
    std::vector<std::pair<double, double>> pr(size);

    pr[0].first = 3;
    pr[0].second = 4;
    pr[1].first = 3;
    pr[1].second = 4;
    answer_tbb = Jarvis_Tbb(pr, num_thr);
    answer_seq = Jarvis_Seq(pr);

    EXPECT_EQ(answer_tbb, answer_seq);
}

TEST(Jarvis_TBB, Test_On_Random_Points_EQ) {
    std::vector<std::pair<double, double>> a;
    std::vector<std::pair<double, double>> answer_seq;
    std::vector<std::pair<double, double>> answer_tbb;
    std::vector<std::pair<double, double>> answer_omp;
    size_t size_a = 10;
    int num_thr = 2;

    a = getRandomPoints(size_a);
    // tbb::tick_count t1 = tbb::tick_count::now();
    answer_seq = Jarvis_Seq(a);
    // tbb::tick_count t2 = tbb::tick_count::now();
    answer_tbb = Jarvis_Tbb(a, num_thr);
    // tbb::tick_count t3 = tbb::tick_count::now();

    // std::cout << "seq_time = " << (t2 - t1).seconds() << "\n";
    // std::cout << "tbb_time = " << (t3 - t2).seconds() << "\n";

    EXPECT_EQ(answer_seq, answer_tbb);
}

TEST(Jarvis_TBB, Test_On_Negative_Points_EQ) {
    std::vector<std::pair<double, double>> a;
    std::vector<std::pair<double, double>> answer_seq;
    std::vector<std::pair<double, double>> answer_tbb;
    size_t size_a = 10;
    int num_thr = 2;

    a = getNegativePoints(size_a);
    answer_tbb = Jarvis_Tbb(a, num_thr);
    answer_seq = Jarvis_Seq(a);

    EXPECT_EQ(answer_seq, answer_tbb);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

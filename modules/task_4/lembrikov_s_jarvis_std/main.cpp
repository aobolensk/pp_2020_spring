// Copyright 2020 Lembrikov Stepan
#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include "./jarvis_std.h"

TEST(Jarvis_STD, Test_On_3_Points_EQ) {
    size_t size = 3;
    int num_thr = 2;
    std::vector<std::pair<double, double>> answer_seq;
    std::vector<std::pair<double, double>> answer_std;
    std::vector<std::pair<double, double>> pr(size);

    pr[0].first = 3;
    pr[0].second = 4;
    pr[1].first = 4;
    pr[1].second = 3;
    pr[2].first = 0;
    pr[2].second = 0;
    answer_std = Jarvis_Std(pr, num_thr);
    answer_seq = Jarvis_Seq(pr);

    EXPECT_EQ(answer_std, answer_seq);
}

TEST(Jarvis_STD, Test_On_7_Points_EQ) {
    size_t size = 7;
    int num_thr = 2;
    std::vector<std::pair<double, double>> answer_std;
    std::vector<std::pair<double, double>> answer_seq;
    std::vector<std::pair<double, double>> pr(size);

    pr[0].first = 0;
    pr[0].second = 0;
    pr[1].first = 5;
    pr[1].second = 0;
    pr[2].first = 1;
    pr[2].second = 2;
    pr[3].first = 5;
    pr[3].second = 3;
    pr[4].first = 3;
    pr[4].second = 4;
    pr[5].first = 1;
    pr[5].second = 5;
    pr[6].first = 3;
    pr[6].second = 6;
    answer_std = Jarvis_Std(pr, num_thr);
    answer_seq = Jarvis_Seq(pr);

    EXPECT_EQ(answer_std, answer_seq);
}

TEST(Jarvis_STD, Test_On_1_Point_EQ) {
    size_t size = 1;
    int num_thr = 2;
    std::vector<std::pair<double, double>> answer_std;
    std::vector<std::pair<double, double>> answer_seq;
    std::vector<std::pair<double, double>> pr(size);

    pr[0].first = 3;
    pr[0].second = 4;
    answer_std = Jarvis_Std(pr, num_thr);
    answer_seq = Jarvis_Seq(pr);

    EXPECT_EQ(answer_std, answer_seq);
}

TEST(Jarvis_STD, Test_On_2_Equal_Points_EQ) {
    size_t size = 2;
    int num_thr = 2;
    std::vector<std::pair<double, double>> answer_std;
    std::vector<std::pair<double, double>> answer_seq;
    std::vector<std::pair<double, double>> pr(size);

    pr[0].first = 3;
    pr[0].second = 4;
    pr[1].first = 3;
    pr[1].second = 4;
    answer_std = Jarvis_Std(pr, num_thr);
    answer_seq = Jarvis_Seq(pr);

    EXPECT_EQ(answer_std, answer_seq);
}

TEST(Jarvis_STD, Test_On_Random_Points_EQ) {
    std::vector<std::pair<double, double>> a;
    std::vector<std::pair<double, double>> answer_seq;
    std::vector<std::pair<double, double>> answer_std;
    size_t size_a = 10;
    // std::clock_t t1, t2, t3;
    // double seq_time, std_time;
    int num_thr = 2;

    a = getRandomPoints(size_a);
    // t1 = clock();
    answer_seq = Jarvis_Seq(a);
    // t2 = clock();
    answer_std = Jarvis_Std(a, num_thr);
    // t3 = clock();

    // seq_time = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
    // std_time = static_cast<double>(t3 - t2) / CLOCKS_PER_SEC;

    // std::cout << "seq_time = " << seq_time << "\n";
    // std::cout << "omp_time = " << std_time << "\n";

    EXPECT_EQ(answer_seq, answer_std);
}

TEST(Jarvis_STD, Test_On_Negative_Points_EQ) {
    std::vector<std::pair<double, double>> a;
    std::vector<std::pair<double, double>> answer_seq;
    std::vector<std::pair<double, double>> answer_std;
    size_t size_a = 10;
    int num_thr = 2;

    a = getNegativePoints(size_a);
    answer_std = Jarvis_Std(a, num_thr);
    answer_seq = Jarvis_Seq(a);

    EXPECT_EQ(answer_seq, answer_std);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

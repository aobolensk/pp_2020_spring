// Copyright 2020 Lembrikov Stepan
#include <gtest/gtest.h>
#include <vector>
#include <utility>
#include "./jarvis.h"

TEST(Vector_Min_MPI, Test_On_3_Points_EQ) {
    size_t size = 3;
    std::vector<std::pair<double, double>> answer_func(size);
    std::vector<std::pair<double, double>> answer_right(size);
    std::vector<std::pair<double, double>> pr(size);

    pr[0].first = 3;
    pr[0].second = 4;
    pr[1].first = 4;
    pr[1].second = 3;
    pr[2].first = 0;
    pr[2].second = 0;
    answer_right[0].first = 0;
    answer_right[0].second = 0;
    answer_right[1].first = 4;
    answer_right[1].second = 3;
    answer_right[2].first = 3;
    answer_right[2].second = 4;
    answer_func = Jarvis(pr);

    EXPECT_EQ(answer_func, answer_right);
}

TEST(Vector_Min_MPI, Test_On_7_Points_EQ) {
    size_t size = 7;
    size_t size_a = 5;
    std::vector<std::pair<double, double>> answer_func(size_a);
    std::vector<std::pair<double, double>> answer_right(size_a);
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
    answer_right[0].first = 0;
    answer_right[0].second = 0;
    answer_right[1].first = 5;
    answer_right[1].second = 0;
    answer_right[2].first = 5;
    answer_right[2].second = 3;
    answer_right[3].first = 3;
    answer_right[3].second = 6;
    answer_right[4].first = 1;
    answer_right[4].second = 5;
    answer_func = Jarvis(pr);

    EXPECT_EQ(answer_func, answer_right);
}

TEST(Vector_Min_MPI, Test_On_1_Point_EQ) {
    size_t size = 1;
    std::vector<std::pair<double, double>> answer_func(size);
    std::vector<std::pair<double, double>> answer_right(size);
    std::vector<std::pair<double, double>> pr(size);

    pr[0].first = 3;
    pr[0].second = 4;
    answer_right[0].first = 3;
    answer_right[0].second = 4;
    answer_func = Jarvis(pr);

    EXPECT_EQ(answer_func, answer_right);
}

TEST(Vector_Min_MPI, Test_On_2_Equal_Points_EQ) {
    size_t size = 2;
    size_t size_a = 1;
    std::vector<std::pair<double, double>> answer_func(size);
    std::vector<std::pair<double, double>> answer_right(size_a);
    std::vector<std::pair<double, double>> pr(size);

    pr[0].first = 3;
    pr[0].second = 4;
    pr[1].first = 3;
    pr[1].second = 4;
    answer_right[0].first = 3;
    answer_right[0].second = 4;
    answer_func = Jarvis(pr);

    EXPECT_EQ(answer_func, answer_right);
}

TEST(Vector_Min_MPI, Test_On_Random_Points_EQ) {
    std::vector<std::pair<double, double>> a;
    std::vector<std::pair<double, double>> answer;
    size_t size;
    size_t size_a = 2;

    a = getRandomPoints(size_a);
    answer = Jarvis(a);
    size = answer.size();

    EXPECT_EQ(size_a, size);
}

TEST(Vector_Min_MPI, Test_On_Random_Points_NE) {
    std::vector<std::pair<double, double>> a;
    std::vector<std::pair<double, double>> answer;
    size_t size;
    size_t size_a = 2;

    a = getRandomPoints(size_a);
    answer = Jarvis(a);
    size = answer.size();

    EXPECT_NE(size_a + 1, size);
}

TEST(Vector_Min_MPI, Test_On_Negative_Points_EQ) {
    std::vector<std::pair<double, double>> a;
    std::vector<std::pair<double, double>> answer;
    size_t size;
    size_t size_a = 2;

    a = getNegativePoints(size_a);
    answer = Jarvis(a);
    size = answer.size();

    EXPECT_EQ(size_a, size);
}

TEST(Vector_Min_MPI, Test_On_Negative_Points_NE) {
    std::vector<std::pair<double, double>> a;
    std::vector<std::pair<double, double>> answer;
    size_t size;
    size_t size_a = 2;

    a = getNegativePoints(size_a);
    answer = Jarvis(a);
    size = answer.size();

    EXPECT_NE(size_a + 1, size);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

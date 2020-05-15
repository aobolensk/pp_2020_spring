// Copyright 2020 Trenina Elizaveta

#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include <iostream>

#include "./convex_hull_graham.h"


TEST(Graham_Alg, Test_cmp) {
    point B(5.0, 10.0);
    point C(10.0, 2.0);
    bool res = cmp(B, C);
    ASSERT_EQ(res, 0);
}

TEST(Graham_Alg, Test_cmp1) {
    point B(5.0, 10.0);
    point C(10.0, 2.0);
    bool res = cmp(C, B);
    ASSERT_EQ(res, 1);
}

TEST(Graham_Alg, Test_cmp2) {
    point B(5.0, 10.0);
    point C(5.0, 10.0);
    bool res = cmp(B, C);
    ASSERT_EQ(res, 0);
}

TEST(Graham_Alg, Test_cmp3) {
    point B(5.0, 10.0);
    point C(10.0, 2.0);
    point D(10.0, 3.0);
    bool res = cmp(C, D);
    ASSERT_EQ(res, 1);
    res = cmp(D, B);
    ASSERT_EQ(res, 1);
    res = cmp(C, B);
    ASSERT_EQ(res, 1);
}


TEST(Graham_Alg, Test_sort) {
    std::vector<point> Q{ {0, 0}, {-1, 3}, {2, 5}, {4, 2}, {2, 0} };
    std::vector<point> exp{ {0, 0}, {2, 0}, {4, 2}, {2, 5}, {-1, 3} };

    std::sort(Q.begin() + 1, Q.end(), cmp);

    ASSERT_EQ(Q, exp);
}


TEST(Graham_Alg, Test_rotate1) {
    point A(0.0, 0.0), B(1.0, 1.0), C(1.0, 5.0);
    ASSERT_EQ(1, rotate(A, B, C));
}

TEST(Graham_Alg, Test_rotate2) {
    point A(0.0, 0.0), B(1.0, 1.0), C(1.0, 5.0);
    ASSERT_EQ(0, rotate(C, B, A));
}

TEST(Graham_Alg, Test_Getrand3) {
    unsigned int n = 5;
    std::vector<point> Q = GetRandSet(n);
    ASSERT_EQ(Q.size(), n);
}



TEST(Graham_Alg, Graham_Test) {
    std::vector<point> Q{ {-1, 3}, {2, 5}, {4, 2}, {2, 0}, {-2, -1},
                               {-4, 1}, {2, 3}, {-1, 2}, {0, 1}, {1, 2} };
    std::vector<point> hull = Graham(Q);
    std::vector<point> exp_hull{ {-2, -1}, {2, 0}, {4, 2}, {2, 5}, {-1, 3}, {-4, 1} };
    ASSERT_EQ(hull.size(), exp_hull.size());
    for (size_t i = 0; i < hull.size(); i++) {
        ASSERT_DOUBLE_EQ(hull[i].x, exp_hull[i].x);
        ASSERT_DOUBLE_EQ(hull[i].y, exp_hull[i].y);
    }
}

// TEST(Graham_Alg, Graham_Test_rand) {
//    int size = 10;
//    std::vector<point> Q = GetRandSet(size);
//    std::vector<point>res = Graham(Q);
// }




int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

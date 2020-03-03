// Copyright 2020 Gaydaychuk Yury
#include <gtest/gtest.h>
#include <vector>
#include "./bitwise_oddeven_sort.h"

TEST(Sequential, Test_Sorted) {
    std::vector<int> vec = {1, 2, 3, 4};
    ASSERT_EQ(true, checkAscending(vec));
}

TEST(Sequential, Test_UnSorted) {
    std::vector<int> vec = {1, 2, 3, 0};
    ASSERT_EQ(false, checkAscending(vec));
}

TEST(Sequential, Test_FirstSort) {
    std::vector<int> vec = {1, 3, 4, 2};
    bitwiseSort(&vec);
    ASSERT_EQ(true, checkAscending(vec));
}

TEST(Sequential, Test_SecondSort) {
    std::vector<int> vec = {4, 3, 2, 1};
    bitwiseSort(&vec);
    ASSERT_EQ(true, checkAscending(vec));
}

TEST(Sequential, Test_ThirdSort) {
    std::vector<int> vec = {4, 3, 3, 2, 1};
    bitwiseSort(&vec);
    ASSERT_EQ(true, checkAscending(vec));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

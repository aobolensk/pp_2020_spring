// Copyright 2020 Gaydaychuk Yury
#include <gtest/gtest.h>
#include <vector>
#include "./bitwise_oddeven_sort.h"

TEST(Sequential, Test_Sorted) {
    std::vector<int> vec = {1, 2, 3, 4};
    bool k = checkAscending(vec);
    ASSERT_EQ(true, k);
}

TEST(Sequential, Test_UnSorted) {
    std::vector<int> vec = {1, 2, 3, 0};
    bool k = checkAscending(vec);
    ASSERT_EQ(false, k);
}

TEST(Sequential, Test_FirstSort) {
    std::vector<int> vec = {1, 3, 4, 2};
    bitwiseSort(vec);
    bool k = checkAscending(vec);
    ASSERT_EQ(true, k);
}

TEST(Sequential, Test_SecondSort) {
    std::vector<int> vec = {4, 3, 2, 1};
    bitwiseSort(vec);
    bool k = checkAscending(vec);
    ASSERT_EQ(true, k);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

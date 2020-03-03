// Copyright 2020 Zhivaev Artem

#include <gtest/gtest.h>
#include "./strassen_mult.h"

TEST(Sequential, Assert_true) {
    ASSERT_TRUE(true);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

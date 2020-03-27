// Copyright 2020 Dudchenko Anton

#include <iostream>
#include "gtest/gtest.h"
#include "../../../modules/task_1/dudchenko_a_sobel/dudchenko_a_sobel.h"

TEST(seqSobelFilter, canCreateRandomMatrix) {
    ASSERT_NO_THROW(randImage(5, 5));
}

TEST(seqSobelFilter, randMatrixWithNullSize) {
    ASSERT_ANY_THROW(randImage(0, 0));
}

TEST(seqSobelFilter, emptyMatrix) {
    ASSERT_ANY_THROW(image<uint8_t>(0, 0));
}

TEST(seqSobelFilter, sobelNoThrow) {
    auto img = randImage(5, 5);
    ASSERT_NO_THROW(sobelSequence(img));
}

TEST(seqSobelFilter, sobelChangeMatrix) {
    auto img = randImage(5, 5);
    auto res = sobelSequence(img);
    ASSERT_EQ(img._columns, res._columns);
    ASSERT_EQ(img._rows, res._rows);
    ASSERT_NE(img._matrix, res._matrix);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Copyright 2020 Dudchenko Anton

#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_3/dudchenko_a_sobel_tbb/dudchenko_a_sobel_tbb.h"

TEST(imageStructure, canCompareImages) {
    image<int> img1({1, 2, 3, 4}, 2, 2);
    image<int> img2({1, 2, 3, 4}, 2, 2);
    image<int> img3({1, 0, 3, 4}, 2, 2);
    image<int> img4({1, 2, 3, 4}, 1, 4);

    ASSERT_TRUE(img1 == img1);
    ASSERT_TRUE(img1 == img2);

    ASSERT_FALSE(img1 == img3);
    ASSERT_FALSE(img1 == img4);
}

TEST(imageStructure, canCreateRandomMatrix) {
    ASSERT_NO_THROW(randImage(5, 5));
}

TEST(imageStructure, randMatrixWithNullSize) {
    ASSERT_ANY_THROW(randImage(0, 0));
}

TEST(imageStructure, createMatrixWithIncorrectSize) {
    ASSERT_ANY_THROW(image<int> ({1, 2, 3, 4}, 1, 2));
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

TEST(tbbSobelFilter, sobelChangeMatrix) {
    auto img = randImage(5, 5);
    auto res = sobelTbb(img);
    ASSERT_EQ(img._columns, res._columns);
    ASSERT_EQ(img._rows, res._rows);
    ASSERT_NE(img._matrix, res._matrix);
}


TEST(tbbSobelFilter, seqAndParIsEqual) {
    auto img = randImage(99, 101);

    auto parRes = sobelTbb(img);
    auto seqRes = sobelSequence(img);

    ASSERT_EQ(parRes, seqRes);
}

TEST(parallelSobelFilter, returnExpectedResult) {
    std::vector<uint8_t> inMatrix(100, 50);
    for (uint8_t i = 0; i < 10; i++) {
        inMatrix[i * 10 + i] = 200;  // Diagonal of light pixels.
    }

    std::vector<uint8_t> expectedMatrix(100, 0);

    for (int i = 2; i < 9; i++) {
        expectedMatrix[i * 10 + i - 1] = 255;  // White pixels above and below main diagonal.
        expectedMatrix[(i - 1) * 10 + i] = 255;
        int color = 212;
        expectedMatrix[(i + 1) * 10 + i - 1] = color;  // Gray pixels below white pixels.
        expectedMatrix[(i - 1) * 10 + i + 1] = color;  // Gray pixels above white pixels.
    }

    for (int i = 0; i < 10; i++) {
        // Black border (3x3 mask).
        expectedMatrix[i] = 0;
        expectedMatrix[i * 10] = 0;
        expectedMatrix[i * 10 + 9] = 0;
        expectedMatrix[90 + i] = 0;
    }

    image<uint8_t> inImage(inMatrix, 10, 10);
    image<uint8_t> expectedImage(expectedMatrix, 10, 10);

    auto parResult = sobelTbb(inImage);
    auto seqResult = sobelSequence(inImage);

    ASSERT_EQ(seqResult, parResult);
    ASSERT_EQ(parResult, expectedImage);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

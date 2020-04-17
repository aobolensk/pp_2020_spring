// Copyright 2020 Dudchenko Anton

#include <iostream>
#include <omp.h>
#include "gtest/gtest.h"
#include "../../../modules/task_2/dudchenko_a_sobel_omp/dudchenko_a_sobel_omp.h"

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

TEST(parallelSobelFilter, sobelChangeMatrix) {
    auto img = randImage(5, 5);
    auto res = sobelOmp(img);
    ASSERT_EQ(img._columns, res._columns);
    ASSERT_EQ(img._rows, res._rows);
    ASSERT_NE(img._matrix, res._matrix);
}

TEST(parallelSobelFilter, seqAndParIsEqual) {
    auto img = randImage(1000, 1000);

    auto startPar = omp_get_wtime();
    auto parRes = sobelOmp(img);
    auto stopPar = omp_get_wtime();

    auto startSeq = omp_get_wtime();
    auto seqRes = sobelSequence(img);
    auto stopSeq = omp_get_wtime();

    std::cout << "Sequnce: " << stopSeq - startSeq << "\n"
              << "Parallel: " << stopPar - startPar << "\n"
              << "Delta: " << stopSeq - startSeq - stopPar + startPar << "\n";

    ASSERT_EQ(parRes, seqRes);
}

TEST(parallelSobelFilter, returnExpectedResult) {
    std::vector<uint8_t> inMatrix(100);

    for (uint8_t i = 0; i < 100; i++) {
        inMatrix[i] = i;
    }

    std::vector<uint8_t> expectedMatrix = {};

    image<uint8_t> inImage(inMatrix, 10, 10);
//    image<uint_8> expectedImage(expectedMatrix, 10, 10);

    for (auto el : inImage._matrix) {
        std::cout << (unsigned int)el << " ";
    }
    std::cout << "\n";

    auto result = sobelOmp(inImage);
    for (auto el : result._matrix) {
        std::cout << (unsigned int)el << " ";
    }
//    ASSERT_EQ(result, expectedImage);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

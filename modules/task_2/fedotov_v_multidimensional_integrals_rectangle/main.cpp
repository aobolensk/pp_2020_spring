// Copyright 2020 Fedotov Vladislav
#include <gtest/gtest.h>
#include <omp.h>
#include "./integrals-rectangle.h"
#define PRINTF 0

TEST(MultiDimensionalIntegralRectangle, func1) {
    double x1 = 0;
    double x2 = 2;
    double y1 = 0;
    double y2 = 2;
    double stepX = 0.01;
    double stepY = 0.01;
    double (*passingFunc)(double, double) = &function1;
    double trueIntegral = 10.67;
    double startTime, endTime;
    startTime = omp_get_wtime();
    double integral = getMultipleIntegralUsingRectangleMethod(passingFunc,
               x1, x2, y1, y2, stepX, stepY);
    endTime = omp_get_wtime();
    if (PRINTF) printf("Func 1 test time: %f", endTime - startTime);

    ASSERT_NEAR(trueIntegral, integral, 0.1);
}

TEST(MultiDimensionalIntegralRectangle, func2) {
    double x1 = -1;
    double x2 = 3;
    double y1 = 0;
    double y2 = 2;
    double stepX = 0.01;
    double stepY = 0.01;
    double (*passingFunc)(double, double) = &function2;
    double trueIntegral = 1.59;
    double startTime, endTime;
    startTime = omp_get_wtime();
    double integral = getMultipleIntegralUsingRectangleMethod(passingFunc,
               x1, x2, y1, y2, stepX, stepY);
    endTime = omp_get_wtime();
    if (PRINTF) printf("Func 2 test time: %f", endTime - startTime);

    ASSERT_NEAR(trueIntegral, integral, 0.001);
}

TEST(MultiDimensionalIntegralRectangle, func3) {
    double x1 = 1;
    double x2 = 4;
    double y1 = -3;
    double y2 = 0;
    double stepX = 0.01;
    double stepY = 0.01;
    double (*passingFunc)(double, double) = &function3;
    double trueIntegral = -0.34;
    double startTime, endTime;
    startTime = omp_get_wtime();
    double integral = getMultipleIntegralUsingRectangleMethod(passingFunc,
               x1, x2, y1, y2, stepX, stepY);
    endTime = omp_get_wtime();
    if (PRINTF) printf("Func 3 test time: %f", endTime - startTime);

    ASSERT_NEAR(trueIntegral, integral, 0.1);
}

TEST(MultiDimensionalIntegralRectangle, func4) {
    double x1 = 1;
    double x2 = 6;
    double y1 = 0;
    double y2 = 7;
    double stepX = 0.01;
    double stepY = 0.01;
    double (*passingFunc)(double, double) = &function4;
    double trueIntegral = 1.76;
    double startTime, endTime;
    startTime = omp_get_wtime();
    double integral = getMultipleIntegralUsingRectangleMethod(passingFunc,
               x1, x2, y1, y2, stepX, stepY);
    endTime = omp_get_wtime();
    if (PRINTF) printf("Func 4 test time: %f", endTime - startTime);

    ASSERT_NEAR(trueIntegral, integral, 0.1);
}

TEST(MultiDimensionalIntegralRectangle, DISABLED_func5) {
    double x1 = 2;
    double x2 = 8;
    double y1 = 1;
    double y2 = 7;
    double stepX = 0.001;
    double stepY = 0.001;
    double (*passingFunc)(double, double) = &function5;
    double trueIntegral = 2880;
    double startTime, endTime;
    startTime = omp_get_wtime();
    double integral = getMultipleIntegralUsingRectangleMethod(passingFunc,
               x1, x2, y1, y2, stepX, stepY);
    endTime = omp_get_wtime();
    if (PRINTF) printf("Func 5 test time: %f", endTime - startTime);

    ASSERT_NEAR(trueIntegral, integral, 0.1);
}

TEST(MultiDimensionalIntegralRectangle, func6) {
    double x1 = 1;
    double x2 = 2;
    double y1 = 1;
    double y2 = 2;
    double stepX = 0.1;
    double stepY = 0.1;
    double (*passingFunc)(double, double) = &function6;
    double trueIntegral = 2.25;
    double startTime, endTime;
    startTime = omp_get_wtime();
    double integral = getMultipleIntegralUsingRectangleMethod(passingFunc,
               x1, x2, y1, y2, stepX, stepY);
    endTime = omp_get_wtime();
    if (PRINTF) printf("Func 6 test time: %f", endTime - startTime);

    ASSERT_NEAR(trueIntegral, integral, 0.1);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

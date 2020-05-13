// Copyright 2020 Fedotov Vladislav
#include "../../modules/task_3/fedotov_v_multidimensional_integrals_rectangle/integrals-rectangle.h"
#include <iostream>
#include <cmath>

// sequential version
double getMultipleIntegralUsingRectangleMethod(
    double (*function)(double, double), double x1, double x2,
    double y1, double y2, double stepX, double stepY) {
    double resultIntegral = 0;
    double cellSquare = stepX * stepY;
    int xStepsNumber = (x2 - x1) / stepX;
    int yStepsNumber = (y2 - y1) / stepY;

    for (int i = 0; i < xStepsNumber; i++) {
        for (int j = 0; j < yStepsNumber; j++) {
            double xMiddle = (x1 + i*stepX + x1 + i*stepX + stepX) / 2;
            double yMiddle = (y1 + j*stepY + y1 + j*stepY + stepY) / 2;

            resultIntegral += function(xMiddle, yMiddle);
        }
    }

    return resultIntegral * cellSquare;  // common factor
}

// TBB version
double getMultipleIntegralUsingRectangleMethodTBB(
    double (*function)(double, double), double x1, double x2,
    double y1, double y2, double stepX, double stepY) {
    double resultIntegral = 0;
    double cellSquare = stepX * stepY;
    int xStepsNumber = (x2 - x1) / stepX;
    int yStepsNumber = (y2 - y1) / stepY;
    printf("xStepsNumber %d\n", xStepsNumber);
    printf("yStepsNumber %d\n", yStepsNumber);


    resultIntegral = tbb::parallel_reduce(
        tbb::blocked_range2d<int, int>{0, xStepsNumber, 0, yStepsNumber},
         0.f, [&](const tbb::blocked_range2d<int, int> &r,
          double localIntegral)->double {
        int x_begin = r.rows().begin();
        int x_end = r.rows().end();
        int y_begin = r.cols().begin();
        int y_end = r.cols().end();

        // printf("x_begin %d\n", x_begin);
        // printf("y_begin %d\n", y_begin);

        for (int i = x_begin; i < x_end; i++) {
            for (int j = y_begin; j < y_end; j++) {
                double xMiddle = (x1 + i*stepX + x1 + i*stepX + stepX) / 2;
                double yMiddle = (y1 + j*stepY + y1 + j*stepY + stepY) / 2;

                localIntegral += function(xMiddle, yMiddle);
            }
        }
        return localIntegral;
    }, [](double localIntegral1, double localIntegral2)-> double {
            return localIntegral1 + localIntegral2;
        });

    return resultIntegral * cellSquare;  // common factor
}

double function1(double x, double y) {
    return x*x + y*y;
}

double function2(double x, double y) {
    return sin(x*y);
}

double function3(double x, double y) {
    return cos(x*y);
}

double function4(double x, double y) {
    return sin(x*y) - cos(x*y);
}

double function5(double x, double y) {
    return 3*x*x - y;
}

double function6(double x, double y) {
    return x*y;
}

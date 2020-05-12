// Copyright 2020 Fedotov Vladislav
#include "../../modules/task_2/fedotov_v_multidimensional_integrals_rectangle/integrals-rectangle.h"
#include <iostream>
#include <cmath>

double getMultipleIntegralUsingRectangleMethod(
    double (*function)(double, double), double x1, double x2,
    double y1, double y2, double stepX, double stepY) {
    double resultIntegral = 0;
    double cellSquare = stepX * stepY;
    int xStepsNumber = (x2 - x1) / stepX;
    int yStepsNumber = (y2 - y1) / stepY;

    #pragma omp parallel for reduction(+: resultIntegral)
    for (int i = 0; i < xStepsNumber; i++) {
        for (int j = 0; j < yStepsNumber; j++) {
            double xMiddle = (x1 + i*stepX + x1 + i*stepX + stepX) / 2;
            double yMiddle = (y1 + j*stepY + y1 + j*stepY + stepY) / 2;

            resultIntegral += function(xMiddle, yMiddle);
        }
    }

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

// Copyright 2020 Fedotov Vladislav
#include "../../modules/task_1/fedotov_v_multidimensional_integrals_rectangle/integrals-rectangle.h"
#include <iostream>
#include <cmath>

double getMultipleIntegralUsingRectangleMethod(
    double (*function)(double, double), double x1, double x2,
    double y1, double y2, double stepX, double stepY) {
    double resultIntegral = 0;
    double cellSquare = stepX * stepY;

    for (double i = x1; i < x2; i += stepX) {
        for (double j = y1; j < y2; j += stepY) {
            double xMiddle = (i + i + stepX) / 2;
            double yMiddle = (j + j + stepY) / 2;

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

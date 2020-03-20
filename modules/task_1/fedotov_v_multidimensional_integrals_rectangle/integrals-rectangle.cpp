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
            double xMiddle = (i + stepX) / 2;
            double yMiddle = (j + stepY) / 2;

            resultIntegral += function(xMiddle, yMiddle);
        }
    }

    resultIntegral *= cellSquare;  // common factor

    return resultIntegral;
}

double function1(double x, double y) {
    return x - y;
}

double function2(double x, double y) {
    return x*x + y*y;
}

double function3(double x, double y) {
    return sin(x*y);
}

double function4(double x, double y) {
    return cos(x*y);
}

double function5(double x, double y) {
    return sin(x*y) - cos(x*y);
}

int main() {
    double (*passingFunc)(double, double) = nullptr;
    passingFunc = &function1;

    double integral = getMultipleIntegralUsingRectangleMethod(passingFunc,
                                                    0, 2, 0, 2, 0.01, 0.01);

    std::cout << integral << std::endl;

    passingFunc = &function2;
    integral = getMultipleIntegralUsingRectangleMethod(passingFunc,
                                                    0, 2, 0, 2, 0.001, 0.001);

    std::cout << integral << std::endl;

    passingFunc = &function3;
    integral = getMultipleIntegralUsingRectangleMethod(passingFunc,
                                                    0, 2, 0, 2, 0.01, 0.01);

    std::cout << integral << std::endl;
}

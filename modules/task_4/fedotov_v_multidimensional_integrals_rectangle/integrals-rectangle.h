// Copyright 2020 Fedotov Vladislav
#ifndef MODULES_TASK_4_FEDOTOV_V_MULTIDIMENSIONAL_INTEGRALS_RECTANGLE_INTEGRALS_RECTANGLE_H_
#define MODULES_TASK_4_FEDOTOV_V_MULTIDIMENSIONAL_INTEGRALS_RECTANGLE_INTEGRALS_RECTANGLE_H_
#include <thread>
#include <mutex>
#include <vector>
#include<algorithm>

double getMultipleIntegralUsingRectangleMethod(
    double (*function)(double, double), double x1,
    double x2, double y1, double y2, double stepX, double stepY);
double getMultipleIntegralUsingRectangleMethodSTD(
    double (*function)(double, double), double x1,
    double x2, double y1, double y2, double stepX, double stepY);
void increaseResultIntegral(double* resultIntegral, int startStep,
    int numberOfSteps, int yStepsNumber, double (*function)(double, double),
    double x1, double x2, double y1, double y2, double stepX, double stepY);

double function1(double x, double y);
double function2(double x, double y);
double function3(double x, double y);
double function4(double x, double y);
double function5(double x, double y);
double function6(double x, double y);

#endif  // MODULES_TASK_4_FEDOTOV_V_MULTIDIMENSIONAL_INTEGRALS_RECTANGLE_INTEGRALS_RECTANGLE_H_

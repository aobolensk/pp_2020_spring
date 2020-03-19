// Copyright 2020 Fedotov Vladislav
#include "../../modules/task_1/fedotov_v_multidimensional_integrals_rectangle/integrals-rectangle.h"
#include <iostream>

double getMultipleIntegralUsingRectangleMethod(double (*function)(double, double), double x1, double x2, double y1, double y2, double stepX, double stepY) {
	double resultIntegral = 0;
	double cellSquare = stepX * stepY;

	for (double i = x1; i < x2; i += stepX) {
		for (double j = y1; j < y2; j += stepY) {
			double xMiddle = (i + stepX) / 2;
			double yMiddle = (j + stepY) / 2;

			resultIntegral += function(xMiddle, yMiddle);
		}
	}

	resultIntegral *= cellSquare; // common factor

	return resultIntegral;
}

double function1(double x, double y) {
	return x - y;
}

int main() {
	double (*passingFunc)(double, double) = nullptr;
	passingFunc = &function1;

	double integral = getMultipleIntegralUsingRectangleMethod(passingFunc, 0, 2, 0, 2, 0.1, 0.1);

	std::cout << integral;
}
// Copyright 2020 Vikhrev Ivan

#ifndef MODULES_TASK_1_VIKHREV_SOBEL_EDGE_DETECTION_SOBEL_EDGE_DETECTION_H_
#define MODULES_TASK_1_VIKHREV_SOBEL_EDGE_DETECTION_SOBEL_EDGE_DETECTION_H_

#include <vector>
#include <string>
#include <random>
#include <iostream>


template <class T>
struct image {
	    std::vector<T> data;
		size_t rows{ 0 };
		size_t cols{ 0 };
		size_t size{ 0 };
		image() {};
		image(size_t r, size_t c);
		image(size_t r, size_t c, std::vector<T> d);
		image(const image<T>& img);
};

using imageU=image<uint8_t>;
using imageS=image<char>;


std::vector<uint8_t> randImg(size_t rows, size_t cols);

std::vector<uint8_t> sobel(std::vector<uint8_t>& img);


#endif  // MODULES_TASK_1_VIKHREV_SOBEL_EDGE_DETECTION_SOBEL_EDGE_DETECTION_H_
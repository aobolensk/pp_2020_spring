// Copyright 2020 Vikhrev Ivan

#include "sobel_edge_detection.h"

template<class T>
image<T>::image(size_t c, size_t r) {
	size = r * c;
	rows = r;
	cols = c;
	data.resize(size);

	std::random_device rnd_device;
	std::mt19937 mersenne_engine{ rnd_device() };
	std::uniform_int_distribution<int> uint_dist{ 0,256 };
	auto gen = [&uint_dist, &mersenne_engine]() {
		return uint_dist(mersenne_engine);
	};

	generate(begin(data), end(data), gen);
	for (auto a : data) {
		std::cout << static_cast<int>(a) << " ";
	}
}

template<class T>
image<T>::image(size_t c, size_t r, std::vector<T> d) {
	size = r * c;
	rows = r;
	cols = c;
	data = d;
}

template<class T>
image<T>::image(const image<T> &img) {
	size = img.size;
	rows = img.rows;
	cols = img.cols;
	data = img.data;
}

//std::vector<uint8_t> randImg(size_t rows, size_t cols){
//    std::random_device rnd_device;
//    std::mt19937 mersenne_engine{rnd_device()};
//	std::uniform_int_distribution<int> uint_dist{ 0,256 };
//    
//	auto gen = [&uint_dist, &mersenne_engine](){
//                   return uint_dist(mersenne_engine);
//               };
//
//    std::vector<uint8_t> img(rows*cols);
//    generate(begin(img), end(img), gen);
//    // Optional
//	for (auto a : img) {
//			std::cout << static_cast<int>(a) << " ";
//	}
//    return img;
//}

imageU sobel(imageU img) {
	imageS kernX(3, 3, { 1, 0, -1, 2, 0, -2, 1, 0, -1 });
	
	imageS kernY(3, 3, { 1, 2, 1, 0, 0, 0, -1, -2, -1 });
	imageU res;

	for (size_t i = 0; i < img.rows; ++i) {
		for (size_t j = 0; j < img.cols; ++j) {

		}
	}


    return {};
}
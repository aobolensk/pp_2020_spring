// Copyright 2020 Vikhrev Ivan

#ifndef MODULES_TASK_1_VIKHREV_SOBEL_EDGE_DETECTION_SOBEL_EDGE_DETECTION_H_
#define MODULES_TASK_1_VIKHREV_SOBEL_EDGE_DETECTION_SOBEL_EDGE_DETECTION_H_

#include <vector>
#include <random>
#include <iostream>

template <class T>
struct image {
        std::vector<T> data;
        int rows{ 0 };
        int cols{ 0 };
        int size{ 0 };
        image() {}
        image(int r, int c);
        image(int r, int c, std::vector<T> d);
        image(const image<T>& img);
        void randImage(int r, int c);
};

/*----------------------------------------------------------------------*/
template<class T>
image<T>::image(int r, int c) {
    size = r * c;
    rows = r;
    cols = c;
    data.assign(size, 0);
}

template<class T>
image<T>::image(int r, int c, std::vector<T> d) {
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

template<class T>
void image<T>::randImage(int r, int c) {
    size = r * c;
    rows = r;
    cols = c;
    data.resize(size);
    std::random_device rnd_device;
    std::mt19937 mersenne_engine{ rnd_device() };
    std::uniform_int_distribution<int> uint_dist{ 0, 256 };
    auto gen = [&uint_dist, &mersenne_engine]() {
        return uint_dist(mersenne_engine);
    };
    generate(begin(data), end(data), gen);
    for (auto a : data) {
        std::cout << static_cast<int>(a) << " ";
    }
}


using imageU = image<uint8_t>;
using imageS = image<char>;

imageU  sobel(const imageU& img);


#endif  // MODULES_TASK_1_VIKHREV_SOBEL_EDGE_DETECTION_SOBEL_EDGE_DETECTION_H_

// Copyright 2020 Dudchenko Anton

#ifndef PP_2020_SPRING_DUDCHENKO_A_SOBEL_H
#define PP_2020_SPRING_DUDCHENKO_A_SOBEL_H

#include <vector>

template <class T>
struct image {
    std::vector<T> _matrix;
    size_t _columns;
    size_t _rows;
    image(std::vector<T> matrix, size_t columns, size_t rows):_matrix(matrix),
                                                              _columns(columns),
                                                              _rows(rows) {};
    image(size_t columns, size_t rows):_columns(columns),
                                       _rows(rows) {
        if (rows <= 0 || columns <= 0) {
            throw -1;
        }
        _matrix.resize(columns * rows);
        _matrix.assign(_matrix.size(), 0);
    };
};

image<uint8_t> sobelSequence(image<uint8_t> inImage);
image<uint8_t> randImage(size_t r, size_t c);

#endif //PP_2020_SPRING_DUDCHENKO_A_SOBEL_H

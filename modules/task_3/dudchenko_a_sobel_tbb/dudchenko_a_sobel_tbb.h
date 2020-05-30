// Copyright 2020 Dudchenko Anton

#ifndef MODULES_TASK_3_DUDCHENKO_A_SOBEL_TBB_DUDCHENKO_A_SOBEL_TBB_H_
#define MODULES_TASK_3_DUDCHENKO_A_SOBEL_TBB_DUDCHENKO_A_SOBEL_TBB_H_

#include <vector>

template <class T>
struct image {
    std::vector<T> _matrix;
    size_t _columns;
    size_t _rows;
    image(std::vector<T> matrix, size_t columns, size_t rows):_matrix(matrix),
                                                              _columns(columns),
                                                              _rows(rows) {
        if (matrix.size() != rows * columns)
            throw -1;
    }

    image(const image<T>& otherImage) {
        this->_rows = otherImage._rows;
        this->_columns = otherImage._columns;
        this->_matrix = otherImage._matrix;
    }

    image(size_t columns, size_t rows):_columns(columns),
                                       _rows(rows) {
        if (rows <= 0 || columns <= 0) {
            throw -1;
        }
        _matrix.resize(columns * rows);
        _matrix.assign(_matrix.size(), 0);
    }

    bool operator==(const image& img) const {
        return this->_matrix == img._matrix &&
               this->_rows == img._rows &&
               this->_columns == img._columns;
    }
};

image<uint8_t> sobelSequence(image<uint8_t> inImage);
image<uint8_t> sobelTbb(image<uint8_t> inImage);
image<uint8_t> randImage(size_t r, size_t c);

#endif  // MODULES_TASK_3_DUDCHENKO_A_SOBEL_TBB_DUDCHENKO_A_SOBEL_TBB_H_

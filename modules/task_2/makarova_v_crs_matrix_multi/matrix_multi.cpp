// Copyright 2020 Makarova Viktoria
#include <omp.h>
#include <random>
#include <ctime>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "../../../modules/task_2/makarova_v_crs_matrix_multi/matrix_multi.h"

Matrix generateRandomMat(int rows, int cols) {
    std::mt19937 gen;
    gen.seed((unsigned)time(0));
    std::uniform_int_distribution<int> dis(-255, 255);
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; ++i) {
        if (dis(gen) > 128) {
            result.val[i] = std::complex<int>(dis(gen), dis(gen));
        } else {
            result.val[i] = 0;
        }
    }
    return result;
}

MatrixCRS generateRandomCRSMat(int rows, int cols) {
    return convert(generateRandomMat(rows, cols));
}

MatrixCRS convert(const Matrix &inMat) {
    MatrixCRS result;
    result.rows = inMat.rows;
    result.cols = inMat.cols;

    int count;

    count = 1;
    result.ptrs.emplace_back(count);
    for (int i = 0; i < inMat.rows; ++i) {
        count = 0;
        for (int j = 0; j < inMat.cols; ++j) {
            if (inMat.val.at(inMat.cols * i + j) != 0) {
                ++count;

                result.val.emplace_back(inMat.val[inMat.cols * i + j]);
                result.cols_pos.emplace_back(j);
            }
        }

        count += result.ptrs.back();
        result.ptrs.emplace_back(count);
    }

    return result;
}

MatrixCRS transp(const MatrixCRS &inMat) {
    // generate out mat
    Matrix just_mat(inMat.rows, inMat.cols);
    int t = static_cast<int>(inMat.ptrs.size());
#pragma omp parallel for
    for (int i = 1; i < t; ++i) {
        // i its rows
        for (int j = inMat.ptrs[i - 1]; j < inMat.ptrs[i]; ++j) {
            just_mat.val[just_mat.cols * (i - 1) +
             inMat.cols_pos[j - 1]] = inMat.val[j - 1];
        }
    }

    // get tr matCRS from out mat
    MatrixCRS result;
    result.cols = inMat.cols;
    result.rows = inMat.rows;
    int count;

    count = 1;
    result.ptrs.emplace_back(1);
    for (int j = 0; j < just_mat.rows; ++j) {
        count = 0;
        for (int i = 0; i < just_mat.cols; ++i) {
            if (just_mat.val[just_mat.cols * i + j] != 0) {
                ++count;
                result.val.emplace_back(just_mat.val[inMat.cols * i + j]);
                result.cols_pos.emplace_back(i);
            }
        }

        count += result.ptrs.back();
        result.ptrs.emplace_back(count);
    }

    return result;
}

Matrix matrixMult(const Matrix &first, const Matrix &second) {
    if (first.cols != second.rows)
        throw std::runtime_error("Matrix dimensions do not match");

    Matrix out(first.rows, second.cols);

    // Now!!! i, j - its out matrix
    for (int i = 0; i < first.rows; ++i)
        for (int j = 0; j < second.cols; ++j) {
            std::complex<int> res = 0;
            for (int k = 0; k < first.cols; ++k)
                res = res + first.val[first.cols * i + k] *
                       second.val[second.cols * k + j];
            out.val[out.cols * i + j] = res;
        }

    return out;
}

MatrixCRS matrixCRSMult(const MatrixCRS &first, const MatrixCRS &second_a) {
    if (first.cols != second_a.rows)
        throw std::runtime_error("Matrix dimensions do not match");

    MatrixCRS second = transp(second_a);

    if (first.ptrs.size() != second.ptrs.size())
            throw std::runtime_error("AAAAAA");

    MatrixCRS out;
    out.rows = first.rows;
    out.cols = second.cols;

    int first_it;
    int second_it;

    int start = 1;
    out.ptrs.emplace_back(start);
    for (size_t i = 1; i < first.ptrs.size(); i++) {
        for (size_t j = 1; j < second.ptrs.size(); j++) {
            // pognali ebat'
            first_it = first.ptrs[i - 1];
            second_it = second.ptrs[j - 1];

            std::complex<int> res = 0;
            while (first_it < first.ptrs[i] && second_it < second.ptrs[j]) {
                if (first.cols_pos[first_it - 1] ==
                 second.cols_pos[second_it - 1]) {
                    res += first.val[first_it - 1] * second.val[second_it - 1];
                    first_it++;
                    second_it++;
                } else {
                    if (first.cols_pos[first_it - 1] <
                     second.cols_pos[second_it - 1])
                        first_it++;
                    else
                        second_it++;
                }
            }

            if (res != 0) {
                out.val.emplace_back(res);
                out.cols_pos.emplace_back(j - 1);
                start++;
            }
        }
        out.ptrs.emplace_back(start);
    }

    return out;
}

void print(const MatrixCRS &in) {
    std::cout <<"vals: "<< std::endl;
    for (size_t i = 0; i < in.val.size(); i++)
        std::cout << in.val[i]<< ' ';
    std::cout << std::endl;

    std::cout <<"cols: "<< std::endl;
    for (size_t i = 0; i < in.cols_pos.size(); i++)
        std::cout << in.cols_pos[i] << ' ';
    std::cout<< std::endl;

    std::cout <<"ptrs: "<< std::endl;
    for (size_t i = 0; i < in.ptrs.size(); i++)
        std::cout << in.ptrs[i] << ' ';
    std::cout<< std::endl;
}

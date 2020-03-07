// Copyright 2020 Korobeinikov Aleksei
#include <algorithm>
#include <vector>
#include <ctime>
#include <utility>
#include <random>
#include "../../modules/task_1/korobeinikov_a_quick_sort/quick_sort.h"


void quickSort(int left, int right, std::vector <double>* arr) {
    while (right > left) {
        int it_l = left;
        int it_r = right;
        double pivot = arr -> at((left + right) / 2);
        // partition
        while (it_l <= it_r) {
            while (arr -> at(it_l) < pivot) {
                it_l++;
            }
            while (arr -> at(it_r) > pivot) {
                it_r--;
            }
            if (it_l <= it_r) {
                std::swap(arr -> at(it_l), arr -> at(it_r));
                it_l++;
                it_r--;
            }
        }
        // recursion
        if (2 * it_l > left + right) {
            quickSort(it_l, right, arr);
            right = it_l - 1;
        } else {
            quickSort(left, it_l - 1, arr);
            left = it_l;
        }
    }
    return;
}

std::vector <double> getRandomVector(int size) {
    std::mt19937 gen(time(0));
    std::uniform_int_distribution <int> dist(-100000, 100000);
    std::vector <double> vec(size);
    for (int i = 0; i < size; ++i) {
        vec[i] = dist(gen);
    }
    return vec;
}

bool checkCorrectnessOfSort(std::vector <double>* vec) {
    return std::is_sorted((*vec).begin(), (*vec).end());
}

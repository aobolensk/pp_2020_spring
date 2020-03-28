// Copyright 2020 Tonkov Alexei

#include <time.h>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
#include "../../../modules/task_1/tonkov_a_odd_even_mergesort/odd_even_mergesort.h"

std::vector<int> getRandomVector(int sz) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<int> vec(sz);
    for (int i = 0; i < sz; i++) {
        vec[i] = gen() % 100;
    }
    return vec;
}

std::vector<int> oddEvenSort(std::vector<int> arr, int n) {
    bool isSorted = false;

    while (!isSorted) {
        isSorted = true;

        // Perform sort on odd indexed element
        for (int i = 1; i <= n - 2; i = i + 2) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }

        // Perform sort on even indexed element
        for (int i = 0; i <= n - 2; i = i + 2) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
    }
    return arr;
}

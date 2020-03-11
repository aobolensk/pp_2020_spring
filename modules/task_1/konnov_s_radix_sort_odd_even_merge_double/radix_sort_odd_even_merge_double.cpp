// Copyright 2020 Konnov Sergey

#include "../../../modules/task_1/konnov_s_radix_sort_odd_even_merge_double/radix_sort_odd_even_merge_double.h"
#include <vector>
#include <ctime>
#include <random>
#include <iostream>


std::vector<double> countingSort(std::vector<double> array, int byteNum) {
    unsigned char* byteArray = reinterpret_cast<unsigned char*>(array.data());
    int counter[256] = {0};
    int offset[256] = {0};
    std::vector<double> ans(array.size());
    for (size_t i = 0; i < array.size(); i++)
        counter[byteArray[8*i+byteNum]]++;
    if (byteNum != 7) {
        for (int i = 1; i < 256; i++)
            offset[i] = offset[i-1] + counter[i-1];
    } else {
        offset[255] = counter[255] - 1;
        for (int i = 254; i >= 128; i--)
            offset[i] = offset[i+1] + counter[i];
        offset[0] = offset[128] + 1;
        for (int i = 1; i < 128; i++)
            offset[i] = offset[i-1] + counter[i-1];
    }
    if (byteNum != 7) {
        for (size_t i = 0; i < array.size(); i++)
            ans[offset[byteArray[8*i+byteNum]]++] = array[i];
    } else {
        for (size_t i = 0; i < array.size(); i++)
            if (byteArray[8*i+byteNum] >= 128) {
                ans[offset[byteArray[8*i+byteNum]]--] = array[i];
            } else {
                ans[offset[byteArray[8*i+byteNum]]++] = array[i];
            }
    }
    return ans;
}

std::vector<double> radixSortOddEvenMergeDouble(const std::vector<double>& array) {
    std::vector<double> tmp = array;
    for (size_t i = 0; i < 8; i++)
        tmp = countingSort(tmp, i);
    return tmp;
}

std::vector<double> getRandomVector(int size, double lower_bound, double upper_bound, int seed) {
    std::mt19937 mt;
    if (seed == -1) {
        mt = std::mt19937(static_cast<int>(time(0)));
    } else {
        mt = std::mt19937(seed);
    }
    std::uniform_real_distribution<double> rand(-500.0, 500.0);
    std::vector<double> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = rand(mt);
    }
    return vec;
}

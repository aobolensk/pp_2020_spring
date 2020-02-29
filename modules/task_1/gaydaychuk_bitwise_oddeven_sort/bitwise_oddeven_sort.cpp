// Copyright 2020 Gaydaychuk Yury
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include "../../../modules/task_1/gaydaychuk_bitwise_oddeven_sort/bitwise_oddeven_sort.h"

bool checkAscending(std::vector<int> vec) {
    int n = vec.size();
    if (n == 0 || n == 1) {
        return true;
    }
    for (int i = 1; i < n; i++) {
        if (vec[i - 1] > vec[i]) {
            return false; 
        }
    }
    return true; 
}

int getMax(std::vector<int> vec) {
    int n = vec.size();
    int max = vec[0]; 
    for (int i = 1; i < n; i++) {
        if (vec[i] > max) {
            max = vec[i]; 
        }
    }
    return max; 
}

void sortByDigit(std::vector<int> &vec, int digit) { 
    int n = vec.size();
    std::vector<int> res(n);
    int i, count[10] = {0}; 
  
    for (i = 0; i < n; i++) {
        count[(vec[i] / digit) % 10]++; 
    }
    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1]; 
    }
    for (i = n - 1; i >= 0; i--) { 
        res[count[(vec[i] / digit) % 10] - 1] = vec[i]; 
        count[(vec[i] / digit) % 10]--; 
    }
    for (i = 0; i < n; i++) {
        vec[i] = res[i]; 
    }
}

void bitwiseSort(std::vector<int> &vec) {
    int max = getMax(vec);
    for (int digit = 1; max / digit > 0; digit *= 10) 
        sortByDigit(vec, digit); 
}
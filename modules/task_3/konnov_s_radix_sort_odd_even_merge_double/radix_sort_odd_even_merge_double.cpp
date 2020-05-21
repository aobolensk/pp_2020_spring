// Copyright 2020 Konnov Sergey

#define NOMINMAX
#include "../../../modules/task_3/konnov_s_radix_sort_odd_even_merge_double/radix_sort_odd_even_merge_double.h"
#include <tbb/tbb.h>
#include <tbb/task.h>
#include <tbb/task_scheduler_init.h>
#include <vector>
#include <ctime>
#include <random>
#include <iostream>
#include <utility>
#include <queue>
#include <limits>

sortTask::sortTask(double* array_tmp, int index_tmp, int size_tmp) {
    array = array_tmp;
    index = index_tmp;
    size = size_tmp;
}

tbb::task* sortTask::execute() {
    radixSortOddEvenMergeDouble(array, index, size);
    return nullptr;
}

oddEvenTask::oddEvenTask(double* array_tmp, int left_tmp, int right_tmp, int* portion_tmp) {
    array = array_tmp;
    left = left_tmp;
    right = right_tmp;
    portion = portion_tmp;
}

tbb::task* oddEvenTask::execute() {
    if (left == 0 && right == 0) {
        tbb::task::set_ref_count(2);
        tbb::task::spawn_and_wait_for_all(*(new(task::allocate_child()) sortTask(array, 0, portion[0])));
        return nullptr;
    }
    tbb::task_list list_of_tasks;
    int average = (left+right)/2+1;
    int index1 = ((left == 0)?0:portion[left-1]);
    int size1 = portion[average-1]-index1;
    int index2 = index1+size1;
    int size2 = portion[right]-portion[average-1];
    if (average-left-1 == 0) {
        list_of_tasks.push_back(*(new(task::allocate_child()) sortTask(array, index1, size1)));
    } else if (average-left-1 > 0) {
        list_of_tasks.push_back(*(new(allocate_child()) oddEvenTask(array, left, average-1, portion)));
    }
    if (right-average == 0) {
        list_of_tasks.push_back(*(new(task::allocate_child()) sortTask(array, index2, size2)));
    } else if (right-average > 0) {
        list_of_tasks.push_back(*(new(allocate_child()) oddEvenTask(array, average, right, portion)));
    }
    tbb::task::set_ref_count(3);
    tbb::task::spawn_and_wait_for_all(list_of_tasks);
    list_of_tasks.clear();
    list_of_tasks.push_back(*(new(tbb::task::allocate_child()) oddTask(array, index1, size1, index2, size2)));
    list_of_tasks.push_back(*(new(tbb::task::allocate_child()) evenTask(array, index1, size1, index2, size2)));
    tbb::task::set_ref_count(3);
    tbb::task::spawn_and_wait_for_all(list_of_tasks);
    oddEvenMerge(array, index1, size1+size2);
    return nullptr;
}


oddTask::oddTask(double * array_tmp, int index1_tmp, int size1_tmp, int index2_tmp, int size2_tmp) {
    array = array_tmp;
    index1 = index1_tmp;
    size1 = size1_tmp;
    index2 = index2_tmp;
    size2 = size2_tmp;
    num_of_depends = 2;
}

tbb::task* oddTask::execute() {
    oddMerge(array, index1, size1, index2, size2);
    return nullptr;
}

evenTask::evenTask(double * array_tmp, int index1_tmp, int size1_tmp, int index2_tmp, int size2_tmp) {
    array = array_tmp;
    index1 = index1_tmp;
    size1 = size1_tmp;
    index2 = index2_tmp;
    size2 = size2_tmp;
    num_of_depends = 2;
}

tbb::task* evenTask::execute() {
    evenMerge(array, index1, size1, index2, size2);
    return nullptr;
}

void countingSort(double* array, int size, int byteNum) {
    unsigned char* byteArray = reinterpret_cast<unsigned char*>(array);
    int counter[256] = {0};
    int offset[256] = {0};
    std::vector<double> ans(size);
    for (int i = 0; i < size; i++)
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
        for (int i = 0; i < size; i++)
            ans[offset[byteArray[8*i+byteNum]]++] = array[i];
    } else {
        for (int i = 0; i < size; i++)
            if (byteArray[8*i+byteNum] >= 128) {
                ans[offset[byteArray[8*i+byteNum]]--] = array[i];
            } else {
                ans[offset[byteArray[8*i+byteNum]]++] = array[i];
            }
    }
    for (int i = 0; i < static_cast<int>(ans.size()); i++)
        array[i] = ans[i];
}

void radixSortOddEvenMergeDouble(double* array, int index, int size) {
    for (size_t i = 0; i < 8; i++)
        countingSort(array + index, size, i);
}

void oddMerge(double* array, int index1, int size1, int index2, int size2) {
    std::vector<double>tmp;
    int ind1 = index1 + 1, ind2 = index2 + 1;
    while (ind1-index1 < size1 && ind2-index2 < size2) {
        if (array[ind1] < array[ind2]) {
            tmp.push_back(array[ind1]);
            ind1 += 2;
        } else {
            tmp.push_back(array[ind2]);
            ind2 += 2;
        }
    }
    while (ind1-index1 < size1) {
        tmp.push_back(array[ind1]);
        ind1+=2;
    }
    while (ind2-index2 < size2) {
        tmp.push_back(array[ind2]);
        ind2+=2;
    }
    int j = index1 + 1;
    for (int i = 0; i < static_cast<int>(tmp.size()); i++) {
        array[j] = tmp[i];
        j+=2;
    }
}

void evenMerge(double* array, int index1, int size1, int index2, int size2) {
    std::vector<double>tmp;
    int ind1 = index1, ind2 = index2;
    while (ind1-index1 < size1 && ind2-index2 < size2) {
        if (array[ind1] < array[ind2]) {
            tmp.push_back(array[ind1]);
            ind1 += 2;
        } else {
            tmp.push_back(array[ind2]);
            ind2 += 2;
        }
    }
    while (ind1-index1 < size1) {
        tmp.push_back(array[ind1]);
        ind1+=2;
    }
    while (ind2-index2 < size2) {
        tmp.push_back(array[ind2]);
        ind2+=2;
    }
    int j = index1;
    for (int i = 0; i < static_cast<int>(tmp.size()); i++) {
        array[j] = tmp[i];
        j+=2;
    }
}

void oddEvenMerge(double* array, int index, int size) {
    if (size == 2) {
        if (array[index] > array[index + 1])
            std::swap(array[index], array[index+1]);
        return;
    }
    for (int i = index + 1; i < index + size-1; i+=2) {
        if (array[i] > array[i+1])
            std::swap(array[i], array[i+1]);
    }
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

std::vector<double> radixSortOddEvenMergeDoubleParallel(const std::vector<double>& v, int num_threads) {
    tbb::task_scheduler_init init(num_threads);
    std::vector<double>ans = v;
    std::vector<int>portion(num_threads);
    for (int i = 0; i < num_threads; i++) {
        portion[i] = static_cast<int>(v.size())/num_threads +
                    (i < (static_cast<int>(v.size())%num_threads)?1:0) + ((i == 0)?0:portion[i-1]);
        if ((portion[i]-(i?portion[i-1]:0))%2) {
            portion[i]++;
            ans.push_back(std::numeric_limits<double>::max());
        }
    }
    tbb::task::spawn_root_and_wait(*(new(tbb::task::allocate_root())
                                        oddEvenTask(ans.data(), 0, num_threads-1, portion.data())));
    int size = static_cast<int>(ans.size());
    for (int i = v.size(); i < size; i++)
        ans.pop_back();
    return ans;
}

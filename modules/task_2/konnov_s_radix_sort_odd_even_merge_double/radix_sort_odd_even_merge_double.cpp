// Copyright 2020 Konnov Sergey

#include "../../../modules/task_2/konnov_s_radix_sort_odd_even_merge_double/radix_sort_odd_even_merge_double.h"
#include <omp.h>
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
    num_of_depends = 0;
}

void sortTask::execute() {
    // std::cout<<"BEGIN OF SORT "<<index<<" "<<size<<"\n";
    radixSortOddEvenMergeDouble(array, index, size);
    // std::cout<<"END OF SORT "<<index<<" "<<size<<"\n";
}

oddEvenTask::oddEvenTask(double* array_tmp, int index_tmp, int size_tmp) {
    array = array_tmp;
    index = index_tmp;
    size = size_tmp;
    num_of_depends = 2;
}

void oddEvenTask::execute() {
    oddEvenMerge(array, index, size);
}


oddTask::oddTask(double * array_tmp, int index1_tmp, int size1_tmp, int index2_tmp, int size2_tmp) {
    array = array_tmp;
    index1 = index1_tmp;
    size1 = size1_tmp;
    index2 = index2_tmp;
    size2 = size2_tmp;
    num_of_depends = 2;
}

void oddTask::execute() {
    oddMerge(array, index1, size1, index2, size2);
}

evenTask::evenTask(double * array_tmp, int index1_tmp, int size1_tmp, int index2_tmp, int size2_tmp) {
    array = array_tmp;
    index1 = index1_tmp;
    size1 = size1_tmp;
    index2 = index2_tmp;
    size2 = size2_tmp;
    num_of_depends = 2;
}

void evenTask::execute() {
    evenMerge(array, index1, size1, index2, size2);
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
    // for (int i = index; i < index+size-1; i++) {
    //     if (array[i] > array[i+1]) {
    //         std::cout<<"???\n"+std::to_string(index) + " " + std::to_string(size)
    // +" "+std::to_string(i) + " "+ std::to_string(array[i]) + " " +std::to_string(array[i+1])+"\n";
    //     }
    // }
}

void oddMerge(double* array, int index1, int size1, int index2, int size2) {
    // std::cout<<index1<<" "<<size1<<" "<<index2<<" "<<size2<<" hmm\n";
    // for (int i = index1; i < index1+size1; i++)
    //     std::cout<<array[i]<<" ";
    // std::cout<<"|";
    // for (int i = index2; i < index2+size2; i++)
    //     std::cout<<array[i]<<" ";
    // std::cout<<"\n";
    std::vector<double>tmp;
    int ind1 = index1 + 1, ind2 = index2 + 1;
    while (ind1-index1 < size1 && ind2-index2 < size2) {
        // std::cout<<ind1<<" "<<ind2<<" KSBVHKSFH\n";
        if (array[ind1] < array[ind2]) {
            tmp.push_back(array[ind1]);
            ind1 += 2;
        } else {
            tmp.push_back(array[ind2]);
            ind2 += 2;
        }
    }
    while (ind1-index1 < size1) {
        // std::cout<<ind1<<" "<<ind2<<" KSBVHKSFH\n";
        tmp.push_back(array[ind1]);
        ind1+=2;
    }
    while (ind2-index2 < size2) {
        // std::cout<<ind1<<" "<<ind2<<" KSBVHKSFH\n";
        tmp.push_back(array[ind2]);
        ind2+=2;
    }
    // for (auto y: tmp)
    //     std::cout<<y<<" ";
    // std::cout<<"\n";
    int j = index1 + 1;
    for (int i = 0; i < static_cast<int>(tmp.size()); i++) {
        array[j] = tmp[i];
        j+=2;
    }
    // std::cout<<"END OF ODD MERGE\n";
}


void evenMerge(double* array, int index1, int size1, int index2, int size2) {
    // std::cout<<index1<<" "<<size1<<" "<<index2<<" "<<size2<<" lel\n";
    // for (int i = index1; i < index1+size1; i++)
    //     std::cout<<array[i]<<" ";
    // std::cout<<"|";
    // for (int i = index2; i < index2+size2; i++)
    //     std::cout<<array[i]<<" ";
    // std::cout<<"\n";
    std::vector<double>tmp;
    int ind1 = index1, ind2 = index2;
    while (ind1-index1 < size1 && ind2-index2 < size2) {
        // if (ind1 < 0 || ind1 >= 8 || ind2 < 0 || ind2 >= 8) {
        //     std::cout<<"ALYARMA";
        //     throw -1;
        // }
        if (array[ind1] < array[ind2]) {
            tmp.push_back(array[ind1]);
            ind1 += 2;
        } else {
            tmp.push_back(array[ind2]);
            ind2 += 2;
        }
    }
    while (ind1-index1 < size1) {
        // if (ind1 < 0 || ind1 >= 8) {
        //     std::cout<<"ALYARMA";
        //     throw -1;
        // }
        tmp.push_back(array[ind1]);
        ind1+=2;
    }
    while (ind2-index2 < size2) {
        // if (ind2 < 0 || ind2 >= 8) {
        //     std::cout<<"ALYARMA";
        //     throw -1;
        // }
        tmp.push_back(array[ind2]);
        ind2+=2;
    }
    // for (auto y: tmp)
    //     std::cout<<y<<" ";
    // std::cout<<"\n";
    int j = index1;
    for (int i = 0; i < static_cast<int>(tmp.size()); i++) {
        // std::cout<<i<<" "<<j<<" "<<tmp[i]<<" "<<tmp.size() <<" #$%^%$#$%^%$#$%^%$#$%^%$#\n";
        // if (j < 0 || j >= 8) {

        //     std::cout<<"ALYARMA";
        //     throw -1;
        // }
        array[j] = tmp[i];
        j+=2;
    }
    // std::cout<<"END OF EVEN MERGE\n";
}

void oddEvenMerge(double* array, int index, int size) {
    if (size == 2) {
        if (array[index] > array[index + 1])
            std::swap(array[index], array[index+1]);
        return;
    }
    // std::cout<<"BEGIN OF ODD_EVEN MERGE\n";
    // for (int i = 0; i < size; i++)
    //     std::cout<<array[i+index]<<" ";
    // std::cout<<" &&&&&\n";
    for (int i = index + 1; i < index + size-1; i+=2) {
        // std::cout<<i<<" "<<array[i]<<" "<<array[i+1]<<"!!!!!!!!!!!!!!!!\n";
        if (array[i] > array[i+1])
            std::swap(array[i], array[i+1]);
    }
    // for (int i = index; i < index + size-1; i++) {
    //     if (array[i] > array[i+1]) {
    //         //std::cout<<"WOW WTF\n";
    //         std::swap(array[i], array[i+1]);
    //     }
    // }
    // std::cout<<"END OF ODD_EVEN MERGE\n";
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

void gen_tasks(double* array, int left, int right, const std::vector<task*>& tasks,
                                const std::vector<int>& portion, task* queue[], bool is_begin) {
    if (left == right) {
        int index = ((left == 0)?0:portion[left-1]);
        int size = portion[left]-((left == 0)?0:portion[left-1]);
        sortTask* stask = new sortTask(array, index, size);
        for (int i = 0; i < static_cast<int>(tasks.size()); i++)
            stask->ref.push_back(tasks[i]);
        queue[left] = stask;
    } else {
        int average = (left+right)/2+1;
        // std::cout<<left<<" "<<right<<" "<<average<<" &^%&^%$^\n";
        int index1 = ((left == 0)?0:portion[left-1]);
        int size1 = portion[average-1]-index1;
        int index2 = index1+size1;
        int size2 = portion[right]-portion[average-1];
        oddEvenTask* oetask = new oddEvenTask(array, index1, size1+size2);
        for (int i = 0; i < static_cast<int>(tasks.size()); i++)
            oetask->ref.push_back(tasks[i]);
        oddTask* otask = new oddTask(array, index1, size1, index2, size2);
        otask->ref.push_back(oetask);
        evenTask* etask = new evenTask(array, index1, size1, index2, size2);
        etask->ref.push_back(oetask);
        std::vector<task*> new_tasks;
        new_tasks.push_back(otask);
        new_tasks.push_back(etask);
        gen_tasks(array, left, average-1, new_tasks, portion, queue);
        gen_tasks(array, average, right, new_tasks, portion, queue);
    }
}

std::vector<double> radixSortOddEvenMergeDoubleParallel(const std::vector<double>& v) {
    int num_threads;
    #pragma omp parallel
    {
        #pragma omp single
        {
            num_threads = omp_get_num_threads();
        }
    }
    std::vector<task*>tmp_queue(num_threads);
    std::vector<double>ans = v;
    std::vector<task*> tasks;
    std::vector<int>portion(num_threads);
    for (int i = 0; i < num_threads; i++) {
        portion[i] = static_cast<int>(v.size())/num_threads +
                    (i < (static_cast<int>(v.size())%num_threads)?1:0) + ((i == 0)?0:portion[i-1]);
        if ((portion[i]-(i?portion[i-1]:0))%2) {
            portion[i]++;
            ans.push_back(std::numeric_limits<double>::max());
        }
    }
    // std::cout<<"\n";
    gen_tasks(ans.data(), 0, num_threads-1, tasks, portion, tmp_queue.data(), 1);
    std::queue<task*> task_queue;
    for (int i = 0; i < static_cast<int>(tmp_queue.size()); i++)
        task_queue.push(tmp_queue[i]);
    omp_lock_t lock;
    omp_init_lock(&lock);
    bool end = 0;
    #pragma omp parallel
    {
        while (true) {
            omp_set_lock(&lock);
            if (end) {
                omp_unset_lock(&lock);
                break;
            }
            if (!task_queue.size()) {
                omp_unset_lock(&lock);
                continue;
            }
            task* task1;
            task1 = task_queue.front();
            // std::cout<<omp_get_thread_num()<<" "<<task->ref.size()<<"\n";
            task_queue.pop();
            if (task1->ref.size() == 0)
                end = 1;
            // task1->print();
            // std::cout<<task1->ref.size()<<"\n";
            // std::cout<<" "<<omp_get_thread_num()<<" "<<omp_get_num_threads()<<"\n";
            omp_unset_lock(&lock);
            task1->execute();
            omp_set_lock(&lock);
            // std::cout<<omp_get_thread_num()<<" "<<task->num_of_depends<<"!!!!!\n";
            for (int i = 0; i < static_cast<int>(task1->ref.size()); i++) {
                task1->ref[i]->num_of_depends--;
                if (task1->ref[i]->num_of_depends <= 0)
                    task_queue.push(task1->ref[i]);
            }
            delete task1;
            omp_unset_lock(&lock);
        }
    }
    // std::cout<<" i t  i s  e n d \n";
    // for (auto y: ans) {
    //     std::cout<<y<<" ";
    // }
    // std::cout<<" <-\n";
    int size = static_cast<int>(ans.size());
    for (int i = v.size(); i < size; i++)
        ans.pop_back();
    // ans.resize(v.size());
    return ans;
}

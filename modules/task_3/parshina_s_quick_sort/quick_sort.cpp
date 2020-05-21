// Copyright 2020 Parshina Sophie
#include "../../../modules/task_3/parshina_s_quick_sort/quick_sort.h"
#include <tbb/tbb.h>
#include <tbb/task_group.h>
#include <tbb/task.h>
#include <utility>
#include <vector>
#include <ctime>
#include <random>
#include <cmath>
#include <iostream>

// The main class of quick sort task
class qHoareSortTask : public tbb::task {
 private:
  double* arr;
  int left_index, right_index;

 public:
  qHoareSortTask(double* arr1, int left_index1, int right_index1) :
    arr(arr1), left_index(left_index1), right_index(right_index1) {}
  task* execute() {
    int min_parallel_length = 50;
    if (right_index - left_index <= min_parallel_length) {
      qHoareSort(arr, left_index, right_index);
    } else {
      int left = left_index;
      int right = right_index;
      int pi = arr[(left + right) / 2];

      while (left <= right) {
        if (pi > arr[left]) {
          left++;
        } else {
          if (arr[right] > pi) {
            right--;
          } else {
            std::swap(arr[left], arr[right]);
            right--;
            left++;
          }
        }
      }

      tbb::task_list tasks_list;
      tasks_list.push_back(*new(tbb::task::allocate_child()) qHoareSortTask(arr, left, right_index));
      tasks_list.push_back(*new(tbb::task::allocate_child()) qHoareSortTask(arr, left_index, right));

      if (left_index < right && right_index > left) {
        set_ref_count(3);
        task::spawn_and_wait_for_all(tasks_list);
      } else {
        set_ref_count(2);
        if (left_index < right) {
          task::spawn_and_wait_for_all(*new(tbb::task::allocate_child()) qHoareSortTask(arr, left_index, right));
        } else {
          task::spawn_and_wait_for_all(*new(tbb::task::allocate_child()) qHoareSortTask(arr, left, right_index));
        }
      }
    }
    return NULL;
  }
};

// The main method that creates the root task of the entire quick Hoare sort
void qHoareSortTbb(double* arr, int n) {
  qHoareSortTask& HoareSort = *new(tbb::task::allocate_root()) qHoareSortTask(arr, 0, n - 1);
  tbb::task::spawn_root_and_wait(HoareSort);
}

// Random Array Generation
void Get_Random_Array(double* arr, int size) {
  std::mt19937 generator(time(0));
  std::uniform_int_distribution<> dist(-100000, 1000000);
  for (int i = 0; i <= size; i++) {
    arr[i] = dist(generator);
  }
}

// Hoare Separation of the array relative to a pivot element and returning its index
int HoarePartition(double* arr, int left_index, int right_index) {
  double pivot = arr[(right_index + left_index) / 2];
  int i = left_index - 1, j = right_index + 1;

  while (true) {
    do {
      i++;
    } while (arr[i] < pivot);

    do {
      j--;
    } while (arr[j] > pivot);

    if (i >= j)
      return j;

    std::swap(arr[i], arr[j]);
  }
}

// Sequential Quick Sort with Hoare separation of the array
void qHoareSort(double* arr, int left_index, int right_index) {
  if (left_index < right_index) {
    int pi = HoarePartition(arr, left_index, right_index);
    qHoareSort(arr, left_index, pi);
    qHoareSort(arr, pi + 1, right_index);
  }
}

// Is the array sorted or not
int IsSorted(double* arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    if (arr[i] > arr[i + 1]) {
      return 0;
    }
  }
  return 1;
}

// Copy elements from array to another one
void Copy_elements(double*a1, double* a2, int n) {
  for (int i = 0; i < n; i++) {
    a2[i] = a1[i];
  }
}

/* Correct, but slow method
void qHoareSortTbb(double* arr, int left_index, int right_index) {
  int min_parallel_length = 3;
  if (right_index - left_index > min_parallel_length) {
    int pi = HoarePartition(arr, left_index, right_index);
    tbb::parallel_invoke([=] {qHoareSortTbb(arr, left_index, pi); },
                         [=] {qHoareSortTbb(arr, pi + 1, right_index); });
  }
  else {
    qHoareSort(arr, left_index, right_index);
  }
}*/

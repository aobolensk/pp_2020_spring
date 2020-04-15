// Copyright 2020 Parshina Sophie
#include <ctime>
#include <utility>
#include <random>
#include "../../../modules/task_1/parshina_s_quick_sort/quick_sort.h"

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

// Quick Sort with Hoare separation of the array
void qHoareSort(double* arr, int left_index, int right_index) {
  if (left_index < right_index) {
    int pi = HoarePartition(arr, left_index, right_index);
    qHoareSort(arr, left_index, pi);
    qHoareSort(arr, pi + 1, right_index);
  }
}

// Is the array sorted or not
int IsSorted(double* arr, int n) {
  for (int i = 0; i < n-1; i++) {
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

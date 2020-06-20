// Copyright 2020 Parshina Sophie
#include <thread>
#include <utility>
#include <random>
#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>
#include "../../../modules/task_4/parshina_s_quick_sort/quick_sort.h"

using namespace std;

void Get_Random_Array(double* arr, int size) {
  std::mt19937 generator(time(0));
  std::uniform_int_distribution<> dist(-100000, 1000000);
  for (int i = 0; i <= size; i++) {
    arr[i] = dist(generator);
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

void Move_Array_To_Dest(double* first, double* last, double* res) {
  while (first != last + 1) {
    (*res) = (*first);
    ++first;
    ++res;
  }
}

void qHoareSort(double* arr, int first, int last) {
  int i = first, j = last;
  int temp, mid = arr[(first + last) / 2];

  do {
    while (arr[i] < mid)
      i++;
    while (arr[j] > mid)
      j--;

    if (i <= j) {
      if (i < j) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
      i++;
      j--;
    }

  } while (i <= j);


  if (i < last)
    qHoareSort(arr, i, last);
  if (first < j)
    qHoareSort(arr, first, j);
}


void Merge(double* arr1_begin, double* arr1_end, double* arr2_begin, double* arr2_end, double* dest) {
  while ((arr1_begin <= arr1_end) && (arr2_begin <= arr2_end)) {
    auto elem1 = *arr1_begin;
    auto elem2 = *arr2_begin;

    if (elem1 < elem2) {
      *dest = elem1;
      ++arr1_begin;
    }
    else {
      *dest = elem2;
      ++arr2_begin;
    }
    ++dest;
  }
  if (arr1_begin > arr1_end) {
    Move_Array_To_Dest(arr2_begin, arr2_end + 1, dest);
  }
  else {
    Move_Array_To_Dest(arr1_begin, arr1_end + 1, dest);
  }
}

void qHoareSortThreads(double* a, int n, int threads_count)
{
  double* sorted_a = new double[n];
  int chunk_size = n / threads_count ? n / threads_count : 1;

  vector<thread> threads;

  for (int i = 0; i < threads_count; ++i) {
    auto first = i * chunk_size;
    auto last = first + chunk_size - 1;
    threads.push_back(std::thread(qHoareSort, a, first, last));
  }

  for (int i = 0; i < threads_count; ++i) {
    threads.at(i).join();
  }

  auto remainder = n % threads_count;
  if (remainder) {
    qHoareSort(a, threads_count * chunk_size, n - 1);
  }

  int array_size = chunk_size;
  int count = array_size << 1;
  int j = 0;
  while (array_size < n) {
    for (j = 0; j <= n - count; j += count) {
      double* first_array_start = a + j;
      double* first_array_end = first_array_start + array_size - 1;

      double* second_array_start = a + j + array_size;
      double* second_array_end = second_array_start + array_size - 1;

      Merge(first_array_start, first_array_end, second_array_start, second_array_end, sorted_a + j);
    }

    Move_Array_To_Dest(sorted_a, sorted_a + j, a);

    array_size = (array_size << 1) > n ? n : array_size << 1;
    count = array_size << 1;
  }

  if (remainder) {
    int array_size = n - remainder;
    double* first_array_start = a;
    double* first_array_end = first_array_start + array_size - 1;

    double* second_array_start = a + array_size;
    double* second_array_end = second_array_start + remainder - 1;

    Merge(first_array_start, first_array_end, second_array_start, second_array_end, sorted_a);
  }

  Move_Array_To_Dest(sorted_a, sorted_a + n, a);
}
// Copyright 2020 Parshina Sophie
#include <omp.h>
#include <utility>
#include <random>
#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>
#include "../../../modules/task_2/parshina_s_quick_sort/quick_sort.h"


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

/*double t()
{
  return omp_get_wtime();
}

// Variables for qsort, merge and summary time 
double qsort_time;
double fusion_time;
double summary_time;*/

// Merge two already sorted arrays into one large sorted array
void Simple_Fusion(double * arr, int n, int m) {
  double * result = new double[n + m];
  double * a = arr;
  double * b = arr + n;

  int a_index = 0, b_index = 0, result_index = 0;
  while ((a_index < n) && (b_index < m)) {
    if (a[a_index] < b[b_index]) {
      result[result_index] = a[a_index];
      ++result_index;
      ++a_index;
    } else {
      result[result_index] = b[b_index];
      ++result_index;
      ++b_index;
    }
  }

  double * tmp;
  int tmp_index, tmp_max;
  if (a_index == n) {
    tmp = b;
    tmp_index = b_index;
    tmp_max = m;
  } else {
    tmp = a;
    tmp_index = a_index;
    tmp_max = n;
  }
  int delta = result_index - tmp_index;

  for (; tmp_index < tmp_max; ++tmp_index)
    result[tmp_index + delta] = tmp[tmp_index];

  for (int i = 0; i < n + m; ++i)
    arr[i] = result[i];
}

// Split array into subarrays based on the number of threads and get the ends of these segments
std::vector<int> Get_Ends(int thread_num, int n, int threads_value) {
  int sub_length = round(1.0 * n / threads_value);
  if (thread_num < threads_value - 1) {
    std::vector<int> ends(2);
    ends[0] = thread_num * sub_length;
    ends[1] = ends[0] + sub_length - 1;
    return ends;
  } else {
    std::vector<int> ends(2);
    ends[0] = thread_num * sub_length;
    ends[1] = n - 1;
    return ends;
  }
}

/* Cout ends with their threads
void dump_thread(vector<vector<int>> x)
{
  static int dump_num = 0;
#pragma omp critical
  {
    ++dump_num;
    cout << "\n\n-----------" << '\n';
    cout << "num " << dump_num << '\n';
    cout << "thread " << omp_get_thread_num() << '\n'
      << "edge 1: " << x[0][0] << ' ' << x[0][1] << '\n'
      << "edge 2: " << x[1][0] << ' ' << x[1][1] << '\n';
    cout << "-----------" << "\n\n\n";
  }
}

void dump_ends(vector<vector<int>> x, int l)
{
  cout << "\n\n-----------" << '\n';
  for (int i = 0; i < l; ++i)
  {
    for (auto b : x[i])
      cout << ' ' << b;
    cout << endl;
  }
  cout << "-----------" << "\n\n\n";
}*/

// OMP quick sort with parallel division
void Parallel_Division_Sort(double * arr, int n, int threads_value) {
  // double wt, qt, ft;
  // wt = qt = ft = 0;
  // wt = t();

  omp_set_num_threads(threads_value);
  // int sub_length = round(1.0 * n / threads_value);
  std::vector<std::vector<int>> splitted_ends(threads_value);
  for (int i = 0; i < threads_value; ++i)
    splitted_ends[i] = Get_Ends(i, n, threads_value);
  // qt = t();
#pragma omp parallel
  {
    int thread_num = omp_get_thread_num();
    qHoareSort(arr, splitted_ends[thread_num][0], splitted_ends[thread_num][1]);
#pragma omp barrier
  }
  // qt = t() - qt;
  // ft = t();
  int length = splitted_ends.size();
  while (length > 1) {
    omp_set_num_threads(length / 2);
#pragma omp parallel
    {
      int thread_num = omp_get_thread_num();
      std::vector<std::vector<int>> individual_thread_arr(2);
      int first_sub_section = thread_num * 2 + (length % 2);
      int second_sub_section = first_sub_section + 1;
      individual_thread_arr[0] = splitted_ends[first_sub_section];
      individual_thread_arr[1] = splitted_ends[second_sub_section];
      int delta = individual_thread_arr[0][0],
        n = individual_thread_arr[0][1] - individual_thread_arr[0][0] + 1,
        m = individual_thread_arr[1][1] - individual_thread_arr[1][0] + 1;
      Simple_Fusion(arr + delta, n, m);
#pragma omp barrier
      individual_thread_arr[0][1] = individual_thread_arr[1][1];
      int insert_pos = (thread_num + 1) - !(length % 2);
      splitted_ends[insert_pos] = individual_thread_arr[0];
#pragma omp barrier
    }
    length = (length + 1) / 2;
  }
  /*ft = t() - ft;
  wt = t() - wt;
  summary_time += wt;
  qsort_time += qt;
  fusion_time += ft;*/
}

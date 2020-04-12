// Copyright 2020 Guschin Alexander
#include "../../../modules/task_1/guschin_a_cc_labeling/cc_labeling.h"
#include <omp.h>
#include <iostream>
#include <vector>

void Print(const std::vector<std::vector<std::int32_t>>& A);
void Merge_omp(std::vector<std::vector<std::int32_t>>* ptr,
               std::int32_t str_row,
               std::int32_t pr_num, std::int32_t req_num, std::int32_t end_x,
               std::int32_t end_y);

std::vector<std::vector<std::int32_t>> Labeling_omp(
    const std::vector<std::vector<std::int8_t>>& pic) {
  std::vector<std::vector<std::int32_t>> res(
      pic.size(), std::vector<int>(pic[0].size(), 0));

  std::int32_t w = pic.size();
  std::int32_t h = pic[0].size();
  std::int32_t comp_counter = 1;
  std::int32_t thread_count = 0;
  //omp_set_num_threads(2);
#pragma omp parallel
  {
    std::int32_t thread_id = omp_get_thread_num();
    thread_count = omp_get_num_threads();
#pragma omp critical
    std::cout << "thread_count: " << thread_count << std::endl;

    std::int32_t first_row;
    if (thread_count >= h)
      first_row = thread_id;
    else
      first_row = (thread_id == 0
                       ? 0
                       : h / thread_count + h % thread_count);
    #pragma omp for
    for (std::int32_t i = 0; i < w; ++i) {
      /*#pragma omp critical
      std::cout << "number: " << thread_id << " index: " << i << std::endl;*/
      for (std::int32_t j = 0; j < h; ++j) {
        std::int32_t up_value = 0;
        std::int32_t left_value = 0;
        std::int32_t sel_v = 0;

        if (i > 0 && i != first_row) up_value = pic[i - 1][j];
        if (j > 0) left_value = pic[i][j - 1];
        sel_v = pic[i][j];

        if (sel_v == 0) {
          continue;
        } else if (up_value == 1 && left_value == 1) {
          if (res[i - 1][j] == res[i][j - 1]) {
            res[i][j] = res[i - 1][j];
          } else {
            std::int32_t min =
                (res[i - 1][j] < res[i][j - 1] ? res[i - 1][j] : res[i][j - 1]);
            std::int32_t max =
                (res[i - 1][j] > res[i][j - 1] ? res[i - 1][j] : res[i][j - 1]);
            Merge_omp(&res, first_row, max, min, i, j);
            res[i][j] = min;
          }
        } else if (up_value == 1 && left_value == 0) {
          res[i][j] = res[i - 1][j];
        } else if (up_value == 0 && left_value == 1) {
          res[i][j] = res[i][j - 1];
        } else if (up_value == 0 && left_value == 0) {
#pragma omp critical (counter)
          {
            res[i][j] = comp_counter;
            comp_counter++;
          }
        }
      }
    }
  }
  std::int32_t str_ind = 1;
  std::int32_t shift = 1;
  if (thread_count <= h) {
    str_ind = h % thread_count;
    shift = h / thread_count;
  }
    
  
  //for (std::int32_t i = str_ind; i < h; i += shift)
  //  for (std::int32_t j = 0; j < w; ++j)
  //    if ()
  Print(res);
  std::cout << "num " << thread_count;
  return res;
}

void Merge_omp(std::vector<std::vector<std::int32_t>>* ptr,
               std::int32_t str_row, std::int32_t pr_num, std::int32_t req_num,
               std::int32_t end_x, std::int32_t end_y) {
  std::int32_t w = (*ptr).size();
  std::int32_t h = (*ptr)[0].size();
  for (std::int32_t i = 0; i < w; ++i)
    for (std::int32_t j = str_row; j < h; ++j) {
      if ((*ptr)[i][j] == pr_num) (*ptr)[i][j] = req_num;
      if (i == end_x && j == end_y) return;
    }
}

void Print(const std::vector<std::vector<std::int32_t>>& A) {
  std::int32_t h = A.size();
  std::int32_t w = A[0].size();
  for (std::int32_t i = 0; i < h; ++i) {
    for (std::int32_t j = 0; j < w; ++j) std::cout << A[i][j] << " ";
    std::cout << std::endl;
  }
}

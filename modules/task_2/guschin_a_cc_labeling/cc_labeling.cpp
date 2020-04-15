// Copyright 2020 Guschin Alexander
#include "../../../modules/task_2/guschin_a_cc_labeling/cc_labeling.h"
#include <omp.h>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

std::vector<std::vector<std::int32_t>> Labeling_omp(
    const std::vector<std::vector<std::int8_t>>& pic) {
  std::vector<std::vector<std::int32_t>> res(
      pic.size(), std::vector<int>(pic[0].size(), 0));

  std::vector<std::int32_t> sec_start;
  std::int32_t h = pic.size();
  std::int32_t w = pic[0].size();
  std::int32_t comp_counter = 1;
  std::int32_t thread_count = 0;
  omp_set_num_threads(4);
#pragma omp parallel
  {
    std::int32_t thread_id = omp_get_thread_num();
    thread_count = omp_get_num_threads();
    std::int32_t first_row;
    bool lock = true;

#pragma omp for schedule(static)
    for (std::int32_t i = 0; i < h; ++i) {
      for (std::int32_t j = 0; j < w; ++j) {
        std::int32_t up_value = 0;
        std::int32_t left_value = 0;
        std::int32_t sel_v = 0;

        if (lock == false) up_value = pic[i - 1][j];
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
            /*#pragma omp critical(print)
            std::cout << "i = " << i << " j = " << j << std::endl;*/
            Merge_omp(&res, first_row, max, min, i, j);
            res[i][j] = min;
          }
        } else if (up_value == 1 && left_value == 0) {
          res[i][j] = res[i - 1][j];
        } else if (up_value == 0 && left_value == 1) {
          res[i][j] = res[i][j - 1];
        } else if (up_value == 0 && left_value == 0) {
#pragma omp critical(counter)
          {
            res[i][j] = comp_counter;
            comp_counter++;
          }
        }
      }

      if (lock == true) {
        lock = false;
        first_row = i;
#pragma omp critical(push)
        std::cout << "start " << first_row << std::endl;
      }

#pragma omp critical(print)
      std::cout << "id = " << thread_id << " i = " << i << std::endl;
    }
  }
  Print(res);

  std::int32_t i = h / thread_count;
  std::int32_t ost = h % thread_count;
  while (i < h) {
    if (ost > 0) {
      ++i;
      --ost;
    }
    for (std::int32_t j = 0; j < w; ++j) {
      if (res[i][j] == 0 || res[i - 1][j] == 0 || res[i][j] == res[i - 1][j]) {
        continue;
      } else {
        Merge_omp(&res, 0, res[i - 1][j], res[i][j], i, j);
      }
    }
    i += h / thread_count;
  }
  Print(res);
  std::cout << "num " << thread_count;
  return res;
}

void Merge_omp(std::vector<std::vector<std::int32_t>>* ptr,
               std::int32_t str_row, std::int32_t pr_num, std::int32_t req_num,
               std::int32_t end_x, std::int32_t end_y) {
  std::int32_t h = (*ptr).size();
  std::int32_t w = (*ptr)[0].size();
  for (std::int32_t i = str_row; i < h; ++i)
    for (std::int32_t j = 0; j < w; ++j) {
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
  std::cout << std::endl;
}

void Fill_random(std::vector<std::vector<std::int8_t>>* ptr) {
  std::int32_t h = ptr->size();
  std::int32_t w = (*ptr)[0].size();
  std::mt19937 gen(time(0));
  for (std::int32_t i = 0; i < h; ++i) {
    for (std::int32_t j = 0; j < w; ++j)
      if (gen() % 2 == 0)
        (*ptr)[i][j] = 1;
      else
        (*ptr)[i][j] = 0;
  }
}

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
#pragma omp parallel
  {
    thread_count = omp_get_num_threads();
    std::int32_t first_row = -1;
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
      }
    }
  }

  std::int32_t i = h / thread_count;
  std::int32_t ost = h % thread_count;
  if (ost > 0) {
    ++i;
    --ost;
  }
  while (i < h) {
    for (std::int32_t j = 0; j < w; ++j) {
      if (res[i][j] == 0 || res[i - 1][j] == 0 || res[i][j] == res[i - 1][j]) {
        continue;
      } else {
        std::int32_t shift = h / thread_count;
        if (ost > 0) shift += 1;
        Merge_omp(&res, 0, res[i - 1][j], res[i][j], i + shift, 0);
      }
    }
    i += h / thread_count;
    if (ost > 0) {
      ++i;
      --ost;
    }
  }
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

bool IsLabeled(const std::vector<std::vector<std::int32_t>>& A) {
  std::int32_t h = A.size();
  std::int32_t w = A[0].size();
  for (std::int32_t i = 0; i < h; ++i) {
    for (std::int32_t j = 0; j < w; ++j) {
      std::int32_t sel_value = A[i][j];
      if (sel_value == 0) continue;

      std::int32_t right_value = 0;
      std::int32_t down_value = 0;

      if (i < h - 1) down_value = A[i + 1][j];
      if (j < w - 1) right_value = A[i][j + 1];

      if (down_value != 0 && down_value != sel_value) return false;
      if (right_value != 0 && right_value != sel_value) return false;
    }
  }
  return true;
}

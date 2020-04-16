// Copyright 2020 Guschin Alexander
#include "../../../modules/task_1/guschin_a_cc_labeling/cc_labeling.h"
#include <vector>

std::vector<std::vector<int>> Labeling(
    const std::vector<std::vector<std::int8_t>>& pic) {
  std::vector<std::vector<int>> res(pic.size(),
                                    std::vector<int>(pic[0].size(), 0));
  int w = pic.size();
  int h = pic[0].size();
  int comp_counter = 1;

  for (int i = 0; i < w; ++i)
    for (int j = 0; j < h; ++j) {
      int left_v = 0;
      int up_v = 0;
      int sel_v = 0;

      if (i > 0) left_v = pic[i - 1][j];
      if (j > 0) up_v = pic[i][j - 1];
      sel_v = pic[i][j];

      if (sel_v == 0) {
        continue;
      } else if (left_v == 1 && up_v == 1) {
        if (res[i - 1][j] == res[i][j - 1]) {
          res[i][j] = res[i - 1][j];
        } else {
          int min =
              (res[i - 1][j] < res[i][j - 1] ? res[i - 1][j] : res[i][j - 1]);
          int max =
              (res[i - 1][j] > res[i][j - 1] ? res[i - 1][j] : res[i][j - 1]);
          Merge(&res, max, min, i, j);
          res[i][j] = min;
        }
      } else if (left_v == 1 && up_v == 0) {
        res[i][j] = res[i - 1][j];
      } else if (left_v == 0 && up_v == 1) {
        res[i][j] = res[i][j - 1];
      } else if (left_v == 0 && up_v == 0) {
        res[i][j] = comp_counter;
        comp_counter++;
      }
    }
  return res;
}

void Merge(std::vector<std::vector<int>>* ptr, int pr_num, int req_num,
           int end_x, int end_y) {
  int w = (*ptr).size();
  int h = (*ptr)[0].size();
  for (int i = 0; i < w; ++i)
    for (int j = 0; j < h; ++j) {
      if ((*ptr)[i][j] == pr_num) (*ptr)[i][j] = req_num;
      if (i == end_x && j == end_y) return;
    }
}

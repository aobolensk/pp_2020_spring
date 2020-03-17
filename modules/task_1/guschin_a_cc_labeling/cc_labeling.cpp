// Copyright 2020 Guschin Alexander
#include <vector>
#include "../../../modules/task_1/guschin_a_cc_labeling/cc_labeling.h"

std::vector<std::vector<int>> Labeling(const std::vector<std::vector<int>>& pic) {
  std::vector<std::vector<int>> res(pic.size(),
                                    std::vector<int>(pic[0].size(), 0));
  int comp_counter = 1;
  for (int i = 0; i < pic.size(); ++i)
    for (int j = 0; j < pic[0].size(); ++j) {
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
          Merge(&res, res[i - 1][j], res[i][j - 1], i, j);
          res[i][j] = res[i - 1][j];
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
  for (int i = 0; i < (*ptr).size(); ++i)
    for (int j = 0; j < (*ptr)[0].size(); ++j) {
      if ((*ptr)[i][j] == pr_num) (*ptr)[i][j] = req_num;
      if (i == end_x && j == end_y) return;
    }
}


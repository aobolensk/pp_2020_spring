// Copyright 2020 Kukushkina Ksenia

#ifndef MODULES_TASK_3_KUKUSHKINA_K_SEGMENTATION_TBB_BIN_IMAGE_SEGMENTATION_H_
#define MODULES_TASK_3_KUKUSHKINA_K_SEGMENTATION_TBB_BIN_IMAGE_SEGMENTATION_H_

#include <tbb/tbb.h>
#include <vector>
#include <atomic>

static tbb::spin_mutex mut_new_seg;
static tbb::spin_mutex mut_recolor;

class Segmentation {
  int* color;
  tbb::atomic<int>* workingThreads;
  std::vector<int>* newColor;
  const std::vector<int>& source;
  std::vector<int>* result;
  std::size_t w;
  std::size_t h;
 public:
  Segmentation(const std::vector<int>& tsource, std::vector<int>* tresult,
    std::size_t tw, std::size_t th, int* tcolor, tbb::atomic<int>* twt,
    std::vector<int>* tnc) : source(tsource), color(tcolor),
    w(tw), h(th), result(tresult), workingThreads(twt), newColor(tnc) {}

  void operator() (const tbb::blocked_range<int>& r) const;
};

std::vector<int> Generate_pic(std::size_t w, std::size_t h);
void Output(const std::vector<int>& source, std::size_t w);

static std::vector<int> Process(const std::vector<int>& source, std::size_t w, std::size_t h) {
  std::vector<int> res(source);
  std::vector<int> tnc;
  int color = 0;
  tbb::atomic<int> wt = 0;
  Segmentation pic(source, &res, w, h, &color, &wt, &tnc);
  parallel_for(tbb::blocked_range<int>(0, source.size(), w), pic);
  return res;
}

#endif  // MODULES_TASK_3_KUKUSHKINA_K_SEGMENTATION_TBB_BIN_IMAGE_SEGMENTATION_H_

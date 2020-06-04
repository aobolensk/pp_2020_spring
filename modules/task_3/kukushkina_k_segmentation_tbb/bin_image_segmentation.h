// Copyright 2020 Kukushkina Ksenia

#ifndef MODULES_TASK_3_KUKUSHKINA_K_SEGMENTATION_TBB_BIN_IMAGE_SEGMENTATION_H_
#define MODULES_TASK_3_KUKUSHKINA_K_SEGMENTATION_TBB_BIN_IMAGE_SEGMENTATION_H_

#include <tbb/tbb.h>
#include <vector>
#include <atomic>
#include <numeric>

static tbb::spin_mutex mut_new_seg;
static tbb::spin_mutex mut_recolor;

class Segmentation {
  std::vector<std::size_t>* result;
  std::size_t w;
  std::size_t* color;
 public:
  Segmentation(std::vector<std::size_t>* tresult,
    std::size_t tw, std::size_t th, std::size_t* tcolor) :
    result(tresult), w(tw), color(tcolor) {}

  void operator() (const tbb::blocked_range<std::size_t>& r) const;
};

class Recolor {
  std::vector<std::size_t>* result;
  std::size_t w;
  const std::vector<std::size_t>& newColor;
 public:
  Recolor(std::vector<std::size_t>* tresult, std::size_t tw,
    const std::vector<std::size_t>& tnc) :
    result(tresult), w(tw), newColor(tnc) {}

  void operator() (const tbb::blocked_range<std::size_t>& r) const;
};

std::vector<std::size_t> Generate_pic(std::size_t w, std::size_t h);
void Output(const std::vector<std::size_t>& source, std::size_t w);

std::vector<std::size_t> Process(const std::vector<std::size_t>& source, std::size_t w, std::size_t h);

#endif  // MODULES_TASK_3_KUKUSHKINA_K_SEGMENTATION_TBB_BIN_IMAGE_SEGMENTATION_H_

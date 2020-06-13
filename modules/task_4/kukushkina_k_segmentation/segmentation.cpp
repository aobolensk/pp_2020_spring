// Copyright 2020 Kukushkina Ksenia
#include "../../modules/task_4/kukushkina_k_segmentation/segmentation.h"
#include <vector>
#include <random>
#include <ctime>
#include <thread>
#include <mutex>

static unsigned int offset = 0;
std::mutex m1;

std::vector<std::size_t> Generate_pic(std::size_t w, std::size_t h) {
  if (h <= 0 || w <= 0) throw "Trying to generate negative-dim pic";
  std::vector<std::size_t> pic(h * w);
  std::mt19937 gen;
  gen.seed(static_cast<unsigned int>(time(0)) + offset++);
  for (std::size_t i = 0; i < h * w; i++) {
    pic[i] = gen() % 2;
  }
  return pic;
}

void Seg(std::size_t w, std::size_t start, std::size_t finish, std::vector<std::size_t>& res, std::vector<std::size_t>& tnc, std::size_t& color) {
  if (res[start] == 1) {  // first elem
    m1.lock();
    color++;
    res[start] = color;
    tnc.push_back(color);
    m1.unlock();
  }
  for (std::size_t i = start + 1; i < start + w; i++) {  // first row
    if (res[i] == 0)  // empty cell
      continue;
    if (res[i - 1] == 0 || i % w == 0) {  // new seg
      m1.lock();
      color++;
      res[i] = color;
      tnc.push_back(color);
      m1.unlock();
      continue;
    }
    res[i] = res[i - 1];
  }
  for (std::size_t i = start + w; i < finish; i++) {  // other rows
    if (res[i] == 0)  // empty cell
      continue;
    if ((res[i - 1] < 2 || i % w == 0) && res[i - w] < 2) {  // new seg
      m1.lock();
      color++;
      res[i] = color;
      tnc.push_back(color);
      m1.unlock();
      continue;
    }
    if (res[i - 1] < 2) {  // only upper is colored
      res[i] = res[i - w];
      continue;
    }
    if (res[i - w] < 2) {  // only left is colored
      res[i] = res[i - 1];
      continue;
    }
    // both upper & left are colored
    std::size_t leftcolor = res[i - 1];
    res[i] = leftcolor;
  }
}

void Recolor(std::size_t start, std::size_t finish, std::vector<std::size_t>& res, std::vector<std::size_t>& tnc) {
  for (size_t j = start; j < finish; j++)
    res[j] = tnc[res[j]];
}

std::vector<std::size_t> Segmentation(const std::vector<std::size_t>& source, std::size_t w) {
  std::vector<std::size_t> res(source);
  std::vector<std::size_t> tnc, tnc1;
  tnc.push_back(0);
  tnc.push_back(1);
  std::size_t color = 1;

  std::size_t N = 1;
  std::vector<std::thread> t;

  std::size_t len = (source.size() / w) / (N + 1) * w;

  for (size_t i = 0; i < N; i++) {
    t.push_back(std::thread(Seg, w, i * len, i * len + len, std::ref(res), std::ref(tnc), std::ref(color)));
  }

  Seg(w, len * N, res.size(), std::ref(res), std::ref(tnc), std::ref(color));

  for (size_t i = 0; i < N; i++) {
    t[i].join();
  }

  // Recoloring preprocessing
  for (std::size_t i = w; i < res.size(); i++) {
    if (res[i] == 0 || res[i - w] == 0)
      continue;
    std::size_t cur = tnc[res[i]];
    std::size_t up = tnc[res[i - w]];
    for (std::size_t j = 2; j < tnc.size(); j++) {
      if (tnc[j] == cur)
        tnc[j] = up;
    }
  }

  // Recoloring
  for (size_t i = 0; i < N; i++) {
    t[i] = std::thread(Recolor, len * i, len * i + len, std::ref(res), std::ref(tnc));
  }

  Recolor(len * N, res.size(), std::ref(res), std::ref(tnc));

  for (size_t i = 0; i < N; i++)
    t[i].join();

  return res;
}

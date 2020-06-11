// Copyright 2020 Golovanova Elena
#include <iostream>
#include <vector>
#include <ctime>
#include "../../../modules/task_3/golovanova_e_sobel/sobel.h"
#include "gtest/gtest.h"

TEST(sobel, get_matrix) {
  std::vector<int> example = { 1, 5, 4, 3 };
  image Example(2, 2, example);
  ASSERT_EQ(example, Example.GetMatrix());
}

TEST(sobel, uncorrect_width) {
  std::vector<int> example = { 1, 5, 4, 3 };
  ASSERT_ANY_THROW(image Example(0, 2, example));
}

TEST(sobel, uncorrect_height) {
  std::vector<int> example = { 1, 5, 4, 3 };
  ASSERT_ANY_THROW(image Example(2, 0, example));
}

TEST(sobel, uncorrect_sizes) {
  std::vector<int> example = { 1, 5, 4, 3 };
  ASSERT_ANY_THROW(image Example(0, 0, example));
}

TEST(sobel, uncorrect_width_in_random) {
  ASSERT_ANY_THROW(image Example(0, 1));
}

TEST(sobel, uncorrect_height_in_random) {
  ASSERT_ANY_THROW(image Example(1, 0));
}

TEST(sobel, uncorrect_sizes_in_random) {
  ASSERT_ANY_THROW(image Example(0, 0));
}

TEST(sobel, seq_sobel) {
  std::vector<int> example = { 1, 0, 2, 1, 0, 2, 1, 0, 2 };
  std::vector<int> result = { 4 };
  image Example(3, 3, example);
  image res = Example.SeqSobel();
  ASSERT_EQ(result, res.GetMatrix());
}

TEST(sobel, tbb_sobel) {
  std::vector<int> example = { 1, 0, 2, 1, 0, 2, 1, 0, 2 };
  std::vector<int> result = { 4 };
  image Example(3, 3, example);
  image res = Example.TbbSobel();
  ASSERT_EQ(result, res.GetMatrix());
}

//  TEST(sobel, many_number_of_elements) {
//  image Ex(10000, 10000);
//  Ex.GetRandom();
//  double start = clock();
//  image K = Ex.SeqSobel();
//  double end_seq = clock();
//  image KL = Ex.TbbSobel();
//  double end_tbb = clock();
//  double seq_time = end_seq - start;
//  double tbb_time = end_tbb - end_seq;
//  std::cout << "SEQ: " << seq_time << std::endl;
//  std::cout << "TBB: " << tbb_time << std::endl;
//  ASSERT_TRUE(tbb_time < seq_time);
//  }

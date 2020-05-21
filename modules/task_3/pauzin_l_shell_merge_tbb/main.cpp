/// Copyright 2020 Pauzin Leonid
#include <gtest/gtest.h>
#include <vector>
#include "./pauzin_l_shell_merge_tbb.h"

TEST(Shell_Merge_Sort_TBB, Simple_Test) {
  const int size = 100;
  std::vector<int> v1(size);
  std::vector<int> v2(size);
  v1 = getRandomVector(size);
  v1 = v2;
  v1 = mySortTbb(v1, 2);
  v2 = ShellSort(v2, size);
  for (int i = 0; i < size; i++) {
    ASSERT_EQ(v2[i], v1[i]);
  }
}

TEST(Shell_Merge_Sort_TBB, Simple_Test_With_2_Thr) {
  const int size = 100;
  std::vector<int> v1(size);
  std::vector<int> v2(size);
  v1 = getRandomVector(size);
  v1 = v2;
  v1 = mySortTbb(v1, 2);
  v2 = ShellSort(v2, size);
  for (int i = 0; i < size; i++) {
    ASSERT_EQ(v2[i], v1[i]);
  }
}

TEST(Shell_Merge_Sort_TBB, Simple_Test_With_3_Thr) {
  const int size = 100;
  std::vector<int> v1(size);
  std::vector<int> v2(size);
  v1 = getRandomVector(size);
  v1 = v2;
  v1 = mySortTbb(v1, 3);
  v2 = ShellSort(v2, size);
  for (int i = 0; i < size; i++) {
    ASSERT_EQ(v2[i], v1[i]);
  }
}

TEST(Shell_Merge_Sort_TBB, Test_With_Odd_Amount) {
  const int size = 13;
  std::vector<int> v1(size);
  v1 = getRandomVector(size);
  std::vector<int> v2(v1);
  v1 = mySortTbb(v1, 2);
  v2 = ShellSort(v2, size);
  for (int i = 0; i < size; i++) {
    ASSERT_EQ(v2[i], v1[i]);
  }
}

TEST(Shell_Merge_Sort_TBB, Test_With_Zero_Vec) {
  std::vector<int> v1(0);
  ASSERT_ANY_THROW(v1 = mySortTbb(v1, 2));
}

TEST(Shell_Merge_Sort_TBB, Test_With_One_Elem_Vec) {
  std::vector<int> v1(1);
  v1[0] = 5;
  ASSERT_NO_THROW(v1 = mySortTbb(v1, 1));
}

TEST(Shell_Merge_Sort_TBB, Test_With_Negative_Vec) {
  const int size = 10;
  std::vector<int> v1(size);
  for (int i = 0; i < size; i++) {
    v1[i] = -2 * i;
  }
  std::vector<int> v2(v1);
  v1 = mySortTbb(v1, 4);
  v2 = ShellSort(v2, size);
  for (int i = 0; i < size; i++) {
    ASSERT_EQ(v2[i], v1[i]);
  }
}



int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

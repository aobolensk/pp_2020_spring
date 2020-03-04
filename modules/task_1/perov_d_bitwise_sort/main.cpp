  // Copyright 2020 diper1998
#include <gtest/gtest.h>
#include <vector>
#include "./bitwise_sort.h"

TEST(Sequential, Random_Sorted) {
  std::vector<double> my_vector = GetRandomVector(100);
  std::vector<double> copy_vector(my_vector);
  BitwiseSort(my_vector.begin(), my_vector.end());
  bool flag = IsSorted(&copy_vector, &my_vector);
  ASSERT_EQ(true, flag);
}

TEST(Sequential, Negativ_Sorted) {
  std::vector<double> my_vector = {-1, -6.45, -5, -0.99, -0.998};
  std::vector<double> copy_vector(my_vector);
  BitwiseSort(my_vector.begin(), my_vector.end());
  bool flag = IsSorted(&copy_vector, &my_vector);
  ASSERT_EQ(true, flag);
}

TEST(Sequential, Positiv_Sort) {
  std::vector<double> my_vector = {1.0, 3.489, 4.47, 4.54, 8.4445, 123};
  std::vector<double> copy_vector(my_vector);
  BitwiseSort(my_vector.begin(), my_vector.end());
  bool flag = IsSorted(&copy_vector, &my_vector);
  ASSERT_EQ(true, flag);
}

TEST(Sequential, Negativ_Positiv_Sort) {
  std::vector<double> my_vector = {-3.489, 4.54, 0, -5.44, -3.412, 8.4445, 123};
  std::vector<double> copy_vector(my_vector);
  BitwiseSort(my_vector.begin(), my_vector.end());
  bool flag = IsSorted(&copy_vector, &my_vector);
  ASSERT_EQ(true, flag);
}

TEST(Sequential, Mantissa_Sort) {
  std::vector<double> my_vector = {0.45, -0.45, 0.1, 0, 0.89, -0.44, 0};
  std::vector<double> copy_vector(my_vector);
  BitwiseSort(my_vector.begin(), my_vector.end());
  bool flag = IsSorted(&copy_vector, &my_vector);
  ASSERT_EQ(true, flag);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

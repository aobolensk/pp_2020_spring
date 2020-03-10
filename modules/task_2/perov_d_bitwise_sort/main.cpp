  // Copyright 2020 diper1998
#include <gtest/gtest.h>
#include <omp.h>
#include <vector>
#include "./bitwise_sort.h"

TEST(OpenMP, Random_Sorted) {
  std::vector<double> my_vector = GetRandomVector(100);
  std::vector<double> copy_vector(my_vector);
  OMPSort(my_vector.begin(), my_vector.end(), 4);
  bool flag = IsSorted(&copy_vector, &my_vector);
  ASSERT_EQ(true, flag);
}

TEST(OpenMP, Negativ_Sorted) {
  std::vector<double> my_vector = {-1, -6.45, -5, -0.99, -0.998};
  std::vector<double> copy_vector(my_vector);
  OMPSort(my_vector.begin(), my_vector.end(), 2);
  bool flag = IsSorted(&copy_vector, &my_vector);
  ASSERT_EQ(true, flag);
}

TEST(OpenMP, Positiv_Sort) {
  std::vector<double> my_vector = {1.0, 3.489, 4.47, 4.54, 8.4445, 123, 6, 32};
  std::vector<double> copy_vector(my_vector);
  OMPSort(my_vector.begin(), my_vector.end(), 4);
  bool flag = IsSorted(&copy_vector, &my_vector);
  ASSERT_EQ(true, flag);
}

TEST(OpenMP, Random_Sorted_Multi) {
  std::vector<double> my_vector = GetRandomVector(100);
  std::vector<double> copy_vector(my_vector);
  OMPSort(my_vector.begin(), my_vector.end(), 16);
  bool flag = IsSorted(&copy_vector, &my_vector);
  ASSERT_EQ(true, flag);
}

TEST(OpenMP, Random_Sorted_Multi_Multi) {
  std::vector<double> my_vector = GetRandomVector(100);
  std::vector<double> copy_vector(my_vector);
  OMPSort(my_vector.begin(), my_vector.end(), 32);
  bool flag = IsSorted(&copy_vector, &my_vector);
  ASSERT_EQ(true, flag);
}

  int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  }

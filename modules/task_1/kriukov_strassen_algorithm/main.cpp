// Copyright 2020 Kriukov Dmitry
#include <gtest/gtest.h>
#include <vector>
#include <../../../modules/task_1/kriukov_strassen_algorithm/strassen_algorithm.h>

#define EXPECT_CONTAINER_DOUBLE_EQ(TYPE, ref_, target_) \
{\
 TYPE ref = ref_;\
 TYPE target = target_;\
 if(ref.size() != target.size())\
  ADD_FAILURE() << "different element count";\
TYPE::iterator rit = ref.begin();\
TYPE::iterator tit = target.begin();\
unsigned int i = 0;\
while(rit != ref.end()){\
  EXPECT_DOUBLE_EQ(*rit, *tit)\
  << "Expected equality of these values:" << std::endl\
  << "  " #ref_ "[" << i << "]" << std::endl << \
  "   Which is : " << *rit << std::endl\
  << "  " #target_ "[" << i  << "]" << std::endl << \
  "   Which is : " << *tit;\
  i++, tit++, rit++;\
  }\
}

TEST(SequentialStrassen, Test_Regular_Sum) {

  std::vector<double> a = { 1.0, 2.0, 3.0, 4.0 };
  std::vector<double> b = { 1.0, 2.0, 3.0, 4.0 };
  std::vector<double> c = { 2.0, 4.0, 6.0, 8.0 };
  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, regularSum(a, b, 4), c);
}

TEST(SequentialStrassen, Test_Regular_Mult) {

  std::vector<double> a = { 1.0, 2.0, 3.0, 4.0 };
  std::vector<double> b = { 1.0, 2.0, 3.0, 4.0 };
  std::vector<double> c = { 7.0, 10.0, 15.0, 22.0 };

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, regularMultiplication(a, b), c);
}

TEST(SequentialStrassen, Test_Regular_Mult_size_9) {

  std::vector<double> a = { 9.0, 0.0, 3.0, 0.0, 4.0, 1.0, 9.0, 2.0, 7.0 };
  std::vector<double> b = { 9.0, 0.0, 3.0, 0.0, 4.0, 1.0, 9.0, 2.0, 7.0 };
  std::vector<double> c = { 108.0, 6.0, 48.0, 9.0, 18.0, 11.0, 144.0, 22.0, 78.0 };

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, regularMultiplication(a, b), c);
}


TEST(SequentialStrassen, Test_Split_Matrix) {

  std::vector<double> mtx = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
  std::vector<double> a, b, c, d;
  std::vector<double> a_exp = { 1.0, 2.0, 5.0, 6.0 };
  std::vector<double> b_exp = { 3.0, 4.0, 7.0, 8.0 };
  std::vector<double> c_exp = { 9.0, 10.0, 13.0, 14.0 };
  std::vector<double> d_exp = { 11.0, 12.0, 15.0, 16.0 };

  splitMatrix(mtx, a, b, c, d, 16);

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, a, a_exp);
  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, b, b_exp);  
  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, c, c_exp);
  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, d, d_exp);
}

TEST(SequentialStrassen, Test_Merge_Matrix) {
  std::vector<double> mtx_exp = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
  std::vector<double> a = { 1.0, 2.0, 5.0, 6.0 };
  std::vector<double> b = { 3.0, 4.0, 7.0, 8.0 };
  std::vector<double> c = { 9.0, 10.0, 13.0, 14.0 };
  std::vector<double> d = { 11.0, 12.0, 15.0, 16.0 };
  std::vector<double> mtx;

  mergeMatrix(mtx, a, b, c, d, 16);

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, mtx, mtx_exp);
}

TEST(SequentialStrassen, Test_Increase_Size_Size_12) {
  std::vector<double> mtx = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, };
  std::vector<double> mtx_exp = { 1.0, 2.0, 3.0, 0.0, 4.0, 5.0, 6.0, 0.0 , 7.0, 8.0, 9.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, toPowerOfTwoSize(mtx), mtx_exp);
}

TEST(SequentialStrassen, Test_Increase_Size_Size_16) {
  std::vector<double> mtx = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, toPowerOfTwoSize(mtx), mtx);
}


//TEST(SequentialStrassen, Test_Strassen_Mult_size_8) {
//
//  std::vector<double> a = getRandomMatrix(8);
//  std::vector<double> b = getRandomMatrix(8);
//  std::vector<double> res_regular = regularMultiplication(a, b);
//  std::vector<double> res_strassen = strassenMultiplication(a, b);
//
//  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_regular, res_strassen);
//}
//
//TEST(SequentialStrassen, Test_Strassen_Mult_size_64) {
//
//  std::vector<double> a = getRandomMatrix(64);
//  std::vector<double> b = getRandomMatrix(64);
//  std::vector<double> res_regular = regularMultiplication(a, b);
//  std::vector<double> res_strassen = strassenMultiplication(a, b);
//
//  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_regular, res_strassen);
//}

//#define STRASSEN_ALGORITHM_TIME_TEST_ON
//
//#ifdef STRASSEN_ALGORITHM_TIME_TEST_ON
//
//TEST(SequentialStrassen, Test_Strassen_Mult_size_64) {
//
//  std::vector<double> a = getRandomMatrix(64);
//  std::vector<double> b = getRandomMatrix(64);
//  std::vector<double> res_regular = regularMultiplication(a, b);
//  std::vector<double> res_strassen = strassenMultiplication(a, b);
//
//  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_regular, res_strassen);
//}
//
//#endif // STRASSEN_ALGORITHM_TIME_TEST_ON
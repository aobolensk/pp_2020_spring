// Copyright 2020 Kriukov Dmitry
#include <gtest/gtest.h>
#include <../../../modules/task_1/kriukov_strassen_algorithm/strassen_algorithm.h>
#include <vector>

#define EXPECT_CONTAINER_DOUBLE_EQ(TYPE, ref_, target_)\
{\
  TYPE ref = ref_;\
  TYPE target = target_;\
  if (ref.size() != target.size())\
    ADD_FAILURE() << "different element count";\
  TYPE::iterator rit = ref.begin();\
  TYPE::iterator tit = target.begin();\
  unsigned int i = 0;\
  while (rit != ref.end()) {\
    ASSERT_DOUBLE_EQ(*rit, *tit)\
    << "Expected equality of these values:" << std::endl\
    << "  " #ref_ "[" << i << "]" << std::endl << \
    "   Which is : " << *rit << std::endl\
    << "  " #target_ "[" << i  << "]" << std::endl << \
    "   Which is : " << *tit;\
    i++, tit++, rit++;\
  }\
}

TEST(SequentialStrassen, Test_Matrix_Sum) {
  std::vector<double> a = { 1.0, 2.0, 3.0, 4.0 };
  std::vector<double> b = { 1.0, 2.0, 3.0, 4.0 };
  std::vector<double> c = { 2.0, 4.0, 6.0, 8.0 };
  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, sum(a, b, 2), c);
}

TEST(SequentialStrassen, Test_Matrix_Diff) {
  std::vector<double> a = { 1.0, 2.0, 3.0, 4.0 };
  std::vector<double> b = { 1.0, 2.0, 3.0, 4.0 };
  std::vector<double> c = { 0.0, 0.0, 0.0, 0.0 };
  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, diff(a, b, 2), c);
}

TEST(SequentialStrassen, Test_Regular_Mult) {
  std::vector<double> a = { 1.0, 2.0, 3.0, 4.0 };
  std::vector<double> b = { 1.0, 2.0, 3.0, 4.0 };
  std::vector<double> c = { 7.0, 10.0, 15.0, 22.0 };

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, regularMultiplication(a, b, 2), c);
}

TEST(SequentialStrassen, Test_Regular_Mult_size_9) {
  std::vector<double> a = { 9.0, 0.0, 3.0, 0.0, 4.0, 1.0, 9.0, 2.0, 7.0 };
  std::vector<double> b = { 9.0, 0.0, 3.0, 0.0, 4.0, 1.0, 9.0, 2.0, 7.0 };
  std::vector<double> c = { 108.0, 6.0, 48.0, 9.0, 18.0, 11.0, 144.0, 22.0, 78.0 };

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, regularMultiplication(a, b, 3), c);
}


TEST(SequentialStrassen, Test_Split_Matrix) {
  std::vector<double> mtx = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
  std::vector<double> a, b, c, d;
  std::vector<double> a_exp = { 1.0, 2.0, 5.0, 6.0 };
  std::vector<double> b_exp = { 3.0, 4.0, 7.0, 8.0 };
  std::vector<double> c_exp = { 9.0, 10.0, 13.0, 14.0 };
  std::vector<double> d_exp = { 11.0, 12.0, 15.0, 16.0 };

  splitMatrix(mtx, &a, &b, &c, &d, 4);

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, a, a_exp);
  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, b, b_exp);
  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, c, c_exp);
  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, d, d_exp);
}

TEST(SequentialStrassen, Test_Merge_Matrix) {
  std::vector<double> mtx_exp = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
    7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
  std::vector<double> a = { 1.0, 2.0, 5.0, 6.0 };
  std::vector<double> b = { 3.0, 4.0, 7.0, 8.0 };
  std::vector<double> c = { 9.0, 10.0, 13.0, 14.0 };
  std::vector<double> d = { 11.0, 12.0, 15.0, 16.0 };
  std::vector<double> mtx;

  mergeMatrix(&mtx, a, b, c, d, 4);

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, mtx, mtx_exp);
}

TEST(SequentialStrassen, Test_Increase_Size_Size_12) {
  std::vector<double> mtx = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, };
  std::vector<double> mtx_exp = { 1.0, 2.0, 3.0, 0.0, 4.0, 5.0, 6.0, 0.0 , 7.0, 8.0, 9.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, toPowerOfTwoSize(mtx, 3), mtx_exp);
}

TEST(SequentialStrassen, Test_Reduse_Size_Size_9) {
  std::vector<double> mtx_exp = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, };
  std::vector<double> mtx = { 1.0, 2.0, 3.0, 0.0, 4.0, 5.0, 6.0, 0.0 , 7.0, 8.0, 9.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, matrixReduce(mtx, 3), mtx_exp);
}

TEST(SequentialStrassen, Test_Increase_Size_Size_16) {
  std::vector<double> mtx = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, toPowerOfTwoSize(mtx, 4), mtx);
}

TEST(SequentialStrassen, Test_Strassen_Mult) {
  std::vector<double> a = { 1.0, 2.0, 3.0, 4.0 };
  std::vector<double> b = { 1.0, 2.0, 3.0, 4.0 };
  std::vector<double> c = { 7.0, 10.0, 15.0, 22.0 };

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, strassenMultiplication(a, b, 2), c);
}

TEST(SequentialStrassen, Test_Strassen_Mult_size_8) {
  unsigned int sz = 8;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  std::vector<double> res_regular = regularMultiplication(a, b, sz);
  std::vector<double> res_strassen = strassenMultiplication(a, b, sz);

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_regular, res_strassen);
}

TEST(SequentialStrassen, Test_Strassen_Mult_size_64) {
  unsigned int sz = 64;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  std::vector<double> res_regular = regularMultiplication(a, b, sz);
  std::vector<double> res_strassen = strassenMultiplication(a, b, sz);

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_regular, res_strassen);
}

TEST(SequentialStrassen, Test_Strassen_Mult_size_3) {
  unsigned int sz = 3;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  std::vector<double> res_regular = regularMultiplication(a, b, sz);
  std::vector<double> res_strassen = strassenMultiplication(a, b, sz);

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_regular, res_strassen);
}

  TEST(SequentialStrassen, Test_Strassen_Mult_size_59) {
    unsigned int sz = 59;
    std::vector<double> a = getRandomMatrix(sz);
    std::vector<double> b = getRandomMatrix(sz);
    std::vector<double> res_regular = regularMultiplication(a, b, sz);
    std::vector<double> res_strassen = strassenMultiplication(a, b, sz);

    EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_regular, res_strassen);
}

#define STRASSEN_ALGORITHM_TIME_TEST_OFF

#ifdef STRASSEN_ALGORITHM_TIME_TEST_ON

TEST(SequentialStrassen, Time_Test_Strassen_Mult_size_256) {
  unsigned int sz = 256;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  clock_t start_r = clock();
  std::vector<double> res_regular = regularMultiplication(a, b, sz);
  clock_t end_r = clock();
  clock_t start_s = clock();
  std::vector<double> res_strassen = strassenMultiplication(a, b, sz);
  clock_t end_s = clock();

  double seconds_r = static_cast<double>(end_r - start_r) / CLOCKS_PER_SEC;
  std::cout << "Regular : " << seconds_r << std::endl;

  double seconds_s = static_cast<double>(end_s - start_s) / CLOCKS_PER_SEC;
  std::cout << "Strassen : " << seconds_s << std::endl;

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_regular, res_strassen);
}

TEST(SequentialStrassen, Time_Test_Strassen_Mult_size_512) {
  unsigned int sz = 512;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  clock_t start_r = clock();
  std::vector<double> res_regular = regularMultiplication(a, b, sz);
  clock_t end_r = clock();
  clock_t start_s = clock();
  std::vector<double> res_strassen = strassenMultiplication(a, b, sz);
  clock_t end_s = clock();

  double seconds_r = static_cast<double>(end_r - start_r) / CLOCKS_PER_SEC;
  std::cout << "Regular : " << seconds_r << std::endl;

  double seconds_s = static_cast<double>(end_s - start_s) / CLOCKS_PER_SEC;
  std::cout << "Strassen : " << seconds_s << std::endl;

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_regular, res_strassen);
}

TEST(SequentialStrassen, Time_Test_Strassen_Mult_size_529) {
  unsigned int sz = 529;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  clock_t start_r = clock();
  std::vector<double> res_regular = regularMultiplication(a, b, sz);
  clock_t end_r = clock();
  clock_t start_s = clock();
  std::vector<double> res_strassen = strassenMultiplication(a, b, sz);
  clock_t end_s = clock();

  double seconds_r = static_cast<double>(end_r - start_r) / CLOCKS_PER_SEC;
  std::cout << "Regular : " << seconds_r << std::endl;

  double seconds_s = static_cast<double>(end_s - start_s) / CLOCKS_PER_SEC;
  std::cout << "Strassen : " << seconds_s << std::endl;

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_regular, res_strassen);
}

TEST(SequentialStrassen, Time_Test_Strassen_Mult_size_1024) {
  unsigned int sz = 1024;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  clock_t start_r = clock();
  std::vector<double> res_regular = regularMultiplication(a, b, sz);
  clock_t end_r = clock();
  clock_t start_s = clock();
  std::vector<double> res_strassen = strassenMultiplication(a, b, sz);
  clock_t end_s = clock();

  double seconds_r = static_cast<double>(end_r - start_r) / CLOCKS_PER_SEC;
  std::cout << "Regular : " << seconds_r << std::endl;

  double seconds_s = static_cast<double>(end_s - start_s) / CLOCKS_PER_SEC;
  std::cout << "Strassen : " << seconds_s << std::endl;

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_regular, res_strassen);
}

TEST(SequentialStrassen, Time_Test_Strassen_Mult_size_1029) {
  unsigned int sz = 1029;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  clock_t start_r = clock();
  std::vector<double> res_regular = regularMultiplication(a, b, sz);
  clock_t end_r = clock();
  clock_t start_s = clock();
  std::vector<double> res_strassen = strassenMultiplication(a, b, sz);
  clock_t end_s = clock();

  double seconds_r = static_cast<double>(end_r - start_r) / CLOCKS_PER_SEC;
  std::cout << "Regular : " << seconds_r << std::endl;

  double seconds_s = static_cast<double>(end_s - start_s) / CLOCKS_PER_SEC;
  std::cout << "Strassen : " << seconds_s << std::endl;

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_regular, res_strassen);
}

TEST(SequentialStrassen, Time_Test_Strassen_Mult_size_2048) {
  unsigned int sz = 2048;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  clock_t start_r = clock();
  std::vector<double> res_regular = regularMultiplication(a, b, sz);
  clock_t end_r = clock();
  clock_t start_s = clock();
  std::vector<double> res_strassen = strassenMultiplication(a, b, sz);
  clock_t end_s = clock();

  double seconds_r = static_cast<double>(end_r - start_r) / CLOCKS_PER_SEC;
  std::cout << "Regular : " << seconds_r << std::endl;

  double seconds_s = static_cast<double>(end_s - start_s) / CLOCKS_PER_SEC;
  std::cout << "Strassen : " << seconds_s << std::endl;

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_regular, res_strassen);
}

TEST(SequentialStrassen, Time_Test_Strassen_Mult_size_4096) {
  unsigned int sz = 4096;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  clock_t start_s = clock();
  std::vector<double> res_strassen = strassenMultiplication(a, b, sz);
  clock_t end_s = clock();


  double seconds_s = static_cast<double>(end_s - start_s) / CLOCKS_PER_SEC;
  std::cout << "Strassen : " << seconds_s << std::endl;
}

#endif  // STRASSEN_ALGORITHM_TIME_TEST_ON

// Copyright 2020 Kriukov Dmitry
#include <gtest/gtest.h>
#include <omp.h>
#include <../../../modules/task_3/kriukov_strassen_algorithm/strassen_algorithm.h>
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

TEST(OMPStrassen, Test_Strassen_Mult) {
  std::vector<double> a = { 1.0, 2.0, 3.0, 4.0 };
  std::vector<double> b = { 1.0, 2.0, 3.0, 4.0 };
  std::vector<double> c = { 7.0, 10.0, 15.0, 22.0 };

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, strassenMultiplication_tbb(a, b, 2), c);
}

TEST(OMPStrassen, Test_Strassen_Mult_size_8) {
  unsigned int sz = 8;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  std::vector<double> res_regular = regularMultiplication(a, b, sz);
  std::vector<double> res_strassen = strassenMultiplication_tbb(a, b, sz);

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_regular, res_strassen);
}

TEST(OMPStrassen, Test_Strassen_Mult_size_64) {
  unsigned int sz = 64;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  std::vector<double> res_regular = regularMultiplication(a, b, sz);
  std::vector<double> res_strassen = strassenMultiplication_tbb(a, b, sz);

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_regular, res_strassen);
}

TEST(OMPStrassen, Test_Strassen_Mult_size_3) {
  unsigned int sz = 3;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  std::vector<double> res_regular = regularMultiplication(a, b, sz);
  std::vector<double> res_strassen = strassenMultiplication_tbb(a, b, sz);

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_regular, res_strassen);
}

  TEST(OMPStrassen, Test_Strassen_Mult_size_59) {
    unsigned int sz = 59;
    std::vector<double> a = getRandomMatrix(sz);
    std::vector<double> b = getRandomMatrix(sz);
    std::vector<double> res_regular = regularMultiplication(a, b, sz);
    std::vector<double> res_strassen = strassenMultiplication_tbb(a, b, sz);

    EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_regular, res_strassen);
}

#define STRASSEN_ALGORITHM_TIME_TEST_OFF

#ifdef STRASSEN_ALGORITHM_TIME_TEST_ON

TEST(OMPStrassen, Time_Test_Strassen_Mult_size_256) {
  unsigned int sz = 256;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  clock_t start_r = clock();
  std::vector<double> res_seq = strassenMultiplication(a, b, sz);
  clock_t end_r = clock();
  clock_t start_s = clock();
  std::vector<double> res_parallel = strassenMultiplication_tbb(a, b, sz);
  clock_t end_s = clock();

  double seconds_r = static_cast<double>(end_r - start_r) / CLOCKS_PER_SEC;
  std::cout << "seq : " << seconds_r << std::endl;

  double seconds_s = static_cast<double>(end_s - start_s) / CLOCKS_PER_SEC;
  std::cout << "parallel : " << seconds_s << std::endl;

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_seq, res_parallel);
}

TEST(OMPStrassen, Time_Test_Strassen_Mult_size_512) {
  unsigned int sz = 512;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  clock_t start_r = clock();
  std::vector<double> res_seq = strassenMultiplication(a, b, sz);
  clock_t end_r = clock();
  clock_t start_s = clock();
  std::vector<double> res_parallel = strassenMultiplication_tbb(a, b, sz);
  clock_t end_s = clock();

  double seconds_r = static_cast<double>(end_r - start_r) / CLOCKS_PER_SEC;
  std::cout << "seq : " << seconds_r << std::endl;

  double seconds_s = static_cast<double>(end_s - start_s) / CLOCKS_PER_SEC;
  std::cout << "parallel : " << seconds_s << std::endl;

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_seq, res_parallel);
}

TEST(OMPStrassen, Time_Test_Strassen_Mult_size_529) {
  unsigned int sz = 529;
  omp_set_num_threads(6);
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  clock_t start_r = clock();
  std::vector<double> res_seq = strassenMultiplication(a, b, sz);
  clock_t end_r = clock();
  clock_t start_s = clock();
  std::vector<double> res_parallel = strassenMultiplication_tbb(a, b, sz);
  clock_t end_s = clock();

  double seconds_r = static_cast<double>(end_r - start_r) / CLOCKS_PER_SEC;
  std::cout << "seq : " << seconds_r << std::endl;

  double seconds_s = static_cast<double>(end_s - start_s) / CLOCKS_PER_SEC;
  std::cout << "parallel : " << seconds_s << std::endl;

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_seq, res_parallel);
}

TEST(OMPStrassen, Time_Test_Strassen_Mult_size_1024) {
  unsigned int sz = 1024;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  clock_t start_r = clock();
  std::vector<double> res_seq = strassenMultiplication(a, b, sz);
  clock_t end_r = clock();
  clock_t start_s = clock();
  std::vector<double> res_parallel = strassenMultiplication_tbb(a, b, sz);
  clock_t end_s = clock();

  double seconds_r = static_cast<double>(end_r - start_r) / CLOCKS_PER_SEC;
  std::cout << "seq : " << seconds_r << std::endl;

  double seconds_s = static_cast<double>(end_s - start_s) / CLOCKS_PER_SEC;
  std::cout << "parallel : " << seconds_s << std::endl;

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_seq, res_parallel);
}

TEST(OMPStrassen, Time_Test_Strassen_Mult_size_1029) {
  unsigned int sz = 1029;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  clock_t start_r = clock();
  std::vector<double> res_seq = strassenMultiplication(a, b, sz);
  clock_t end_r = clock();
  clock_t start_s = clock();
  std::vector<double> res_parallel = strassenMultiplication_tbb(a, b, sz);
  clock_t end_s = clock();

  double seconds_r = static_cast<double>(end_r - start_r) / CLOCKS_PER_SEC;
  std::cout << "seq : " << seconds_r << std::endl;

  double seconds_s = static_cast<double>(end_s - start_s) / CLOCKS_PER_SEC;
  std::cout << "parallel : " << seconds_s << std::endl;

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_seq, res_parallel);
}

TEST(OMPStrassen, Time_Test_Strassen_Mult_size_2048) {
  unsigned int sz = 2048;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  clock_t start_r = clock();
  std::vector<double> res_seq = strassenMultiplication(a, b, sz);
  clock_t end_r = clock();
  clock_t start_s = clock();
  std::vector<double> res_parallel = strassenMultiplication_tbb(a, b, sz);
  clock_t end_s = clock();

  double seconds_r = static_cast<double>(end_r - start_r) / CLOCKS_PER_SEC;
  std::cout << "seq : " << seconds_r << std::endl;

  double seconds_s = static_cast<double>(end_s - start_s) / CLOCKS_PER_SEC;
  std::cout << "parallel : " << seconds_s << std::endl;

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_seq, res_parallel);
}

TEST(OMPStrassen, Time_Test_Strassen_Mult_size_4096) {
  unsigned int sz = 4096;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  clock_t start_r = clock();
  std::vector<double> res_seq = strassenMultiplication(a, b, sz);
  clock_t end_r = clock();
  clock_t start_s = clock();
  std::vector<double> res_parallel = strassenMultiplication_tbb(a, b, sz);
  clock_t end_s = clock();

  double seconds_r = static_cast<double>(end_r - start_r) / CLOCKS_PER_SEC;
  std::cout << "seq : " << seconds_r << std::endl;

  double seconds_s = static_cast<double>(end_s - start_s) / CLOCKS_PER_SEC;
  std::cout << "parallel : " << seconds_s << std::endl;

  EXPECT_CONTAINER_DOUBLE_EQ(std::vector<double>, res_seq, res_parallel);
}

TEST(SequentialStrassen, Time_Test_Strassen_Mult_size_8192) {
  unsigned int sz = 8192;
  std::vector<double> a = getRandomMatrix(sz);
  std::vector<double> b = getRandomMatrix(sz);
  clock_t start_s = clock();
  std::vector<double> res_strassen = strassenMultiplication_tbb(a, b, sz);
  clock_t end_s = clock();


  double seconds_s = static_cast<double>(end_s - start_s) / CLOCKS_PER_SEC;
  std::cout << "parallel : " << seconds_s << std::endl;
}

#endif  // STRASSEN_ALGORITHM_TIME_TEST_ON

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

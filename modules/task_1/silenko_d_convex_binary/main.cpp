// Copyright 2020 Silenko Dmitrii

#include <gtest/gtest.h>
#include <algorithm>
#include <vector>
#include "../../../modules/task_1/silenko_d_convex_binary/convex_binary.h"

TEST(convex_binary_seq, test_one_point) {
  std::vector<int*> result;
  int** convex_mas = NULL;
  int num = 0, n = 5, m = 20;

  int** mas = new int*[n];
  for (int i = 0; i < n; i++)
    mas[i] = new int[m];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      mas[i][j] = 0;
  mas[2][7] = 1;

  result = getComponent(mas, n, m, &convex_mas, &num);

  int s = result.size();
  int** tmp = new int*[s];
  for (int i = 0; i < s; i++)
    tmp[i] = new int[2];
  tmp[0][0] = 7;
  tmp[0][1] = 2;

  for (int i = 0; i < s; i++) {
    int* temp = result[i];
    EXPECT_EQ(temp[0], tmp[i][0]);
    EXPECT_EQ(temp[1], tmp[i][1]);
  }

  for (int i = 0; i < s; i++)
    delete[] tmp[i];
  delete[] tmp;
  for (int i = 0; i < n; i++)
    delete[] mas[i];
  delete[] mas;
  for (int i = 0; i < num; i++)
    delete[] convex_mas[i];
  delete[] convex_mas;
}

TEST(convex_binary_seq, test_one_line) {
  std::vector<int*> result;
  int** convex_mas = NULL;
  int num = 0, n = 1, m = 20;

  int** mas = new int*[n];
  for (int i = 0; i < n; i++)
    mas[i] = new int[m];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      mas[i][j] = 0;
  mas[0][2] = 1;
  mas[0][11] = 1;
  mas[0][7] = 1;
  mas[0][19] = 1;
  mas[0][5] = 1;
  mas[0][17] = 1;


  result = getComponent(mas, n, m, &convex_mas, &num);

  int** tmp = new int*[2];
  for (int i = 0; i < 2; i++)
    tmp[i] = new int[2];
  tmp[0][0] = 2;
  tmp[0][1] = 0;
  tmp[1][0] = 19;
  tmp[1][1] = 0;

  int s = result.size();
  for (int i = 0; i < s; i++) {
    int* temp = result[i];
    EXPECT_EQ(temp[0], tmp[i][0]);
    EXPECT_EQ(temp[1], tmp[i][1]);
  }

  for (int i = 0; i < s; i++)
    delete[] tmp[i];
  delete[] tmp;
  for (int i = 0; i < n; i++)
    delete[] mas[i];
  delete[] mas;
  for (int i = 0; i < num; i++)
    delete[] convex_mas[i];
  delete[] convex_mas;
}

TEST(convex_binary_seq, test_sq) {
  std::vector<int*> result;
  int** convex_mas = NULL;
  int num = 0, n = 10, m = 10;

  int** mas = new int*[n];
  for (int i = 0; i < n; i++)
    mas[i] = new int[m];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      mas[i][j] = 0;
  mas[0][2] = 1;
  mas[0][5] = 1;
  mas[0][8] = 1;
  mas[2][5] = 1;
  mas[2][8] = 1;
  mas[5][8] = 1;
  mas[5][5] = 1;
  mas[5][4] = 1;
  mas[3][2] = 1;
  mas[1][2] = 1;


  result = getComponent(mas, n, m, &convex_mas, &num);

  int s = result.size();
  int** tmp = new int*[s];
  for (int i = 0; i < s; i++)
    tmp[i] = new int[2];
  tmp[0][0] = 2;
  tmp[0][1] = 0;
  tmp[1][0] = 8;
  tmp[1][1] = 0;
  tmp[2][0] = 8;
  tmp[2][1] = 5;
  tmp[3][0] = 4;
  tmp[3][1] = 5;
  tmp[4][0] = 2;
  tmp[4][1] = 3;

  for (int i = 0; i < s; i++) {
    int* temp = result[i];
    EXPECT_EQ(temp[0], tmp[i][0]);
    EXPECT_EQ(temp[1], tmp[i][1]);
  }

  for (int i = 0; i < s; i++)
    delete[] tmp[i];
  delete[] tmp;
  for (int i = 0; i < n; i++)
    delete[] mas[i];
  delete[] mas;
  for (int i = 0; i < num; i++)
    delete[] convex_mas[i];
  delete[] convex_mas;
}

TEST(convex_binary_seq, test_inside) {
  std::vector<int*> result;
  int** convex_mas = NULL;
  int num = 0, n = 6, m = 6;

  int** mas = new int*[n];
  for (int i = 0; i < n; i++)
    mas[i] = new int[m];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      mas[i][j] = 0;
  mas[0][1] = 1;
  mas[0][2] = 1;
  mas[1][1] = 1;
  mas[1][5] = 1;
  mas[2][4] = 1;
  mas[2][5] = 1;
  mas[3][5] = 1;
  mas[4][2] = 1;

  result = getComponent(mas, n, m, &convex_mas, &num);
  std::vector<int*> inl;
  inl = Inside(result, convex_mas, num);

  int s = inl.size();
  int** tmp = new int*[s];
  for (int i = 0; i < s; i++)
    tmp[i] = new int[2];
  tmp[0][0] = 1;
  tmp[0][1] = 0;
  tmp[1][0] = 5;
  tmp[1][1] = 1;
  tmp[2][0] = 2;
  tmp[2][1] = 4;

  for (int i = 0; i < s; i++) {
    int* temp = inl[i];
    EXPECT_EQ(temp[0], tmp[i][0]);
    EXPECT_EQ(temp[1], tmp[i][1]);
  }

  for (int i = 0; i < s; i++)
    delete[] tmp[i];
  delete[] tmp;
  for (int i = 0; i < n; i++)
    delete[] mas[i];
  delete[] mas;
  for (int i = 0; i < num; i++)
    delete[] convex_mas[i];
  delete[] convex_mas;
}

TEST(convex_binary_seq, test_rand) {
  std::vector<int*> result;
  int** convex_mas = NULL;
  int num = 0, n = 20, m = 20;

  int** mas = getRandomMas(n, m);

  EXPECT_NO_THROW(result = getComponent(mas, n, m, &convex_mas, &num));

  std::vector<int*> inside;

  EXPECT_NO_THROW(inside = Inside(result, convex_mas, num));

  for (int i = 0; i < n; i++)
    delete[] mas[i];
  delete[] mas;
  for (int i = 0; i < num; i++)
    delete[] convex_mas[i];
  delete[] convex_mas;
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

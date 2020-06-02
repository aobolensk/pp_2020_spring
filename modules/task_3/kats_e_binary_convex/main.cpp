// Copyright 2020 Kats Eugeny

#include <gtest/gtest.h>
#include <omp.h>
#include <algorithm>
#include <vector>
#include "../../../modules/task_2/kats_binary_convex/convex_binary_omp.h"

TEST(convex_binary_seq, random_pic_validation) {
  // Arrange
  SideClass sc;
  ASSERT_ANY_THROW(sc.getRandomPic(-1, -1));
}

TEST(convex_binary_seq, test_one_point) {
    // Arrange
    std::vector<int*> result;
    MainClass mc;
    int** convex_arr = NULL;
    int num = 0, a = 5, b = 20;
    // Act
    int** arr = new int*[a];
    for (int i = 0; i < a; i++) arr[i] = new int[b];
    for (int i = 0; i < a; i++)
        for (int j = 0; j < b; j++) arr[i][j] = 0;
    arr[2][7] = 1;

    result = mc.getComponent_OMP(arr, a, b, &convex_arr, &num);

    int s = result.size();
    int** tmp = new int*[s];
    for (int i = 0; i < s; i++) tmp[i] = new int[2];
    tmp[0][0] = 7;
    tmp[0][1] = 2;
    // Assert
    for (int i = 0; i < s; i++) {
        int* temp = result[i];
        EXPECT_EQ(temp[0], tmp[i][0]);
        EXPECT_EQ(temp[1], tmp[i][1]);
    }
}

TEST(convex_binary_seq, test_one_line) {
    // Arrange
    MainClass mc;
    std::vector<int*> result;
    int** convex_arr = NULL;
    int num = 0, a = 1, b = 20;
    // Act
    int** arr = new int*[a];
    for (int i = 0; i < a; i++) arr[i] = new int[b];
    for (int i = 0; i < a; i++)
        for (int j = 0; j < b; j++) arr[i][j] = 0;
    arr[0][2] = 1;
    arr[0][11] = 1;
    arr[0][7] = 1;
    arr[0][19] = 1;
    arr[0][5] = 1;
    arr[0][17] = 1;

    result = mc.getComponent_OMP(arr, a, b, &convex_arr, &num);

    int** tmp = new int*[2];
    for (int i = 0; i < 2; i++) tmp[i] = new int[2];
    tmp[0][0] = 2;
    tmp[0][1] = 0;
    tmp[1][0] = 19;
    tmp[1][1] = 0;
    // Assert
    int s = result.size();
    for (int i = 0; i < s; i++) {
        int* temp = result[i];
        EXPECT_EQ(temp[0], tmp[i][0]);
        EXPECT_EQ(temp[1], tmp[i][1]);
    }
}

TEST(convex_binary_seq, test_rand) {
    // Arrange
    MainClass mc;
    SideClass sc;
    std::vector<int*> result;
    int** convex_arr = NULL;
    int num = 0, a = 20, b = 20;
    // Act
    int** arr = sc.getRandomPic(a, b);
    // Assert
    EXPECT_NO_THROW(result = mc.getComponent_OMP(arr, a, b, &convex_arr, &num));

    std::vector<int*> inside;

    EXPECT_NO_THROW(inside = mc.inside(result, convex_arr, num));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

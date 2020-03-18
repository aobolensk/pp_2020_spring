// Copyright 2020 Utkin Konstantin
#include <gtest/gtest.h>
#include <vector>
#include "./lin_img_filter_gauss_vert.h"

TEST(Lin_Img_Filter_Gauss_Vert, Cant_Get_Random_Pic_With_Bad_Sizes) {
    EXPECT_ANY_THROW(getRandomPic(0, 0));
    EXPECT_ANY_THROW(getRandomPic(-1, 0));
    EXPECT_ANY_THROW(getRandomPic(0, -1));
    EXPECT_ANY_THROW(getRandomPic(-100, -100));
}

TEST(Lin_Img_Filter_Gauss_Vert, Can_Get_Random_Pic_With_Normal_Sizes) {
    ASSERT_NO_THROW(getRandomPic(1, 1));
    ASSERT_NO_THROW(getRandomPic(1545, 2231));
}

TEST(Lin_Img_Filter_Gauss_Vert, Random_Pic_Has_Values_Ranging_From_0_To_255) {
    int n = 20;
    int m = 40;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);

    for (int i = 0; i < n * m; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_GE(pic[i][j], 0);
            ASSERT_LE(pic[i][j], 255);
        }
    }
}

TEST(Lin_Img_Filter_Gauss_Vert, Cant_Add_Borders_With_Bad_Sizes) {
    int n = 15;
    int m = 31;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);

    EXPECT_ANY_THROW(addBorders(pic, 0, 0));
    EXPECT_ANY_THROW(addBorders(pic, -n, m));
    EXPECT_ANY_THROW(addBorders(pic, n, -m));
    EXPECT_ANY_THROW(addBorders(pic, -n, -m));
}

TEST(Lin_Img_Filter_Gauss_Vert, Can_Add_Borders_With_Normal_Sizes) {
    int n = 5;
    int m = 50;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);

    ASSERT_NO_THROW(addBorders(pic, n, m));
}

TEST(Lin_Img_Filter_Gauss_Vert, Added_Edges_Are_Correct) {
    int n = 11;
    int m = 24;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);
    std::vector<std::vector<int>> newPic = addBorders(pic, n, m);

    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(pic[0][i], newPic[0][i]);
        ASSERT_EQ(pic[n - 1][i], newPic[n + 2 - 1][i]);
        ASSERT_EQ(pic[(n - 1) * m][i], newPic[(n + 2 - 1) * (m + 2)][i]);
        ASSERT_EQ(pic[n * m - 1][i], newPic[(n + 2) * (m + 2) - 1][i]);
    }
}

TEST(Lin_Img_Filter_Gauss_Vert, Added_Top_And_Bottom_Borders_Are_Correct) {
    int n = 31;
    int m = 17;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);
    std::vector<std::vector<int>> newPic = addBorders(pic, n, m);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(pic[i][j], newPic[i + 1][j]);
            ASSERT_EQ(pic[(n - 1) * m][j], newPic[(n + 2 - 1) * (m + 2) + 1][j]);
        }
    }
}

TEST(Lin_Img_Filter_Gauss_Vert, Added_Right_And_Left_Borders_Are_Correct) {
    int n = 14;
    int m = 42;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);
    std::vector<std::vector<int>> newPic = addBorders(pic, n, m);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(pic[i * n][j], newPic[(i + 1) * (n + 2)][j]);
            ASSERT_EQ(pic[i * n + n - 1][j], newPic[(i + 1) * (n + 2) + n + 2 - 1][j]);
        }
    }
}

TEST(Lin_Img_Filter_Gauss_Vert, Copied_Pic_Is_Correct) {
    int n = 77;
    int m = 3;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);
    std::vector<std::vector<int>> newPic = addBorders(pic, n, m);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < 3; ++k) {
                ASSERT_EQ(pic[i * n + j][k], newPic[(i + 1) * (n + 2) + 1 + j][k]);
            }
        }
    }
}

TEST(Lin_Img_Filter_Gauss_Vert, Cant_Gauss_Filter_With_Bad_Sizes) {
    int n = 43;
    int m = 26;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);

    EXPECT_ANY_THROW(gaussFilter(pic, 0, 0));
    EXPECT_ANY_THROW(gaussFilter(pic, -n, m));
    EXPECT_ANY_THROW(gaussFilter(pic, n, -m));
    EXPECT_ANY_THROW(gaussFilter(pic, -n, -m));
}

TEST(Lin_Img_Filter_Gauss_Vert, Check_Gauss_Filter_1x1_Size) {
    int n = 1;
    int m = 1;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);

    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(pic[0][i], gaussFilter(pic, n, m));
    }
}

TEST(Lin_Img_Filter_Gauss_Vert, Can_Gauss_Filter_With_Big_Sizes) {
    int n = 4533;
    int m = 74125;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);

    ASSERT_NO_THROW(gaussFilter(pic, n, m));
}

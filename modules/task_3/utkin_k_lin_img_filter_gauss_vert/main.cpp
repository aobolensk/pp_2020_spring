// Copyright 2020 Utkin Konstantin
#include <tbb/tbb.h>
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
    ASSERT_NO_THROW(getRandomPic(17, 31));
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

TEST(Lin_Img_Filter_Gauss_Vert, Added_Edges_Are_Correct_5x5) {
    int n = 5;
    int m = 5;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);
    std::vector<std::vector<int>> newPic = addBorders(pic, n, m);

    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(pic[0][i], newPic[0][i]);
        ASSERT_EQ(pic[n - 1][i], newPic[n + 2 - 1][i]);
        ASSERT_EQ(pic[(m - 1) * n][i], newPic[(m + 2 - 1) * (n + 2)][i]);
        ASSERT_EQ(pic[n * m - 1][i], newPic[(n + 2) * (m + 2) - 1][i]);
    }
}

TEST(Lin_Img_Filter_Gauss_Vert, Added_Edges_Are_Correct_6x4) {
    int n = 6;
    int m = 4;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);
    std::vector<std::vector<int>> newPic = addBorders(pic, n, m);

    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(pic[0][i], newPic[0][i]);
        ASSERT_EQ(pic[n - 1][i], newPic[n + 2 - 1][i]);
        ASSERT_EQ(pic[(m - 1) * n][i], newPic[(m + 2 - 1) * (n + 2)][i]);
        ASSERT_EQ(pic[n * m - 1][i], newPic[(n + 2) * (m + 2) - 1][i]);
    }
}

TEST(Lin_Img_Filter_Gauss_Vert, Added_Edges_Are_Correct_4x6) {
    int n = 4;
    int m = 6;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);
    std::vector<std::vector<int>> newPic = addBorders(pic, n, m);

    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(pic[0][i], newPic[0][i]);
        ASSERT_EQ(pic[n - 1][i], newPic[n + 2 - 1][i]);
        ASSERT_EQ(pic[(m - 1) * n][i], newPic[(m + 2 - 1) * (n + 2)][i]);
        ASSERT_EQ(pic[n * m - 1][i], newPic[(n + 2) * (m + 2) - 1][i]);
    }
}

TEST(Lin_Img_Filter_Gauss_Vert, Added_Top_And_Bottom_Borders_Are_Correct_5x5) {
    int n = 5;
    int m = 5;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);
    std::vector<std::vector<int>> newPic = addBorders(pic, n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(pic[i][j], newPic[i + 1][j]);
            ASSERT_EQ(pic[(m - 1) * n + i][j], newPic[(m + 2 - 1) * (n + 2) + 1 + i][j]);
        }
    }
}

TEST(Lin_Img_Filter_Gauss_Vert, Added_Top_And_Bottom_Borders_Are_Correct_6x4) {
    int n = 6;
    int m = 4;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);
    std::vector<std::vector<int>> newPic = addBorders(pic, n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(pic[i][j], newPic[i + 1][j]);
            ASSERT_EQ(pic[(m - 1) * n + i][j], newPic[(m + 2 - 1) * (n + 2) + 1 + i][j]);
        }
    }
}

TEST(Lin_Img_Filter_Gauss_Vert, Added_Top_And_Bottom_Borders_Are_Correct_4x6) {
    int n = 4;
    int m = 6;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);
    std::vector<std::vector<int>> newPic = addBorders(pic, n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(pic[i][j], newPic[i + 1][j]);
            ASSERT_EQ(pic[(m - 1) * n + i][j], newPic[(m + 2 - 1) * (n + 2) + 1 + i][j]);
        }
    }
}

TEST(Lin_Img_Filter_Gauss_Vert, Added_Right_And_Left_Borders_Are_Correct_5x5) {
    int n = 5;
    int m = 5;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);
    std::vector<std::vector<int>> newPic = addBorders(pic, n, m);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(pic[i * n][j], newPic[(i + 1) * (n + 2)][j]);
            ASSERT_EQ(pic[i * n + n - 1][j], newPic[(i + 1) * (n + 2) + n + 2 - 1][j]);
        }
    }
}

TEST(Lin_Img_Filter_Gauss_Vert, Added_Right_And_Left_Borders_Are_Correct_6x4) {
    int n = 6;
    int m = 4;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);
    std::vector<std::vector<int>> newPic = addBorders(pic, n, m);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(pic[i * n][j], newPic[(i + 1) * (n + 2)][j]);
            ASSERT_EQ(pic[i * n + n - 1][j], newPic[(i + 1) * (n + 2) + n + 2 - 1][j]);
        }
    }
}

TEST(Lin_Img_Filter_Gauss_Vert, Added_Right_And_Left_Borders_Are_Correct_4x6) {
    int n = 4;
    int m = 6;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);
    std::vector<std::vector<int>> newPic = addBorders(pic, n, m);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(pic[i * n][j], newPic[(i + 1) * (n + 2)][j]);
            ASSERT_EQ(pic[i * n + n - 1][j], newPic[(i + 1) * (n + 2) + n + 2 - 1][j]);
        }
    }
}

TEST(Lin_Img_Filter_Gauss_Vert, Copied_Pic_Is_Correct_5x5) {
    int n = 5;
    int m = 5;
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

TEST(Lin_Img_Filter_Gauss_Vert, Copied_Pic_Is_Correct_6x4) {
    int n = 6;
    int m = 4;
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

TEST(Lin_Img_Filter_Gauss_Vert, Copied_Pic_Is_Correct_4x6) {
    int n = 4;
    int m = 6;
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
    std::vector<std::vector<int>> newPic = gaussFilter(pic, n, m);

    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(pic[0][i], newPic[0][i]);
    }
}

/*
TEST(Lin_Img_Filter_Gauss_Vert, Can_Gauss_Filter_With_Big_Sizes) {
    int n = 533;
    int m = 412;
    std::vector<std::vector<int>> pic = getRandomPic(n, m);

    ASSERT_NO_THROW(gaussFilter(pic, n, m));
}
*/

int main(int argc, char** argv) {
    tbb::task_scheduler_init init;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

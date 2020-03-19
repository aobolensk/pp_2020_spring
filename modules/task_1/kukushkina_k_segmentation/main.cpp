// Copyright 2020 Kukushkina Ksenia
#include <gtest/gtest.h>
#include "./bin_image_segmentation.h"

TEST(Segmentation, Init) {
    ASSERT_NO_THROW(1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

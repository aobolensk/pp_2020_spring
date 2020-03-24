// Copyright 2020 Gaydaychuk Yury
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "./bitwise_oddeven_sort.h"

TEST(Sequential, Test_Sorted) {
    std::vector<int> vec = {1, 2, 3, 4};
    ASSERT_EQ(true, checkAscending(vec));
}

TEST(Sequential, Test_UnSorted) {
    std::vector<int> vec = {1, 2, 3, 0};
    ASSERT_EQ(false, checkAscending(vec));
}

TEST(Sequential, Test_FirstSort) {
    std::vector<int> vec = {1, 3, 4, 2};
    bitwiseSort(&vec);
    ASSERT_EQ(true, checkAscending(vec));
}

TEST(Sequential, Test_SecondSort) {
    std::vector<int> vec = {4, 3, 2, 1};
    bitwiseSort(&vec);
    ASSERT_EQ(true, checkAscending(vec));
}

TEST(Sequential, Test_ThirdSort) {
    std::vector<int> vec = {4, 3, 3, 2, 1};
    bitwiseSort(&vec);
    std::cout<<"Hello hello\n";
    ASSERT_EQ(true, checkAscending(vec));
}

TEST(Sequential, Test_RawDataCheckAsc) {
    int a[5] = {5, 4, 3, 2, 1};
    int b[5] = {1, 2, 3, 4, 5};
    ASSERT_EQ(true, (!checkAscending(a, 5) && checkAscending(b, 5)));
}

TEST(Sequential, Test_RawDataGetMax) {
    int a[5] = {5, 4, 6, 2, 1};
    ASSERT_EQ(6, getMax(a, 5));
}

TEST(Sequential, Test_RawDataBitwiseSort) {
    int a[5] = {5, 4, 6, 2, 1};
    bitwiseSort(a, 5);
    ASSERT_EQ(true, checkAscending(a, 5));
}

TEST(Sequential, Test_PrintThreadNumber) {
    printThreadNum(30);
    ASSERT_EQ(true, true);
}

TEST(Sequential, Test_PrintThreadArea1) {
    printThreadArea(30, 4);
    ASSERT_EQ(true, true);
}
TEST(Sequential, Test_PrintThreadArea2) {
    printThreadArea(30, 5);
    ASSERT_EQ(true, true);
}
TEST(Sequential, Test_PrintThreadArea3) {
    printThreadArea(11, 4);
    ASSERT_EQ(true, true);
}
TEST(Sequential, Test_PrintThreadArea4) {
    printThreadArea(5, 4);
    ASSERT_EQ(true, true);
}

TEST(Sequential, Test_MergingTest1) {
    int a[] = {1,4,5,7,8,9,2,3,6};
    int specimen[] = {1, 2, 3, 7, 8, 9, 4, 5, 6};
    mergeAndSplit(a, 3, a + 6, 3);
    bool ok = true;
    for(int i = 0; i < 9; i++){
        if(a[i] != specimen[i]){
            ok = false;
            break;
        }
    }
    // for(int i = 0; i < 9; i++){
    //     std::cout<<a[i]<<"\t";
    // }
    ASSERT_EQ(true, ok);
}

TEST(Sequential, Test_MergingTest2) {
    int a[] = {10,4,5,7,8,9,2,3,6};
    int specimen[] = {10, 2, 3, 4, 5, 9, 6, 7, 8};
    mergeAndSplit(a + 1, 4, a + 6, 3);
    bool ok = true;
    for(int i = 0; i < 9; i++){
        if(a[i] != specimen[i]){
            ok = false;
            break;
        }
    }
    // for(int i = 0; i < 9; i++){
    //     std::cout<<a[i]<<"\t";
    // }
    ASSERT_EQ(true, ok);
}

/*
TEST(Sequential, Comparator) {
    NetworkBuilder nb;
    nb.setNetworkSize(32);
    nb.computeNetwork();
    std::cout<<"My comparator\n\n\n\n" << 
    nb.printParallelComp() << nb.printAux() <<"\n^^^^^^^^^^^^^^^^^^\n"
    <<nb.printComp();
    std::cout<<"**************** state   ***************\n" << nb.getState();
    ASSERT_EQ(2*2, 4);
}
*/
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

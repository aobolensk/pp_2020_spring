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

// TEST(Sequential, Test_PrintThreadNumber) {
//     printThreadNum(30);
//     ASSERT_EQ(true, true);
// }

// TEST(Sequential, Test_PrintThreadArea1) {
//     printThreadArea(30, 4);
//     ASSERT_EQ(true, true);
// }
// TEST(Sequential, Test_PrintThreadArea2) {
//     printThreadArea(30, 5);
//     ASSERT_EQ(true, true);
// }
// TEST(Sequential, Test_PrintThreadArea3) {
//     printThreadArea(11, 4);
//     ASSERT_EQ(true, true);
// }
// TEST(Sequential, Test_PrintThreadArea4) {
//     printThreadArea(5, 4);
//     ASSERT_EQ(true, true);
// }
// TEST(Sequential, Test_PrintThreadArea5) {
//     printThreadArea(9, 4);
//     ASSERT_EQ(true, true);
// }

// TEST(Sequential, Test_LocalSorting1) {
//     int a[] = {99,88,77,6,5,4,333,222,111};
// git     ASSERT_EQ(true, parallelBitwiseBatcherSort(a, 9, 4));
// }


// TEST(Sequential, Test_LocalSorting2) {
//     int a[] = {9,8,7,6,5,4,3,2,1};
//     ASSERT_EQ(true, parallelBitwiseBatcherSort(a, 9, 2));
// }

// TEST(Sequential, Test_LocalSorting3) {
//     int a[] = {9,8,7,6,5,4,3,2,1};
//     ASSERT_EQ(true, parallelLocalSort(a, 9, 10));
// }

// TEST(Sequential, Test_GlobalSorting1) {
//     int a[] = {9,8,7,6,5,4,3,2,1};
//     ASSERT_EQ(true, parallelBitwiseBatcherSort(a, 9, 10));
// }

// TEST(Sequential, Test_GlobalSorting2) {
//     int a[] = {9,8,7,6,5,4,3,2,1, 10, 11, 12};
//     ASSERT_EQ(true, parallelBitwiseBatcherSort(a, 12, 2));
// }

// TEST(Sequential, Test_GlobalSorting3) {
//     int a[] = {9,8,7,6,5,4,3,2,1, 10, 11, 12};
//     ASSERT_EQ(true, parallelBitwiseBatcherSort(a, 12, 3));
// }



TEST(Sequential, Test_RandomGlobalSorting1) {
    int size = 100;
    int *a = new int[size];
    std::srand((unsigned) 999);
     
    for(int i = 0; i < size; i++){
        a[i] = ((int)(std::rand()) % 100) + 1;
    }
    bool sortedSuccessfully = parallelBitwiseBatcherSort(a, size, 3);
    for(int i = 0; i < size; i++){
        std::cout<<a[i] << "\t";
    }
    std::cout<<"\n";
    ASSERT_EQ(true, sortedSuccessfully);
}

TEST(Sequential, Test_RandomGlobalSorting2) {
    int size = 10000;
    int *a = new int[size];
    std::srand((unsigned) 999);
     
    for(int i = 0; i < size; i++){
        a[i] = ((int)(std::rand()) % 100) + 1;
    }
    bool sortedSuccessfully = parallelBitwiseBatcherSort(a, size, 5);
    // for(int i = 0; i < size; i++){
    //     std::cout<<a[i] << "\t";
    // }
    // std::cout<<"\n";
    ASSERT_EQ(true, sortedSuccessfully);
}

TEST(Sequential, Test_RandomGlobalSorting3) {
    int size = 100000;
    int *a = new int[size];
    std::srand((unsigned) 999);
     
    for(int i = 0; i < size; i++){
        a[i] = ((int)(std::rand()) % 100) + 1;
    }
    bool sortedSuccessfully = parallelBitwiseBatcherSort(a, size, 4);
    // for(int i = 0; i < size; i++){
    //     std::cout<<a[i] << "\t";
    // }
    // std::cout<<"\n";
    ASSERT_EQ(true, sortedSuccessfully);
}

TEST(Sequential, Test_RandomGlobalSorting4) {
    int size = 3000;
    int *a = new int[size];
    std::srand((unsigned) 999);
     
    for(int i = 0; i < size; i++){
        a[i] = ((int)(std::rand()) % 100) + 1;
    }
    bool sortedSuccessfully = parallelBitwiseBatcherSort(a, size, 50);
    // for(int i = 0; i < size; i++){
    //     std::cout<<a[i] << "\t";
    // }
    // std::cout<<"\n";
    ASSERT_EQ(true, sortedSuccessfully);
}

// TEST(Sequential, Test_RandomGlobalSorting3) {
//     int size = 1000000;
//     int *a = new int[size];
//     std::srand((unsigned) 999);
     
//     for(int i = 0; i < size; i++){
//         a[i] = ((int)(std::rand()) % 100) + 1;
//     }
//     bool sortedSuccessfully = parallelBitwiseBatcherSort(a, size, 6);
//     // for(int i = 0; i < size; i++){
//     //     std::cout<<a[i] << "\t";
//     // }
//     // std::cout<<"\n";
//     ASSERT_EQ(true, sortedSuccessfully);
// }
// TEST(Sequential, Test_MergingTest1) {
//     int a[] = {1,4,5,7,8,9,2,3,6};
//     int specimen[] = {1, 2, 3, 7, 8, 9, 4, 5, 6};
//     mergeAndSplit(a, 3, a + 6, 3);
//     bool ok = true;
//     for(int i = 0; i < 9; i++){
//         if(a[i] != specimen[i]){
//             ok = false;
//             break;
//         }
//     }
//     // for(int i = 0; i < 9; i++){
//     //     std::cout<<a[i]<<"\t";
//     // }
//     ASSERT_EQ(true, ok);
// }

// TEST(Sequential, Test_MergingTest2) {
//     int a[] = {10,4,5,7,8,9,2,3,6};
//     int specimen[] = {10, 2, 3, 4, 5, 9, 6, 7, 8};
//     mergeAndSplit(a + 1, 4, a + 6, 3);
//     bool ok = true;
//     for(int i = 0; i < 9; i++){
//         if(a[i] != specimen[i]){
//             ok = false;
//             break;
//         }
//     }
//     // for(int i = 0; i < 9; i++){
//     //     std::cout<<a[i]<<"\t";
//     // }
//     ASSERT_EQ(true, ok);
// }


// TEST(Sequential, Comparator) {
//     NetworkBuilder nb;
//     nb.setNetworkSize(8);
//     nb.computeNetwork();
//     std::cout<<"My comparator\n\n\n\n" << 
//     nb.printParallelComp();  // <<
//     //  nb.printAux() <<"\n^^^^^^^^^^^^^^^^^^\n"
//     // <<nb.printComp();
//     std::cout<<"**************** state   ***************\n" << nb.getState();
//     ASSERT_EQ(2*2, 4);
// }

// TEST(Sequential, Comparator) {
//     NetworkBuilder nb;
//     nb.setNetworkSize(6);
//     auto parallelArray =  nb.getParallelBlockArray();
//     std::cout<<"My comparator\n\n\n\n";
//     for(auto itBlocks = parallelArray.begin();
//     itBlocks != parallelArray.end();
//     ++itBlocks){
//         for(std::vector<std::pair <int, int> >::iterator itElements = itBlocks->begin();
//         itElements != itBlocks->end();
//         ++itElements){
//             std::cout<<"Pair: " << itElements->first << ", " << itElements->second<<"\n";
//         }
//         std::cout<<"------------\n";
//     } 
//     ASSERT_EQ(2*2, 4);
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

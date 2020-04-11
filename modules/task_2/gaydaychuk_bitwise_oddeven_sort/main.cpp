// Copyright 2020 Gaydaychuk Yury
#include <gtest/gtest.h>
#include <utility>
#include <vector>
#include <list>
#include "./bitwise_oddeven_sort.h"

// TEST(OpenMP, Test_PrintThreadArea1) {
//     printThreadArea(30, 4);
//     ASSERT_EQ(true, true);
// }
// TEST(OpenMP, Test_PrintThreadArea2) {
//     printThreadArea(30, 5);
//     ASSERT_EQ(true, true);
// }
// TEST(OpenMP, Test_PrintThreadArea3) {
//     printThreadArea(11, 4);
//     ASSERT_EQ(true, true);
// }
// TEST(OpenMP, Test_PrintThreadArea4) {
//     printThreadArea(5, 4);
//     ASSERT_EQ(true, true);
// }
// TEST(OpenMP, Test_PrintThreadArea5) {
//     printThreadArea(9, 4);
//     ASSERT_EQ(true, true);
// }

// TEST(OpenMP, Test_LocalSorting1) {
//     int a[] = {99, 88, 77, 6, 5, 4, 333, 222, 111};
//     ASSERT_EQ(true, parallelBitwiseBatcherSort(a, 9, 4));
// }


// TEST(OpenMP, Test_LocalSorting2) {
//     int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
//     ASSERT_EQ(true, parallelBitwiseBatcherSort(a, 9, 2));
// }

// TEST(OpenMP, Test_LocalSorting3) {
//     int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
//     ASSERT_EQ(true, parallelLocalSort(a, 9, 10));
// }

// TEST(OpenMP, Test_GlobalSorting1) {
//     int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
//     ASSERT_EQ(true, parallelBitwiseBatcherSort(a, 9, 10));
// }

// TEST(OpenMP, Test_GlobalSorting2) {
//     int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 10, 11, 12};
//     ASSERT_EQ(true, parallelBitwiseBatcherSort(a, 12, 2));
// }

// TEST(OpenMP, Test_GlobalSorting3) {
//     int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 10, 11, 12};
//     ASSERT_EQ(true, parallelBitwiseBatcherSort(a, 12, 3));
// }



// TEST(OpenMP, Test_RandomGlobalSorting1) {
//     int size = 100;
//     int *a = new int[size];
//     std::srand(static_cast<unsigned>(999));
//     for (int i = 0; i < size; i++) {
//         a[i] = (static_cast<int>(std::rand()) % 100) + 1;
//     }
//     bool sortedSuccessfully = parallelBitwiseBatcherSort(a, size, 3);
//     for (int i = 0; i < size; i++) {
//         printf("%i\t", a[i]);
//     }
//     printf("\n");
//     ASSERT_EQ(true, sortedSuccessfully);
// }

TEST(OpenMP, Test_RandomGlobalSorting2) {
    int size = 10000;
    int *a = new int[size];
    std::srand(static_cast<unsigned>(999));
    for (int i = 0; i < size; i++) {
        a[i] = (static_cast<int>(std::rand()) % 100) + 1;
    }
    bool sortedSuccessfully = parallelBitwiseBatcherSort(a, size, 5);
    // for(int i = 0; i < size; i++){
    //     std::cout<<a[i] << "\t";
    // }
    // std::cout<<"\n";
    ASSERT_EQ(true, sortedSuccessfully);
}

// TEST(OpenMP, Test_RandomGlobalSorting3) {
//     int size = 100000;
//     int *a = new int[size];
//     std::srand(static_cast<unsigned>(999));
//     for (int i = 0; i < size; i++) {
//         a[i] = (static_cast<int>(std::rand()) % 100) + 1;
//     }
//     bool sortedSuccessfully = parallelBitwiseBatcherSort(a, size, 4);
//     // for(int i = 0; i < size; i++){
//     //     std::cout<<a[i] << "\t";
//     // }
//     // std::cout<<"\n";
//     ASSERT_EQ(true, sortedSuccessfully);
// }

// TEST(OpenMP, Test_RandomGlobalSorting4) {
//     int size = 3000;
//     int *a = new int[size];
//     std::srand(static_cast<unsigned>(999));
//     for (int i = 0; i < size; i++) {
//         a[i] = (static_cast<int>(std::rand()) % 100) + 1;
//     }
//     bool sortedSuccessfully = parallelBitwiseBatcherSort(a, size, 50);
//     // for(int i = 0; i < size; i++){
//     //     std::cout<<a[i] << "\t";
//     // }
//     // std::cout<<"\n";
//     ASSERT_EQ(true, sortedSuccessfully);
// }

// TEST(OpenMP, Test_RandomGlobalSorting5) {
//     int size = 1000000;
//     int *a = new int[size];
//     std::srand(static_cast<unsigned>(999));
//     for (int i = 0; i < size; i++) {
//         a[i] = (static_cast<int>(std::rand()) % 100) + 1;
//     }
//     bool sortedSuccessfully = parallelBitwiseBatcherSort(a, size, 40);
//     // for(int i = 0; i < size; i++){
//     //     std::cout<<a[i] << "\t";
//     // }
//     // std::cout<<"\n";
//     ASSERT_EQ(true, sortedSuccessfully);
// }
// TEST(OpenMP, Test_MergingTest1) {
//     int a[] = {1, 4, 5, 7, 8, 9, 2, 3, 6};
//     int specimen[] = {1, 2, 3, 7, 8, 9, 4, 5, 6};
//     mergeAndSplit(a, 3, a + 6, 3);
//     bool ok = true;
//     for (int i = 0; i < 9; i++) {
//         if (a[i] != specimen[i]) {
//             ok = false;
//             break;
//         }
//     }
//     // for(int i = 0; i < 9; i++){
//     //     std::cout<<a[i]<<"\t";
//     // }
//     ASSERT_EQ(true, ok);
// }

// TEST(OpenMP, Test_MergingTest2) {
//     int a[] = {10, 4, 5, 7, 8, 9, 2, 3, 6};
//     int specimen[] = {10, 2, 3, 4, 5, 9, 6, 7, 8};
//     mergeAndSplit(a + 1, 4, a + 6, 3);
//     bool ok = true;
//     for (int i = 0; i < 9; i++) {
//         if (a[i] != specimen[i]) {
//             ok = false;
//             break;
//         }
//     }
//     // for(int i = 0; i < 9; i++){
//     //     std::cout<<a[i]<<"\t";
//     // }
//     ASSERT_EQ(true, ok);
// }


// TEST(OpenMP, Comparator1) {
//     NetworkBuilder nb;
//     nb.setNetworkSize(8);
//     nb.computeNetwork();
//     printf("My comparator\n%s", nb.printParallelComp().c_str());
//     printf("**************** state   ***************%s",
//     nb.getState().c_str());
//     ASSERT_EQ(2*2, 4);
// }

// TEST(OpenMP, Comparator2) {
//     NetworkBuilder nb;
//     nb.setNetworkSize(6);
//     auto parallelArray =  nb.getParallelBlockArray();
//     printf("My comparator\n");
//     for (auto itBlocks = parallelArray.begin();
//     itBlocks != parallelArray.end();
//     ++itBlocks) {
//         for (std::vector<std::pair <int, int> >::iterator itElements =
//         itBlocks->begin();
//         itElements != itBlocks->end();
//         ++itElements) {
//             printf("Pair: %i, %i\n", itElements->first, itElements->second);
//         }
//         printf("------------\n");
//     }
//     ASSERT_EQ(2*2, 4);
// }

// TEST(OpenMP, HPC_gain1) {
//     int size = 100000;
//     int *ompArray = new int[size];
//     int *seqArray = new int[size];
//     std::srand(static_cast<unsigned>(999));
//     for (int i = 0; i < size; i++) {
//         ompArray[i] = (static_cast<int>(std::rand()) % 100) + 1;
//         seqArray[i] = (static_cast<int>(std::rand()) % 100) + 1;
//     }
//     double timeSeq = 0, timeOmp = 0;
//     bool ompCheck = true, seqCheck = true;
//     // bitwiseSort(seqArray, size);
//     bitwiseSortWithTiming(seqArray, size, &timeSeq);
//     seqCheck = checkAscending(seqArray, size);
//     // ompCheck = parallelBitwiseBatcherSort(ompArray, size, 4);
//     ompCheck = parallelBitwiseBatcherSort_for_timing(ompArray, size, 4, &timeOmp);
//     printf("\n batcher_gain = %f", timeSeq / timeOmp);
//     printf("\n timeSeq = %f", timeSeq);
//     printf("\n timeOmp = %f", timeOmp);

//     delete[] ompArray;
//     delete[] seqArray;

//     ASSERT_EQ(true, ompCheck && seqCheck);
// }


// TEST(OpenMP, HPC_gain2) {
//     int size = 1000000;
//     int *ompArray = new int[size];
//     int *seqArray = new int[size];
//     std::srand(static_cast<unsigned>(999));
//     for (int i = 0; i < size; i++) {
//         ompArray[i] = (static_cast<int>(std::rand()) % 100) + 1;
//         seqArray[i] = (static_cast<int>(std::rand()) % 100) + 1;
//     }
//     double timeSeq = 0, timeOmp = 0;
//     bool ompCheck = true, seqCheck = true;
//     // bitwiseSort(seqArray, size);
//     bitwiseSortWithTiming(seqArray, size, &timeSeq);
//     seqCheck = checkAscending(seqArray, size);
//     // ompCheck = parallelBitwiseBatcherSort(ompArray, size, 4);
//     ompCheck = parallelBitwiseBatcherSort(ompArray, size, 4, &timeOmp);
//     printf("\n batcher_gain = %f", timeSeq / timeOmp);
//     printf("\n timeSeq = %f", timeSeq);
//     printf("\n timeOmp = %f", timeOmp);

//     ASSERT_EQ(true, ompCheck && seqCheck);
// }


// TEST(OpenMP, HPC_gain3) {
//     int size = 1000000;
//     int *ompArray = new int[size];
//     int *seqArray = new int[size];
//     std::srand(static_cast<unsigned>(999));
//     for (int i = 0; i < size; i++) {
//         ompArray[i] = (static_cast<int>(std::rand()) % 100) + 1;
//         seqArray[i] = (static_cast<int>(std::rand()) % 100) + 1;
//     }
//     double timeSeq = 0, timeOmp = 0;
//     bool ompCheck = true, seqCheck = true;
//     // bitwiseSort(seqArray, size);
//     bitwiseSortWithTiming(seqArray, size, &timeSeq);
//     seqCheck = checkAscending(seqArray, size);
//     // ompCheck = parallelBitwiseBatcherSort(ompArray, size, 4);
//     ompCheck = parallelBitwiseBatcherSort(ompArray, size, 8, &timeOmp);
//     printf("\n batcher_gain = %f", timeSeq / timeOmp);
//     printf("\n timeSeq = %f", timeSeq);
//     printf("\n timeOmp = %f", timeOmp);

//     ASSERT_EQ(true, ompCheck && seqCheck);
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

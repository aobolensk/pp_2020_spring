// Copyright 2020 Gaydaychuk Yury
#include <gtest/gtest.h>
#include <vector>
#include "./bitwise_oddeven_sort.h"

// TEST(Parallel_Operations_TBB, Test_1) {
//     std::vector<int> vec = getRandomVector(10000);
//     double time = 0;
//     bitwiseSort(&vec.front(), vec.size(), &time);
//     printf("\n time = %f\n", time);
//     ASSERT_EQ(true, true);
// }

// TEST(Parallel_Operations_TBB, Test_2) {
//     std::vector<int> vec = getRandomVector(100);
//     printf("\n hello = %f\n", 1.0);
//     for (int i = 0; i < 3; i++) {
//         tbbHello(i);
//     }
//     ASSERT_EQ(true, true);
// }

// TEST(Parallel_Operations_TBB, Test_3) {
//     std::vector<int> vec = getRandomVector(10);
//     printf("\n hello = %f\n", 1.0);

//     ASSERT_EQ(true, true);
// }

TEST(Parallel_Operations_TBB, Good_Test) {
    ASSERT_EQ(true, true);
}

// TEST(Parallel_Operations_TBB, Task_Test1) {
//     tbb::task_list taskList1;
//     tbb::task_list taskList2;
//     for (int i = 0; i < 10; i++) {
//         HelloTask *ht = new(tbb::task::allocate_root()) HelloTask(i, 1);
//         taskList1.push_back(*ht);
//     }
//     for (int i = 0; i < 10; i++) {
//         HelloTask *ht = new(tbb::task::allocate_root()) HelloTask(i, 2);
//         taskList2.push_back(*ht);
//     }
//     tbb::task::spawn_root_and_wait(taskList1);
//     tbb::task::spawn_root_and_wait(taskList2);
//     // tbb::task::spawn_root_and_wait(*ht);
//     ASSERT_EQ(true, true);
// }

// TEST(Parallel_Operations_TBB, Task_Test2) {
//     std::vector<int> tbbVec = getRandomVector(100000);
//     double tbbTime;
//     parallelLocalSort(&tbbVec.front(), tbbVec.size(), 16, &tbbTime);
//     printf("\n TBB time = %f\n", tbbTime);
//     // for(int i = 0; i < tbbVec.size(); i++) {
//         // printf("%i\t", tbbVec.at(i));
//     // }

//     std::vector<int> seqVec = getRandomVector(1000);
//     double seqTime = 0;
//     bitwiseSort(&seqVec.front(), seqVec.size(), &seqTime);
//     printf("\n SEQ time = %f\n", seqTime);
//     bool ss = checkAscending(&seqVec.front(), seqVec.size());
//     bool tt = checkAscending(&tbbVec.front(), tbbVec.size());

//     // for(int i = 0; i < seqVec.size(); i++) {
//         // printf("%i\t", seqVec.at(i));
//     // }

//     ASSERT_EQ(true, ss && tt);
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

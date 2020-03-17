// Copyright 2020 Gaydaychuk Yury
#ifndef MODULES_TASK_1_GAYDAYCHUK_BITWISE_ODDEVEN_SORT_BITWISE_ODDEVEN_SORT_H_
#define MODULES_TASK_1_GAYDAYCHUK_BITWISE_ODDEVEN_SORT_BITWISE_ODDEVEN_SORT_H_
#include <vector>
#include <string>
#include <list>

class NetworkBuilder{
    std::list<std::vector<int> > auxiliaryNodeSetArray;
    std::list<std::vector<std::pair <int, int> > > parallelBlockArray;
    std::string state;
    int size = 0;
    int twoDegree = 0;
    std::vector<std::pair <int, int> > comparatorArray;
    std::vector<int> indexArray;
    void pseudoSort_2(int lo, int n);
    void bMerge_2(int lo, int n, int r, int level_of_merge);
    void printIndexArray();

    void addComparator(int i, int j);
public:
    void setNetworkSize(int size);
    void computeNetwork();
    std::string printComp();
    std::string NetworkBuilder::printParallelComp();
    std::string NetworkBuilder::printAux();
    std::string NetworkBuilder::getState();
};

bool checkAscending(std::vector<int> vec);
int getMax(std::vector<int> *vec);
void sortByDigit(std::vector<int> *vec, int exp);
void bitwiseSort(std::vector<int> *vec);

#endif  // MODULES_TASK_1_GAYDAYCHUK_BITWISE_ODDEVEN_SORT_BITWISE_ODDEVEN_SORT_H_

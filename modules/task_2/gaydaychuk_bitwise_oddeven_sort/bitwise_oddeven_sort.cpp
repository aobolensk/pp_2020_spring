// Copyright 2020 Gaydaychuk Yury
#include <vector>
#include <list>
#include <string>
#include <ctime>
#include <algorithm>
#include "../../../modules/task_2/gaydaychuk_bitwise_oddeven_sort/bitwise_oddeven_sort.h"

void NetworkBuilder::setNetworkSize(int size){
        this->size = size;
        twoDegree = 1;
        while(twoDegree < size){
            twoDegree *= 2;
        }
        indexArray.clear();
        for(int i = 1; i <= twoDegree; i++){
            indexArray.push_back(i);
        }
        auxiliaryNodeSetArray.clear();
        parallelBlockArray.clear();
    }
void NetworkBuilder::computeNetwork(){
    pseudoSort_2(0, (int)indexArray.size());
}

void NetworkBuilder::pseudoSort_2(int lo, int n)
{
    if (n>1)
    {
    // comparatorArray.push_back(std::pair<int, int>(-1, -1));
        int m=n/2;
        pseudoSort_2(lo, m);
        pseudoSort_2(lo+m, m);
            // comparatorArray.push_back(std::pair<int, int>(-4, -4));

        bMerge_2(lo, n, 1, 1);
    }
}

void NetworkBuilder::bMerge_2(int lo, int n, int r, int level_of_merge)
{
    // comparatorArray.push_back(std::pair<int, int>(-2, -r));

    // comparatorArray.push_back(std::pair<int, int>(-222, -level_of_merge));
    // lo is the starting position and
    // n is the length of the piece to be merged,
    // r is the distance of the elements to be compared
    int m=r*2;
    if (m<n)
    {
            // comparatorArray.push_back(std::pair<int, int>(-2, -r));

        bMerge_2(lo, n, m, level_of_merge + 1);      // even subsequence
        bMerge_2(lo+r, n, m, level_of_merge + 1);    // odd subsequence
        for (int i=lo+r; i+r<lo+n; i+=m){
            // comparatorArray.push_back(std::pair<int, int>(-4, -r));
            // comparatorArray.push_back(std::pair<int, int>(0, -level_of_merge));

            comparatorArray.push_back(std::pair<int, int>(indexArray[i], indexArray[i + r]));
            addComparatorAnother(indexArray[i], indexArray[i + r]);
        }
    }
    else{
        // comparatorArray.push_back(std::pair<int, int>(-3, -r));
        // comparatorArray.push_back(std::pair<int, int>(0, -level_of_merge));


        addComparatorAnother(indexArray[lo], indexArray[lo + r]);
        comparatorArray.push_back(std::pair<int, int>(indexArray[lo], indexArray[lo + r]));
    }
}

void NetworkBuilder::addComparator(int i, int j){
    if(auxiliaryNodeSetArray.empty()){
        std::vector<int> newBlockNodeSet;

        newBlockNodeSet.push_back(i);
        newBlockNodeSet.push_back(j);
        auxiliaryNodeSetArray.push_back(newBlockNodeSet);

        std::vector<std::pair <int, int> > newBlock;
        newBlock.push_back(std::pair<int, int>(i, j));
        parallelBlockArray.push_back(newBlock);
    }
    else{
        bool pairAndSetIntersectionFound = false;
        std::list<std::vector<std::pair <int, int> > >::iterator parallelBlocksIterator = parallelBlockArray.begin();
        for(
            std::list<std::vector<int > >::iterator itBlocks = auxiliaryNodeSetArray.begin(); 
            itBlocks != auxiliaryNodeSetArray.end(); 
            ++itBlocks) {
            pairAndSetIntersectionFound = false;
            auto currBlock = *itBlocks;
            for(std::vector<int> ::iterator itInBlock = currBlock.begin(); itInBlock != currBlock.end(); ++itInBlock){
                if(i == *itInBlock || j == *itInBlock){
                    pairAndSetIntersectionFound = true;
                    break;
                }
            };
            if(pairAndSetIntersectionFound == true){
                  if((itBlocks != auxiliaryNodeSetArray.end()) && (next(itBlocks) == auxiliaryNodeSetArray.end())){
                    auxiliaryNodeSetArray.push_back({i, j});
                    parallelBlockArray.push_back(std::vector<std::pair <int, int> >({std::pair <int, int>(i, j)}));
                    break;
                }
                else{
                    continue;
                }
            }
            else{
                parallelBlocksIterator->push_back(std::pair<int, int>(i, j));
                itBlocks->push_back(i);
                itBlocks->push_back(j);
                break;
            }
            ++parallelBlocksIterator;
        };
    }
}

void NetworkBuilder::addComparatorAnother(int i, int j){
    if(auxiliaryNodeSetArray.empty()){
        std::vector<int> newBlockNodeSet;

        newBlockNodeSet.push_back(i);
        newBlockNodeSet.push_back(j);
        auxiliaryNodeSetArray.push_back(newBlockNodeSet);

        std::vector<std::pair <int, int> > newBlock;
        newBlock.push_back(std::pair<int, int>(i, j));
        parallelBlockArray.push_back(newBlock);
    }
    else{
        bool pairAndSetIntersectionFound = false;
        std::list<std::vector<std::pair <int, int> > >::reverse_iterator  parallelBlocksIterator = parallelBlockArray.rbegin();
        for(
            std::list<std::vector<int > >::reverse_iterator  itBlocks = auxiliaryNodeSetArray.rbegin(); 
            itBlocks != auxiliaryNodeSetArray.rend(); 
            ++itBlocks) {
            pairAndSetIntersectionFound = false;
            auto currBlock = *itBlocks;
            for(std::vector<int> ::iterator itInBlock = currBlock.begin(); itInBlock != currBlock.end(); ++itInBlock){
                if(i == *itInBlock || j == *itInBlock){
                    pairAndSetIntersectionFound = true;
                    break;
                }
            };
            if(pairAndSetIntersectionFound == true){
                if(itBlocks == auxiliaryNodeSetArray.rbegin()){
                    auxiliaryNodeSetArray.push_back({i, j});
                    parallelBlockArray.push_back(std::vector<std::pair <int, int> >({std::pair <int, int>(i, j)}));
                    break;
                }
                else{
                    --itBlocks;
                    --parallelBlocksIterator;
                    parallelBlocksIterator->push_back(std::pair<int, int>(i, j));
                    itBlocks->push_back(i);
                    itBlocks->push_back(j);
                    break;
                }
            }
            else{
                if(next(itBlocks) != auxiliaryNodeSetArray.rend()){
                    ++parallelBlocksIterator;
                    continue;
                }
                else{
                    parallelBlocksIterator->push_back(std::pair<int, int>(i, j));
                    itBlocks->push_back(i);
                    itBlocks->push_back(j);
                }
            }
            ++parallelBlocksIterator;
        };
    }
}

std::string NetworkBuilder::printComp(){
    std::string result;
    for(std::vector<std::pair<int, int>>::iterator it = comparatorArray.begin(); it != comparatorArray.end(); ++it) {
        if(it->first < 0){
            result = result + "\t\t";
        }
        if(it->first == 0){
            result = result + "\t\t\t\t";
        }
        
        result = result + "Pair: (" + std::to_string(it->first) + " ," + std::to_string(it->second) + ")\n";
    }
    result = result + "\nsize = " + std::to_string(parallelBlockArray.size()) + "\n";
    return result;
};

std::string NetworkBuilder::getState(){ return state; }

std::string NetworkBuilder::printParallelComp(){
    std::string result;
    for(std::list<std::vector<std::pair <int, int> > >::iterator blockIt = parallelBlockArray.begin(); blockIt != parallelBlockArray.end(); ++blockIt) {
        result = result + "\n ------------ \n";
        for(std::vector<std::pair <int, int> >::iterator it = blockIt->begin(); it != blockIt->end(); ++it) {
            result = result + "Pair: (" + std::to_string(it->first) + " ," + std::to_string(it->second) + ")\n";
        }
    }
    return result;
}

std::string NetworkBuilder::printAux(){
    std::string result = "\n ================ \n ==============\n";
    for(std::list<std::vector<int> >::iterator blockIt = auxiliaryNodeSetArray.begin(); blockIt != auxiliaryNodeSetArray.end(); ++blockIt) {
        result = result + "\n ------------ \n";
        for(std::vector<int>::iterator it = blockIt->begin(); it != blockIt->end(); ++it) {
            result = result + "Aux: " + std::to_string(*it) + "\n";
        }
    }
    return result;
}

void NetworkBuilder::printIndexArray(){
    state = state + "\nIndexArray = ";
    for(std::vector<int>::iterator it = indexArray.begin(); it != indexArray.end(); ++it) {
        state = state + ", " + std::to_string(*it);
    }
    state = state + "\n";
}

bool checkAscending(std::vector<int> vec) {
    return std::is_sorted(std::begin(vec), std::end(vec));
}

int getMax(std::vector<int> *vec) {
    int n = vec->size();
    int max = vec->at(0);
    for (int i = 1; i < n; i++) {
        if (vec->at(i) > max) {
            max = vec->at(i);
        }
    }
    return max;
}

void sortByDigit(std::vector<int> *vec, int digit) {
    int n = vec->size();
    std::vector<int> res(n);
    int i, count[10] = {0};
    for (i = 0; i < n; i++) {
        count[(vec->at(i) / digit) % 10]++;
    }
    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    for (i = n - 1; i >= 0; i--) {
        res[count[(vec->at(i) / digit) % 10] - 1] = vec->at(i);
        count[(vec->at(i) / digit) % 10]--;
    }
    for (i = 0; i < n; i++) {
        vec->at(i) = res[i];
    }
}

void bitwiseSort(std::vector<int> *vec) {
    int max = getMax(vec);
    for (int digit = 1; max / digit > 0; digit *= 10)
        sortByDigit(vec, digit);
}



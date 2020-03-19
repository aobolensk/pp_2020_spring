#include "multi_matrix.h"
#include <random>



SparseMatrixCCS::SparseMatrixCCS(int _n, int _m, int _noneZero)
{
    n = _n;
    m = _m;
    noneZero = _noneZero;
    
    value.resize(noneZero);
    row_index.resize(noneZero);
    col_offsets.resize(noneZero+1);
}

SparseMatrixCCS::SparseMatrixCCS(const SparseMatrixCCS& obj){
    n = obj.n;
    m = obj.m;
    noneZero = obj.noneZero;
    value = obj.value;
    row_index = obj.row_index;
    col_offsets = obj.col_offsets;
}

// SparseMatrixCCS randomGenerateMatrix(int _n, int _m){
//     std::mt19937 gen;
//     gen.seed(time(0));
// }




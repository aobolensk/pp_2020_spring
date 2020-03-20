#include "multi_matrix.h"
#include <random>
#include <iostream>



SparseMatrixCCS::SparseMatrixCCS(int _m, int _n, int _noneZero)
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

mtxComplex SparseMatrixCCS::randomGenerateMatrix(double sparseness){
    mtxComplex vec(m);
    for ( int i = 0 ; i < m; i++ )
    vec[i].resize(n);
    std::mt19937 genReal{std::random_device()()};
    std::mt19937 genImag{std::random_device()()};
    std::mt19937 gen{std::random_device()()};
    std::uniform_int_distribution<int> randReal (0,10), randImag(0,10);
    std::uniform_real_distribution<> probability{0,1};

    for(int i=0;i<m;i++){
        for(int j=0; j<n; j++){
            if(probability(gen)>=sparseness){
                vec[i][j].real(randReal(genReal));
                vec[i][j].imag(randImag(genImag));
            }
        }
    }
   return vec;
}

//Debug
void SparseMatrixCCS::Print(const mtxComplex& mt){
    for(int i=0;i<m;i++){
        for(int j=0; j<n; j++)
        std::cout<< mt[i][j] << " \n"[j == n-1];
    }
}







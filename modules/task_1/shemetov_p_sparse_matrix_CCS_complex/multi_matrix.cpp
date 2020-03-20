#include "multi_matrix.h"
#include <random>
#include <iostream>
#include <chrono>



SparseMatrixCCS::SparseMatrixCCS(size_t _m, size_t _n)
{
    n = _n;
    m = _m;
    // noneZero = _noneZero;
    
    // value.resize(noneZero);
    // row_index.resize(noneZero);
    // col_offsets.resize(noneZero+1);
}

SparseMatrixCCS::SparseMatrixCCS(const SparseMatrixCCS& obj){
    n = obj.n;
    m = obj.m;
    noneZero = obj.noneZero;
    value = obj.value;
    row_index = obj.row_index;
    col_offsets = obj.col_offsets;
}

mtxComplex randomGenerateMatrix(size_t m,size_t n, 
                                                double sparseness){
    mtxComplex vec(m);
    for ( size_t i = 0 ; i < m; i++ )
    vec[i].resize(n);
    std::mt19937 genReal{std::random_device()()};
    std::mt19937 genImag{std::random_device()()};
    std::mt19937 gen{std::random_device()()};
    std::uniform_int_distribution<int> randReal (0,10), randImag(0,10);
    std::uniform_real_distribution<> probability{0,1};

    for(size_t i=0;i<m;i++){
        for(size_t j=0; j<n; j++){
            if(probability(gen)>=sparseness){
                vec[i][j].real(randReal(genReal));
                vec[i][j].imag(randImag(genImag));
            }
        }
    }
   return vec;
}

mtxComplex TransposeMatrix(const mtxComplex& mt){
    
    mtxComplex transpose(mt[0].size(),std::vector<std::complex<double>>());
    
     for (size_t i = 0; i < mt.size(); i++) {
        for (size_t j = 0; j < mt[i].size(); j++) {
            transpose[j].push_back(mt[i][j]);
        }
    }
    return transpose; 
}

SparseMatrixCCS::SparseMatrixCCS(const mtxComplex& mt){
    mtxComplex vec = TransposeMatrix(mt);
    m = vec.size();
    n = vec[0].size();
    col_offsets.reserve(mt.size()+1);
    col_offsets.push_back(0);
    for(size_t i = 0; i<m;i++){
        for(size_t j=0; j<n; j++){
            if(vec[i][j].imag()!=0 || vec[i][j].real()!=0){
            value.push_back(vec[i][j]);
            row_index.push_back(j);
            }
        }
    }

}

//Debug
void SparseMatrixCCS::Print(const mtxComplex& mt){
    for(size_t i=0;i<m;i++){
        for(size_t j=0; j<n; j++)
        std::cout<< mt[i][j] << " \n"[j == n-1];
    }
}

void SparseMatrixCCS::TransposePrint(const mtxComplex& mt){
    for(size_t i=0;i<n;i++){
        for(size_t j=0; j<m; j++)
        std::cout<< mt[i][j] << " \n"[j == m-1];
    }
}

void SparseMatrixCCS::PrintCCS(){
    std::cout << std::endl;
    std::cout << "--------------" << std::endl;
    for (size_t i = 0; i < value.size(); i++)
    {
        std::cout << value[i] << "|";
    }
    std::cout << std::endl;
    std::cout << "--------------" << std::endl;
    for (size_t i = 0; i < row_index.size(); i++)
    {
        std::cout << row_index[i] << "|";
    }
    
}








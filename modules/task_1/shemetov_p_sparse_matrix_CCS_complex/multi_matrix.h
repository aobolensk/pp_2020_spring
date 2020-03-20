#ifndef MODULES_TASK_1_SHEMETOV_P_SPARSE_MATRIX_CSS_COMPLEX_MULTI_MATRIX_H_
#define MODULES_TASK_1_SHEMETOV_P_SPARSE_MATRIX_CSS_COMPLEX_MULTI_MATRIX_H_
#include <vector>
#include <complex>

typedef std::vector<std::vector<std::complex<double>>> mtxComplex;

class SparseMatrixCCS
{
private:
    std::vector<std::complex<int>> value;
    std::vector<int> row_index;
    std::vector<int> col_offsets;
    size_t n, m;
    int noneZero;
public:
    SparseMatrixCCS(size_t m, size_t n);
    SparseMatrixCCS(const mtxComplex&);
    SparseMatrixCCS(const SparseMatrixCCS& obj);
    void Print(const mtxComplex&);
    void PrintCCS();
    void TransposePrint(const mtxComplex&);
    
};

mtxComplex randomGenerateMatrix(size_t m,size_t n,double sparseness);
mtxComplex TransposeMatrix(const mtxComplex&);


#endif // MODULES_TASK_1_SHEMETOV_P_SPARSE_MATRIX_CSS_COMPLEX_MULTI_MATRIX_H_
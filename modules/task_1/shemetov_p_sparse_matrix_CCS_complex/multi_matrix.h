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
    int n, m, noneZero;
public:
    SparseMatrixCCS(int m, int n, int noneZero);
    SparseMatrixCCS(const mtxComplex&);
    SparseMatrixCCS(const SparseMatrixCCS& obj);
    mtxComplex randomGenerateMatrix(double sparseness);
    mtxComplex TransposeMatrix(const mtxComplex&);
    void Print(const mtxComplex&);
    
};



#endif // MODULES_TASK_1_SHEMETOV_P_SPARSE_MATRIX_CSS_COMPLEX_MULTI_MATRIX_H_
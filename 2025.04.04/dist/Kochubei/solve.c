#include "solve.h"
#include <stdio.h>

void init_array(int* r, int n)
{
    for (int i=0; i<n; i++)
    {
        r[i]=i;
    }
}

matrix_status gauss_step(restrict mat A, restrict mat B, int n, int k, int* r, double norm)
{
    int max_pos=find_max(A, n, k);
    if (max_pos!=k)
    {
        swap_columns(A, n, k, max_pos);
        swap_int(r+k, r+max_pos);
    }
    if (equals_zero(A[k*n+k], norm))
    {
        return FAILED;
    }
    B[k]=B[k]/A[k*n+k];
    divide_row(A, n, k);
    #pragma omp parallel for
    for (int i=k+1; i<n; i++)
    {
        double el=A[i*n+k];
        B[i]=B[i]-el*B[k];
        subtract_row(A, n, i, k);
    }
    return SOLVED;
}

matrix_status gauss(restrict mat A, restrict mat B, restrict mat X, int n, int* r)
{
    double norm=matrix_norm(A,n);
    init_array(r,n);
    for (int i=0; i<n; i++)
    {
        if (gauss_step(A, B, n, i, r, norm)==FAILED) return FAILED;
    }
    for (int i=n-1; i>=0; i--)
    {
        double sum=0;
        for (int j=n-1; j>i; j--)
        {
            sum=sum+A[i*n+j]*X[r[j]];
        }
        X[r[i]]=B[i]-sum;
    }
    return SOLVED;
}

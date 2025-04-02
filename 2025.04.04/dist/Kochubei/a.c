#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "solve.h"

#define task 10

int main(int argc, char** argv)
{
    int n=0;
    int p=0;
    int k=0;
    char* name;
    mat A;
    mat B;
    mat X;
    int* r;
    matrix_status result;
    double r1=0, r2=0;
    double t=0;
    if (argc<4)
    {
        printf("Usage: %s n p k [name if k=0]\n", argv[0]);
        return -1;
    }
    if (sscanf(argv[1], "%d", &n)!=1 || sscanf(argv[2], "%d", &p)!=1 || sscanf(argv[3], "%d", &k)!=1)
    {
        printf("Usage: %s n p k [name if k=0]\n", argv[0]);
        return -1;
    }
    A=(mat)malloc(n*n*sizeof(double));
    if (!A)
    {
        printf("Not enough memory\n");
        return -1;
    }
    if (k==0)
    {
        io_status ret;
        if (argc<5)
        {
            printf("Usage: %s n p k [name if k=0]\n", argv[0]);
            free(A);
            return -1;
        }
        name=argv[4];
        ret=read_matrix(A,n,n,name);
        if (ret!=SUCCESS)
        {
            printf("Read error\n");
            free(A);
            return -1;
        }
    }
    else
    {
        init_matrix(A,n,n,k);
    }
    B=(mat)malloc(n*sizeof(double));
    if (!B)
    {
        printf("Not enough memory\n");
        free(A);
        return -1;
    }
    X=(mat)malloc(n*sizeof(double));
    if (!X)
    {
        printf("Not enough memory\n");
        free(A);
        free(B);
        return -1;
    }
    r=(int*)malloc(n*sizeof(int));
    if (!r)
    {
        printf("Not enough memory\n");
        free(A);
        free(B);
        free(X);
        return -1;
    }
    init_vector(A,B,n);
    printf("Matrix:\n");
    print_matrix(A,n,n,p);
    printf("Vector:\n");
    print_matrix(B,n,1,p);
    t=omp_get_wtime();
    result=gauss(A,B,X,n,r);
    t=(omp_get_wtime()-t);
    if (result==FAILED)
    {
        printf("Matrix is singular.\n");
        free(A);
        free(B);
        free(X);
        free(r);
        return 0;
    }
    printf("Solution:\n");
    print_matrix(X,n,1,p);
    if (k==0)
    {
        io_status ret;
        name=argv[4];
        ret=read_matrix(A,n,n,name);
        if (ret!=SUCCESS)
        {
            printf("Read error\n");
            free(A);
            free(B);
            free(X);
            free(r);
            return -1;
        }
    }
    else
    {
        init_matrix(A,n,n,k);
    }
    init_vector(A,B,n);
    r1=R1(A,X,B,n);
    r2=R2(X,n);
    printf ("%s : Task = %d Res1 = %e Res2 = %e Elapsed = %.2f K = %d N = %d\n", argv[0], task, r1, r2, t, k, n);
    free(A);
    free(B);
    free(X);
    free(r);
    return 0;
}

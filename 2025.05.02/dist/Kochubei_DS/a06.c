#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "add.h"
#include "solve.h"

int main(int argc, char** argv)
{
    int m=0;
    double a=0;
    double b=0;
    double e=0;
    int M=0;
    int k=0;
    int res=0;
    int count=0;
    double x=0;
    double t=0;
    double* arr;
    double (*f[7])(double) = {f0,f1,f2,f3,f4,f5,f6};
    if (argc!=7)
    {
        printf("Usage: %s m[>0] a b e[>0] M[>0] k[0-6]\n", argv[0]);
        return -1;
    }
    if (sscanf(argv[1], "%d", &m)!=1 || sscanf(argv[2], "%lf", &a)!=1 || sscanf(argv[3], "%lf", &b)!=1 || sscanf(argv[4], "%lf", &e)!=1 || sscanf(argv[5], "%d", &M)!=1 || sscanf(argv[6], "%d", &k)!=1)
    {
        printf("Usage: %s m[>0] a b e[>0] M[>0] k[0-6]\n", argv[0]);
        return -1;
    }
    if (k<0 || k>6)
    {
        printf("Usage: %s m[>0] a b e[>0] M[>0] k[0-6]\n", argv[0]);
        return -1;
    }
    if (m<0)
    {
        printf("Usage: %s m[>0] a b e[>0] M[>0] k[0-6]\n", argv[0]);
        return -1;
    }
    e=fabs(e);
    if (b<a)
    {
        double tmp=a;
        a=b;
        b=tmp;
    }
    arr=(double*)malloc(3*(m+1)*sizeof(double));
    t=clock();
    res=solve6(f[k],m, arr, a, b, e, M, &x);
    t=(clock()-t)/CLOCKS_PER_SEC;
    count=get_count();
    if (res<0)
    {
        printf ("%s : Task = %d NOT FOUND Count = %d T = %.2f\n", argv[0], 6, count, t);
    }
    else
    {
        printf ("%s : Task = %d X = %e Res = %e Its = %d Count = %d T = %.2f\n", argv[0], 6, x, f[k](x), res, count, t);
    }
    free(arr);
    return 0;
}

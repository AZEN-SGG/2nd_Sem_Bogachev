#include <stdio.h>
#include <time.h>
#include <math.h>
#include "add.h"
#include "solve.h"

int main(int argc, char** argv)
{
    double x0=0;
    double e=0;
    int M=0;
    int k=0;
    int count=0;
    double x=0;
    double t=0;
    int res=0;
    double (*f[7])(double) = {f0,f1,f2,f3,f4,f5,f6};
    double (*d[7])(double) = {d0,d1,d2,d3,d4,d5,d6};
    if (argc!=5)
    {
        printf("Usage: %s x0 e[>0] M[>0] k[0-6]\n", argv[0]);
        return -1;
    }
    if (sscanf(argv[1], "%lf", &x0)!=1 || sscanf(argv[2], "%lf", &e)!=1 || sscanf(argv[3], "%d", &M)!=1 || sscanf(argv[4], "%d", &k)!=1)
    {
        printf("Usage: %s x0 e[>0] M[>0] k[0-6]\n", argv[0]);
        return -1;
    }
    if (k<0 || k>6)
    {
        printf("Usage: %s x0 e[>0] M[>0] k[0-6]\n", argv[0]);
        return -1;
    }
    e=fabs(e);
    t=clock();
    res=solve2(f[k], d[k], x0, e, M, &x);
    t=(clock()-t)/CLOCKS_PER_SEC;
    count=get_count();
    if (res<0)
    {
        printf ("%s : Task = %d NOT FOUND Count = %d T = %.2f\n", argv[0], 2, count, t);
    }
    else
    {
        printf ("%s : Task = %d X = %e Res = %e Its = %d Count = %d T = %.2f\n", argv[0], 2, x, f[k](x), res, count, t);
    }
    return 0;
}

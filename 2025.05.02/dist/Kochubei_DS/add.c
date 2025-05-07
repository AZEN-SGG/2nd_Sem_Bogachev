#include <math.h>
#include <stdio.h>
#include <string.h>
#include "add.h"

static unsigned int count=0;

inline unsigned int get_count(void)
{
    return count;
}

double f0(double x)
{
    (void)x;
    count++;
    return 1;
}

double f1(double x)
{
    count++;
    return x-1e100;
}

double f2(double x)
{
    count++;
    return 4-x*x;
}

double f3(double x)
{
    count++;
    return x*x*x+3*x*x+16;
}

double f4(double x)
{
    count++;
    return 3-2*x*x-x*x*x*x;
}

double f5(double x)
{
    count++;
    return sqrt(fabs(x)+1)-2;
}

double f6(double x)
{
    count++;
    return sqrt(sqrt(fabs(x)+1)+1)-2;
}

double d0(double x)
{
    (void)x;
    return 0;
}

double d1(double x)
{
    (void)x;
    return 1;
}

double d2(double x)
{
    return -2*x;
}

double d3(double x)
{
    return 3*x*x+6*x;
}

double d4(double x)
{
    return -4*x-4*x*x*x;
}

double d5(double x)
{
    if (x>0)
    {
        return 1.0/2.0/sqrt(x+1);
    }
    else if (eq(x,0))
    {
        return 0;
    }
    else
    {
        return -1.0/2.0/sqrt(1-x);
    }
}

double d6(double x)
{
    if (x>0)
    {
        double r=sqrt(x+1);
        return 1.0/4.0/sqrt(r+1)/r;
    }
    else if (eq(x,0))
    {
        return 0;
    }
    else
    {
        double r=sqrt(1-x);
        return 1.0/4.0/sqrt(r+1)/r;
    }
}

inline int eq(double a, double b)
{
    long long int A=0;
    long long int B=0;
    memcpy(&A, &a, sizeof(a));
    memcpy(&B, &b, sizeof(b));
    return (A==B);
}

inline int sign_eq(double a, double b)
{
    return (a>0 && b>0) || (a<0 && b<0);
}
inline int newton(double x, int n, double* a, double* b, double* ans)
{
    double res=0;
    for (int j=0; j<n; j++)
    {
        for (int i=n-1; i>j; i--)
        {
            double dif=a[i]-a[i-j-1];
            if (eq(dif,0))
            {
                return -1;
            }
            b[i]=(b[i]-b[i - 1])/dif;
        }
    }
    for (int i=n-1; i>=0; i--)
    {
        res=res*(x-a[i])+b[i];
    }
    *ans=res;
    return 0;
}

inline void parabola(double x1, double x2, double x3, double y1, double y2, double y3, double* A, double* B, double* C)
{
    double V=(x1-x2)*(x1-x3)*(x2-x3);
    if (eq(x1,x2) || eq(x2,x3) || eq(x3,x1))
    {
        *A=0;
        *B=0;
        *C=0;
        return;
    }
    *A=(y1*x2-y1*x3-y2*x1+y3*x1+y2*x3-y3*x2)/V;
    *B=(x2*x2*y3-x3*x3*y2-x1*x1*y3+x3*x3*y1+x1*x1*y2-x2*x2*y1)/V;
    *C=(y1*x2*x3*(x2-x3)-y2*x1*x3*(x1-x3)+y3*x1*x2*(x1-x2))/V;
    return;
}

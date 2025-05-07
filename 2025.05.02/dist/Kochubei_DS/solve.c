#include <math.h>
#include <stdio.h>
#include "add.h"
#include "solve.h"

inline int solve1(double (*f) (double), double a, double b, double e, int M, double* x)
{
    double y1=0;
    double y2=0;
    if (eq(a,b))
    {
        if (f(a)<e)
        {
            *x=a;
            return 0;
        }
        else
        {
            return -1;
        }
    }
    y1=f(a);
    y2=f(b);
    for (int i=0; i<M; i++)
    {
        if (sign_eq(y1, y2))
        {
            return -1;
        }
        else
        {
            double c=(a+b)/2;
            double y3=f(c);
            if (fabs(y3)<e)
            {
                *x=c;
                return i;
            }
            if (sign_eq(y1, y3))
            {
                a=c;
                y1=y3;
            }
            else
            {
                b=c;
                y2=y3;
            }
        }
    }
    return -1;
}

inline int solve2(double (*f) (double), double (*d) (double), double x0, double e, int M, double* x)
{
    double y=f(x0);
    for (int i=0; i<M; i++)
    {
        double y_new=0;
        if (fabs(y)<e)
        {
            *x=x0;
            return i;
        }
        if (eq(d(x0), 0))
        {
            return -1;
        }
        x0=x0-y/d(x0);
        y_new=f(x0);
        /*/
        if (fabs(y_new)>fabs(y))
        {
            return -1;
        }
        /*/
        y=y_new;
    }
    return -1;
}

inline int solve3(double (*f) (double), double a, double b, double e, int M, double* x)
{
    double y1=0;
    double y2=0;
    if (eq(a,b))
    {
        if (f(a)<e)
        {
            *x=a;
            return 0;
        }
        else
        {
            return -1;
        }
    }
    y1=f(a);
    y2=f(b);
    if (sign_eq(y1, y2))
    {
        return -1;
    }
    for (int i=0; i<M; i++)
    {
        double c=0;
        double y3=0;
        if (eq(y1,y2))
        {
            return -1;
        }
        c=a-(b-a)*y1/(y2-y1);
        y3=f(c);
        if (fabs(y3)<e)
        {
            *x=c;
            return i;
        }
        if (sign_eq(y1, y3))
        {
            a=c;
            y1=y3;
        }
        else
        {
            b=c;
            y2=y3;
        }
    }
    return -1;
}

inline int solve4(double (*f) (double), double a, double b, double e, int M, double* x)
{
    double y1=0;
    double y2=0;
    if (eq(a,b))
    {
        if (f(a)<e)
        {
            *x=a;
            return 0;
        }
        else
        {
            return -1;
        }
    }
    y1=f(a);
    y2=f(b);
    for (int i=0; i<M; i++)
    {
        double c=0;
        double y3=0;
        c=a-(b-a)*y1/(y2-y1);
        y3=f(c);
        if (fabs(y3)<e)
        {
            *x=c;
            return i;
        }
        if (c>a && c>b)
        {
            a=b;
            y1=y2;
            b=c;
            y2=y3;
        }
        else if (c<a && c<b)
        {
            b=a;
            y2=y1;
            a=c;
            y1=y3;
        }
        else
        {
            if (fabs(a-c)<=fabs(b-c))
            {
                a=c;
                y1=y3;
            }
            else
            {
                b=c;
                y2=y3;
            }
        }
    }
    return -1;
}

inline int solve5(double (*f) (double), double a, double b, double e, int M, double* x)
{
    double y1=0;
    double y2=0;
    if (eq(a,b))
    {
        if (f(a)<e)
        {
            *x=a;
            return 0;
        }
        else
        {
            return -1;
        }
    }
    y1=f(a);
    y2=f(b);
    for (int i=0; i<M; i++)
    {
        double c=0;
        double y3=0;
        double X[3];
        double Y[3];
        double p=0;
        double y_p=0;
        c=(a+b)/2;
        y3=f(c);
        X[0]=y1;
        X[1]=y3;
        X[2]=y2;
        Y[0]=a;
        Y[1]=c;
        Y[2]=b;
        if (newton(0, 3, X, Y, &p)==-1)
        {
            return -1;
        }
        y_p=f(p);
        if (fabs(y_p)<e)
        {
            *x=p;
            return i;
        }
        if (p<a)
        {
            b=a;
            y2=y1;
            a=p;
            y1=y_p;
        }
        else if (p>=a && p<=c)
        {
            a=p;
            y1=y_p;
            b=c;
            y2=y3;
        }
        else if (p<=c && p<=b)
        {
            a=c;
            y1=y3;
            b=p;
            y2=y_p;
        }
        else
        {
            a=b;
            y1=y2;
            b=p;
            y2=y_p;
        }
    }
    return -1;
}

inline int solve6(double (*f) (double), int m, double* d, double a, double b, double e, int M, double *x)
{
    double y1=0;
    double y2=0;
    if (m<1) return -1;
    if (eq(a,b))
    {
        if (f(a)<e)
        {
            *x=a;
            return 0;
        }
        else
        {
            return -1;
        }
    }
    y1=f(a);
    y2=f(b);
    for (int i=0; i<M; i++)
    {
        double p=0;
        double y_p=0;
        double h=(b-a)/m;
        d[0]=a;
        d[m+1]=y1;
        d[2*(m+1)]=y1;
        d[m]=b;
        d[m+(m+1)]=y2;
        d[m+2*(m+1)]=y2;
        for (int j=1; j<m; j++)
        {
            double t=f(a+j*h);
            d[j]=a+j*h;
            d[j+(m+1)]=t;
            d[j+2*(m+1)]=t;
        }
        if (newton(0, m+1, d+(m+1), d, &p)==-1)
        {
            return -1;
        }
        y_p=f(p);
        for (int j=0; j<m+1; j++)
        {
            d[j+(m+1)]=d[j+2*(m+1)];
        }
        if (fabs(y_p)<e)
        {
            *x=p;
            return i;
        }
        if (p<a)
        {
            b=a;
            y2=y1;
            a=p;
            y1=y_p;
        }
        else if (p>b)
        {
            a=b;
            y1=y2;
            b=p;
            y2=y_p;
        }
        else
        {
            int pos=(p-a)/h;
            a=a+pos*h;
            y1=d[pos+(m+1)];
            b=a+(pos+1)*h;
            y2=d[pos+1+(m+1)];
        }
    }
    return -1;
}

inline int solve7(double (*f) (double), double x0, double e, int M, double* x)
{
    double last_x0=1e300;
    for (int i=0; i<M; i++)
    {
        double y=f(x0);
        if (fabs(y-x0)>fabs(x0-last_x0))
        {
            return -1;
        }
        if (fabs(y-x0)<e)
        {
            *x=x0;
            return i;
        }
        last_x0=x0;
        x0=y;
    }
    return -1;
}

inline int solve8(double (*f) (double), double a, double b, double e, int M, double* x)
{
    double y1=0;
    double y2=0;
    if (eq(a,b))
    {
        *x=a;
        return 0;
    }
    y2=f(a);
    for (int i=0; i<M; i++)
    {
        double h=(b-a)/16;
        int was_break=0;
        for (int j=0; j<15; j++)
        {
            y1=y2;
            y2=f(a+(j+1)*h);
            if (y2<y1)
            {
                b=(a+j*h);
                a=(a+(j+1)*h);
                was_break=1;
                break;
            }
        }
        if (was_break==0)
        {
            a=a+15*h;
        }
        if (fabs(b-a)<e)
        {
            *x=(b+a)/2;
            return i;
        }
    }
    return -1;
}

inline int solve9(double (*f) (double), double a, double b, double e, int M, double* x)
{
    double phi=(1+sqrt(5))/2;
    double y1=0;
    double y2=0;
    double x1=b-(b-a)/phi;
    double x2=a+(b-a)/phi;
    if (eq(a,b))
    {
        *x=a;
        return 0;
    }
    y1=f(x1);
    y2=f(x2);
    for (int i=0; i<M; i++)
    {
        if (y1<=y2)
        {
            a=x1;
            y1=y2;
            x1=b-(b-a)/phi;
            x2=a+(b-a)/phi;
            y2=f(x2);
        }
        else
        {
            b=x2;
            y2=y1;
            x1=b-(b-a)/phi;
            x2=a+(b-a)/phi;
            y1=f(x1);
        }
        if (b-a<e)
        {
            *x=(b+a)/2;
            return i;
        }
    }
    return -1;
}

inline int solve10(double (*f) (double), double a, double b, double e, int M, double *x)
{
    double y1=0;
    double y2=0;
    if (eq(a,b))
    {
        *x=a;
        return 0;
    }
    y1=f(a);
    y2=f(b);
    for (int i=0; i<M; i++)
    {
        double c=(a+b)/2;
        double y_c=f(c);
        double A=0;
        double B=0;
        double C=0;
        double x_max=0;
        double y_max=0;
        parabola(a,c,b,y1,y_c,y2, &A, &B, &C);
        if (A>=0)
        {
            return -1;
        }
        x_max=-B/2/A;
        y_max=f(x_max);
        if (x_max<a)
        {
            b=a;
            y2=y1;
            a=x_max;
            y1=y_max;
        }
        else if (x_max>a && x_max<c)
        {
            a=x_max;
            y1=y_max;
            b=c;
            y2=y_c;
        }
        else if (x_max>c && x_max<b)
        {
            a=c;
            y1=y_c;
            b=x_max;
            y2=y_max;
        }
        else if (x_max>b)
        {
            a=b;
            y1=y2;
            b=x_max;
            y2=y_max;
        }
        else
        {
            *x=x_max;
            return i;
        }
        if (b-a<e)
        {
            *x=x_max;
            return i;
        }
    }
    return -1;
}


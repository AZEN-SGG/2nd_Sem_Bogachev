#include <stdio.h>
#include <math.h>
#include "add.h"

#define eps 1e-16

// ���������� ��������, ��������� � ������ �� ������ �����
// �����: �� ������ � fmax � �.�, � �� ����� �� �� ������ � FPE...
int max(int a, int b)
{
    if (a>=b) return a;
    else return b;
}

int min(int a, int b)
{
    if (a<=b) return a;
    else return b;
}

int abs(int a)
{
    if (a>=0) return 0;
    else return -a;
}

// ���������� �������� �������
// k - ����� �������, n, m - ������� �������, i, j - ������� ��������
// �������� k=5 � k=6 �� ������� � �������� � ����� ������������� ��� �������� ���������� ������
double f(int k, int n, int m, int i, int j)
{
    i=i+1;
    j=j+1;
    if (k==1)
    {
        return max(n,m)-max(i,j)+1;
    }
    else if (k==2)
    {
        return max(i,j);
    }
    else if (k==3)
    {
        return abs(i-j);
    }
    // ������� ���������
    else if (k==4)
    {
        return 1.0/(i+j-1);
    }

    // ������������ � ������� ���������

    // ������� ������
    else if (k==5)
    {
        return (min(i,j))*1.0/max(i,j);
    }
    // ������� ����������
    else if (k==6)
    {
        if (j==1 || j%i==0) return 1;
        else return 0;
    }
    else return 0;
}

// ������ �������
// A - ������ ���������� ��� �������, n, m - ������� �������, name - ��� �����
io_status read_matrix(restrict mat A, int n, int m, char* name)
{
    FILE* f=fopen(name, "rt");
    if (!f) return ERROR_OPEN;
    for (int i=0; i<n*m; i++)
    {
        if (fscanf(f, "%lf", &A[i])!=1)
        {
            fclose(f);
            return ERROR_READ;
        }
    }
    fclose(f);
    return SUCCESS;
}

// ����� �������
// A - �������, n, m - ������� �������, p - ������������ ���������� ����� � �������� ��� ������
void print_matrix(restrict mat A, int n, int m, int p)
{
    for (int i=0; i<n && i<p; i++)
    {
        for (int j=0; j<m && j<p; j++)
        {
            printf("%10.3e ", A[i*m+j]);
        }
        printf("\n");
    }
}

// ������������� �������
// A - �������, n, m - ������� �������, k - ����� �������
// ��� ������� k �� main ������ ���������� ������� read_matrix()
void init_matrix(restrict mat A, int n, int m, int k)
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<m; j++)
        {
            A[i*m+j]=f(k, n, m, i, j);
        }
    }
}

// ������������� �������
// A - ����������� ������� ������� n*n, V - ������, n - ����� �������
void init_vector(restrict mat A, restrict mat V, int n)
{
    for (int i=0; i<n; i++)
    {
        double sum=0;
        for (int k=0; k<=(n-1)/2; k++)
        {
            sum=sum+A[i*n+2*k];
        }
        V[i]=sum;
    }
}

// ����� �������
// V - ������, n - ����� �������
// ��������� ����� ��� ����� ������� ��������� �������
double vector_norm(restrict mat V, int n)
{
    double sum=0;
    for (int i=0; i<n; i++)
    {
        sum=sum+fabs(V[i]);
    }
    return sum;
}

// ���������� ������� (r1)
// A - �������, X - ������ �������� ���������� �������, B - ��������� �������, n - ������ ������� � ����� �������
// �����: ����� ������ ������ ������ B
double R1(restrict mat A, restrict mat X, restrict mat B, int n)
{
    double norm1=0;
    double norm2=0;
    norm2=vector_norm(B, n);
    if (0<=norm2 && norm2<=0) return 1e300;
    for (int i=0; i<n; i++)
    {
        double sum=0;
        for (int j=0; j<n; j++)
        {
            sum=sum+A[i*n+j]*X[j];
        }
        B[i]=sum-B[i];
    }
    norm1=vector_norm(B,n);
    return norm1/norm2;
}

// ���������� r2
// X - ������, n - ��� �����
double R2(restrict mat X, int n)
{
    double sum1=0;
    double sum2=0;
    if (n<=0) return 0;
    for (int i=1; i<=n; i++)
    {
        sum1=sum1+fabs(X[i-1]-(i&1));
    }
    for (int i=1; i<=n; i++)
    {
        sum2=sum2+(i&1);
    }
    return sum1/sum2;
}

// �������� �� ��������� �������� ������� ����, ������������ �� �����
// x - ������� �������, norm - ����� �������
int equals_zero(double x, double norm)
{
    if (fabs(x)<eps*norm) return 1;
    else return 0;
}

// ����� ������� A_inf
// A - ���������� �������, n - �� ������
double matrix_norm(restrict mat A, int n)
{
    double norm=0;
    for (int i=0; i<n; i++)
    {
        double sum=0;
        for (int j=0; j<n; j++)
        {
            sum=sum+fabs(A[i*n+j]);
        }
        if (sum>norm) norm=sum;
    }
    return norm;
}

// ������������ �������������� ��� ������ ������
// A - ���������� �������, n - �� ������, k - ����� ������
// �����: ��������������, ��� ������� A[k*n+k] ��� ������ ���������
// �����: ��������������, ��� ��������, ������� ����� A[k*n+k], ��� �������� ��������
void divide_row(restrict mat A, int n, int k)
{
    double el=A[k*n+k];
    for (int i=k+1; i<n; i++)
    {
        A[k*n+i]=A[k*n+i]/el;
    }
    A[k*n+k]=1;
}

int find_max(restrict mat A, int n, int k)
{
    int res=k;
    double mx=fabs(A[k*n+k]);
    for (int i=k+1; i<n; i++)
    {
        double tmp=fabs(A[k*n+i]);
        if (tmp>mx)
        {
            res=i;
            mx=tmp;
        }
    }
    return res;
}

void subtract_row(restrict mat A, int n, int a, int b)
{
    double el=A[a*n+b];
    for (int i=b+1; i<n; i++)
    {
        A[a*n+i]=A[a*n+i]-A[b*n+i]*el;
    }
    A[a*n+b]=0;
}

void swap(double* a, double* b)
{
    double tmp=*a;
    *a=*b;
    *b=tmp;
}

void swap_int(int* a, int* b)
{
    int tmp=*a;
    *a=*b;
    *b=tmp;
}

void swap_columns(restrict mat A, int n, int a, int b)
{
    for (int i=0; i<n; i++)
    {
        swap(A+i*n+a, A+i*n+b);
    }
}

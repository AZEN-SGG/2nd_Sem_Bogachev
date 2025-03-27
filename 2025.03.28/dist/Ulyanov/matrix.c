#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io_status.h"
#include "matrix.h"

void multmatvec(double* a, double* x1, double* x2, int n)
  {
  int i, j;
  double sum;
  for (i = 0; i < n; i++)
      {
      sum = 0;
      for (j = 0; j < n; j++)
          sum += a[i * n+ j] * x1[j];
      x2[i] = sum;
      }
  }

double scalp(double* a, double* b, int n)
  {
  int i;
  double mult = 0;
  for (i = 0; i < n; i++) mult += a[i] * b[i];
  return mult;
  }
  
double count_task1(double* a, double* x, double r1, int n)
  {
  int i, j;
  double mltd_el_x, sum, modsum1 = 0, modsum2 = 0;
  for (i = 0; i < n; i++)
      {
      sum = 0;
      for (j = 0; j < n; j++) sum += a[i * n + j] * x[j];
      mltd_el_x = r1 * x[i];
      modsum1 += fabs(sum - mltd_el_x);
      modsum2 += fabs(mltd_el_x);
      }
  return modsum1 / modsum2;
  }
  
double count_r1(double* a, double* b, double* x, int n)
  {
  int i, j;
  double el_b, sum, modsum1 = 0, modsum2 = 0;
  for (i = 0; i < n; i++)
      {
      sum = 0;
      for (j = 0; j < n; j++) sum += a[i * n + j] * x[j];
      el_b = b[i];
      modsum1 = fabs(sum - el_b);
      modsum2 = fabs(el_b);
      }
  return modsum1 / modsum2;
  }
  
double count_r2(double* x, int n)
  {
  int i;
  double modsum = 0;
  int ost, sum = 0;
  for (i = 0; i < n; i++)
      {
      ost = (i + 1) % 2;
      modsum += fabs(x[i] - ost);
      sum += ost;
      }
  return modsum / sum;
  }
  
void vecdiff(double* a, double* b, int n)
  {
  int i;
  for (i = 0; i < n; i++) a[i] -= b[i];
  }
  
void vecmult(double* a, double lambda, int n)
  {
  int i;
  for (i = 0; i < n; i++) a[i] = lambda * a[i];
  }
  
void veccpy(double* a, double* b, int n)
  {
  int i;
  for (i = 0; i < n; i++) a[i] = b[i];
  }
  
void veccomb(double lambda, double* a, double myu, double* b, int n)
  {
  int i;
  for (i = 0; i < n; i++) a[i] = lambda * a[i] + myu * b[i];
  }
  
int equal(double a, double b)
  {
  if (fabs(a - b) <= EPS * fmax(fabs(a), fabs(b))) return 1;
  return 0;
  }
  
void multdiagvec(double* a, double* x1, double* x2, int n)
  {
  int i;
  for (i = 0; i < n; i++) x2[i] = x1[i] * a[i * n + i];
  }
  
void deldiagvec(double* a, double* x1, double* x2, int n)
  {
  int i;
  for (i = 0; i < n; i++) x2[i] = x1[i] / a[i * n + i];
  }
  
void deldiagmultvec(double* a, double* x1, double* x2, double tau, int n)
  {
  int i;
  for (i = 0; i < n; i++) x2[i] = tau * (x1[i] / a[i * n + i]);
  }
  
io_status checkdiag(double* a, int n)
  {
  int i;
  for (i = 0; i < n; i++) 
      {
      if (equal(a[i * n + i], 0)) return ERROR_READ;
      }
  return SUCCESS;
  }
  
void slaudown(double* a, double* x, double* r, int n)
  {
  int i, j;
  double sum;
  for (i = 0; i < n; i++)
      {
      sum = x[i];
      for (j = 0; j < i; j++) sum -= a[i * n + j] * r[j];
      r[i] = sum / a[i * n + i]; 
      }
  }
  
void slauup(double* a, double* x, double* r, int n)
  {
  int i, j;
  double sum;
  for (i = n - 1; i >= 0; i--)
      {
      sum = x[i];
      for (j = i + 1; j < n; j++) sum -= a[i * n + j] * r[j];
      r[i] = sum / a[i * n + i]; 
      }
  }


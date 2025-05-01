#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "io_status.h"
#include "functions.h"
#include "comparison.h"

int solve6(int, double, double, double, int, double*, double*, double*, double*, double (*)(double));
io_status build(double*, double*, int);
double comp(double*, double*, int);
void swap_max(double, double, double*, double*, double*, int);

int main(int argc, char* argv[])
  {
  int task = 6;
  double a, b, eps;
  int maxit, k, m;
  double t;
  double (*f)(double);
  double (*func[])(double) = {f0, f1, f2, f3, f4, f5, f6};
  double x = 0, fx;
  double* z;
  double* y;
  double* s;
  int it, c;
  if (!(argc == 7 && sscanf(argv[1], "%d", &m) == 1 && sscanf(argv[2], "%lf", &a) == 1 && sscanf(argv[3], "%lf", &b) == 1 && sscanf(argv[4], "%le", &eps) == 1 && sscanf(argv[5], "%d", &maxit) == 1 && sscanf(argv[6], "%d", &k) == 1 && k >= 0 && k <= 6))
      {
      printf("Usage: %s m a b eps M k\n", argv[0]);
      return -2;
      }
  z = (double*) malloc((m + 1) * sizeof(double));
  y = (double*) malloc((m + 1) * sizeof(double));
  s = (double*) malloc((m + 1) * sizeof(double));
  if (!z || !y || !s)
      {
      if (z) free(z);
      if (y) free(y);
      if (s) free(s);
      }
  f = func[k];
  t = clock();
  it = solve6(m, a, b, eps, maxit, &x, z, y, s, f);
  t = (clock() - t) / CLOCKS_PER_SEC;
  c = get_count();
  free(z);
  free(y);
  free(s);
  if (it < 0)
      {
      printf("%s : Task = %d NOT FOUND Count = %d T = %.2f\n", argv[0], task, c, t);
      return -1;
      }
  fx = (*f)(x);
  printf("%s : Task = %d X = %e Res = %e Its = %d Count = %d T = %.2f\n", argv[0], task, x, fx, it, c, t);
  return 0;
  }
  
int solve6(int m, double a, double b, double eps, int maxit, double* x, double* z, double* y, double* s, double (*f)(double))
  {
  int i;
  int it;
  double tmp, xi, fxi;
  io_status res;
  for (i = 0; i <= m; i++)
      {
      tmp = a + (b - a) * i / m;
      z[i] = tmp;
      y[i] = (*f)(tmp);
      s[i] = tmp;
      }
  for (it = 0; it < maxit; it++)
      {
      res = build(z, y, m);
      if (res != SUCCESS) return -1;
      xi = comp(z, y, m);
      fxi = (*f)(xi);
      if (fabs(fxi) < eps * fabs(xi)) {*x = xi; break;}
      swap_max(xi, fxi, z, y, s, m);
      }
  if (it >= maxit) return -1;
  return it;
  }
  
io_status build(double* z, double* y, int m)
  {
  int i, j;
  double el_i, el_prev;
  for (j = 0; j <= m; j++)
      {
      for (i = m; i > j; i--)
          {
          el_i = y[i];
          el_prev = y[i - j - 1];
          if (equal(el_i, el_prev)) return ERROR_FUNCTION;
          z[i] = (z[i] - z[i - 1]) / (el_i - el_prev);
          }
      }
  return SUCCESS;
  }
  
double comp(double* z, double* y, int m)
  {
  int i;
  double sum = 0;
  for (i = m; i >= 0; i--) sum = z[i] - y[i] * sum;
  return sum;
  }
  
void swap_max(double xi, double fxi, double* z, double* y, double* s, int m)
  {
  int i, maxind = 0;
  double max = fabs(y[0]), mod_yi;
  for (i = 0; i <= m; i++)
      {
      z[i] = s[i];
      mod_yi = fabs(y[i]);
      if (mod_yi > max) {max = mod_yi; maxind = i;}
      }
  z[maxind] = xi;
  y[maxind] = fxi;
  s[maxind] = xi;
  }


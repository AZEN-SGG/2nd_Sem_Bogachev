#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "io_status.h"
#include "functions.h"
#include "comparison.h"

int solve9(double, double, double, int, double*, double (*)(double));

int main(int argc, char* argv[])
  {
  int task = 9;
  double a, b, eps;
  int maxit, k;
  double t;
  double (*f)(double);
  double (*func[])(double) = {f0, f1, f2, f3, f4, f5, f6};
  double x = 0, fx;
  int it, c;
  if (!(argc == 6 && sscanf(argv[1], "%lf", &a) == 1 && sscanf(argv[2], "%lf", &b) == 1 && sscanf(argv[3], "%le", &eps) == 1 && sscanf(argv[4], "%d", &maxit) == 1 && sscanf(argv[5], "%d", &k) == 1 && k >= 0 && k <= 6))
      {
      printf("Usage: %s a b eps M k\n", argv[0]);
      return -2;
      }
  f = func[k];
  t = clock();
  it = solve9(a, b, eps, maxit, &x, f);
  t = (clock() - t) / CLOCKS_PER_SEC;
  c = get_count();
  if (it < 0)
      {
      printf("%s : Task = %d NOT FOUND Count = %d T = %.2f\n", argv[0], task, c, t);
      return -1;
      }
  fx = (*f)(x);
  printf("%s : Task = %d X = %e Res = %e Its = %d Count = %d T = %.2f\n", argv[0], task, x, fx, it, c, t);
  return 0;
  }
  
int solve9(double a, double b, double eps, int maxit, double* x, double (*f)(double))
  {
  int it;
  double phi = 2 / (1 + sqrt(5));
  double x1 = b - (b - a) * phi, x2 = a + (b - a) * phi;
  double fx1 = (*f)(x1), fx2 = (*f)(x2);
  for (it = 0; it < maxit; it++)
      {
      if (fx1 < fx2) 
          {
          a = x1; 
          x1 = x2; fx1 = fx2;
          x2 = a + (b - a) * phi; fx2 = (*f)(x2);
          }
      else 
          {
          b = x2;
          x2 = x1; fx2 = fx1;
          x1 = b - (b - a) * phi; fx1 = (*f)(x1);
          }
      if (fabs(a - b) < eps) {*x = x1; break;}
      }
  if (it >= maxit) return -1;
  return it;
  }

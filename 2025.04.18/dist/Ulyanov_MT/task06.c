#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "io_status.h"
#include "array.h"
#include "functions.h"

double solve6(double, double);

int main(int argc, char* argv[])
  {
  int task = 6;
  double x, eps;
  double res;
  double diff;
  double t;
  if (!((argc == 3) && sscanf(argv[1], "%le", &x) == 1 && sscanf(argv[2], "%le", &eps) == 1))
      {
      printf("Usage: %s x0 eps\n", argv[0]);
      return 1;
      }
  t = clock();
  res = solve6(x, eps);
  t = (clock() - t) / CLOCKS_PER_SEC;
  diff = fabs(res - cos(x));
  printf ("%s : Task = %d Result = %e Residual = %e Elapsed = %.2f\n", argv[0], task, res, diff, t);
  return 0;
  }
  
double solve6(double x, double eps)
  {
  int i = 1, sign = 1, flag = 1;
  double el, res = 0;
  x = fmod(x, 2 * M_PI);
  if (x > M_PI)
      {
      x = x - M_PI;
      sign *= -1;
      }
  if (x < -M_PI)
      {
      x = x + M_PI;
      sign *= -1;
      }
  if (x > M_PI / 2)
      {
      x = M_PI - x;
      sign *= -1;
      }
  if (x < -M_PI / 2) 
      {
      x = -M_PI - x;
      sign *= -1;
      }
  if (x > M_PI / 4)
      {
      x = M_PI / 2 - x;
      flag = 0;
      }
  if (x < -M_PI / 4)
      {
      x = -M_PI / 2 - x;
      sign *= -1;
      flag = 0;
      }
  if (flag == 1)
      {
      el = 1;
      while (fabs(el) >= eps)
          {
          res += el;
          el *= -1 * ((x * x) / (4 * i * i - 2 * i));
          i++;
          }
      }
  else
      {
      el = x;
      while (fabs(el) >= eps)
          {
          res += el;
          el *= -1 * ((x * x) / (4 * i * i + 2 * i));
          i++;
          }
      }
  return sign * res;
  }

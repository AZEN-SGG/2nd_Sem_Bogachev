#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "io_status.h"
#include "functions.h"
#include "comparison.h"

static int count = 0;

double f0(double x)
  {
  count++;
  (void) x;
  return 1;
  }

double f1(double x)
  {
  count++;
  return x - 1e100;
  }

double f2(double x)
  {
  count++;
  return 4 - x * x;
  }
  
double f3(double x)
  {
  count++;
  return x * x * x + 3 * x * x + 16;
  }
  
double f4(double x)
  {
  count++;
  return 3 - 2 * x * x - x * x * x * x;
  }
  
double f5(double x)
  {
  count++;
  return sqrt(fabs(x) + 1) - 2;
  }
  
double f6(double x)
  {
  count++;
  return sqrt(sqrt(fabs(x) + 1) + 1) - 2;
  }
  
double der_f0(double x)
  {
  (void) x;
  return 0;
  }

double der_f1(double x)
  {
  (void) x;
  return 1;
  }
  
double der_f2(double x)
  {
  return -2 * x;
  }
  
double der_f3(double x)
  {
  return 3 * x * x + 6 * x;
  }
  
double der_f4(double x)
  {
  return -4 * x - 4 * x * x * x;
  }
  
double der_f5(double x)
  {
  if (x > 0) return 1 / (2 * sqrt(x + 1));
  if (x < 0) return -1 / (2 * sqrt(-x + 1));
  return 0;
  }
  
double der_f6(double x)
  {
  if (x > 0)
      {
      double sqrtp = sqrt(x + 1);
      return 1 / (4 * sqrt(x * sqrtp + sqrtp + x + 1));
      }
  if (x < 0)
      {
      double sqrtn = sqrt(-x + 1);
      return -1 / (4 * sqrt(-x * sqrtn + sqrtn - x + 1));
      }
  return 0;
  }
int get_count(void)
  {
  return count;
  }

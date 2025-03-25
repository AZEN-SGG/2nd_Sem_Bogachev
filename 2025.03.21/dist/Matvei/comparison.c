#include <math.h>
#include "comparison.h"

int equal(double a, double b)
  {
  if (fabs(a - b) <= EPS * fmax(fabs(a), fabs(b))) return 1;
  return 0;
  }

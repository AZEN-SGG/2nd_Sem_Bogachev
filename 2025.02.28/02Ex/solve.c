#include "solve.h"

#include "array.h"

void t2_solve(char **arr_a, char **arr_b, char **arr_c, int n, int m, int (*cmp)(const char *, const char *))
{
 int i, j, k, cntr, len = n + m; // cntr - contrast
 for (i = 0, j = 0, k = 0; k < len; ++k)
 {
  if (i >= n) 
  {
   arr_c[k] = arr_b[j++];
  } else if (j >= m)
  {
   arr_c[k] = arr_a[i++];
  } else 
  {
   cntr = cmp(arr_a[i], arr_b[j]);
   if (cntr <= 0) arr_c[k] = arr_a[i++];
   else arr_c[k] = arr_b[j++];
  } 
 }
}


#include "solve.h"

void t8_solve(char **a, char **b, int n, int (*cmp)(const char *, const char *))
{
	int i = 2, j, margin;
	do {
		int hf_i = i/2;
		for (j = 0; j < n; j += i)
		{
			if (n < j+i)
			{
				margin = n-(j+hf_i);
				if (margin <= 0) break;
			} else margin = hf_i;

			unite(a+j, a+(j+hf_i), b, hf_i, margin, cmp);
			for (int k = 0; k < hf_i+margin; k++) a[j+k] = b[k];
		}

		i *= 2;
	} while (i < n*2);
}

void unite(char **arr_a, char **arr_b, char **arr_c, int n, int m, int (*cmp)(const char *, const char *))
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


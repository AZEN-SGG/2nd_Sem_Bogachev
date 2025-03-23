#include "solve.h"

int t6_solve(char ** a, int n, char *s) {
	int i, j, k;
	for (i = 0, j = 0, k = 0; i < n; ++i) {
		if (strpbrk(a[i], s)) {
			if (k > 1)
			{
				for (int x = 2; x < k; x++) free(a[i - x]);
				a[j++] = a[i - 1];
			}
			
			if (i != j) 
			{
				a[j] = a[i];
			}
			j++;
			k = 0;
		} else {
			if (k == 0)  {
				if (i != j)
					a[j] = a[i];
				j++;
			}
			k++;
		}
	}
	
	if (k > 1)
	{
		for (int x = 2; x < k; x++) free(a[i - x]);
		a[j++] = a[i - 1];
	}	

	for (i = j; i < n; ++i) a[i] = 0;

	return j;
}


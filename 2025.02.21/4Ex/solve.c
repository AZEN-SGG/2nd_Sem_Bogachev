#include "solve.h"

int t4_solve(char ** a, int n, char *s) {
	size_t len_s = strlen(s);
	int i, j, k;
	for (i = 0, j = 0, k = 0; i < n; ++i) {
		if (len_s <= strlen(a[i])) {
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
			} else {
				free(a[i]);
			}
			k++;
		}
	}

	for (i = j; i < n; ++i) a[i] = 0;

	return j;
}

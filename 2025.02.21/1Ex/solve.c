#include "solve.h"

int t1_solve(char ** a, int n, char *s) {
	int i, j;
	for (i = 0, j = 0; i < n; ++i) {
		if (strcmp(a[i], s) >= 0) 
		{
			if (i != j) a[j] = a[i];
			j++;
		} else free(a[i]);
	}

	for (i = j; i < n; ++i) a[i] = 0;

	return j;
}

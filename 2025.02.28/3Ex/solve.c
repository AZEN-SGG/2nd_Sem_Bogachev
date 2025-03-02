#include "solve.h"

int t3_solve(char **a, int n, char *x, int (*cmp)(const char *, const char *)) {
    int i = 0, j = n-1;
    char *temp;

    while (1) 
    {
        for (; i < n; i++) if (cmp(a[i], x) >= 0) break;
        for (; j >= 0; j--) if (cmp(a[j], x) < 0) break;

        if (i >= j) break;
	temp = a[i];
	a[i] = a[j];
	a[j] = temp;

	i++, j--;
    }

    return i;
}

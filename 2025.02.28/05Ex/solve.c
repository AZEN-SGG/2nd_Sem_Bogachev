#include "solve.h"

void t5_solve(char **a, int n, int (*cmp)(const char *, const char *))
{
	char *temp;
	size_t size_c = sizeof(char);
	int i, min;
	for (i=0; i < n-1; ++i)
	{
		min = minimum(a+i*size_c, n-i, cmp)+i;
		temp = a[min];
		a[min] = a[i];
		a[i] = temp;
	}
}

int minimum(char **a, int n, int (*cmp)(const char *, const char *))
{
	int i, min=0;
	if (n <= 0) return 0;
	for (i = 1; i < n; ++i)
	{
		if (cmp(a[min], a[i]) > 0) min = i;
	}

	return min;
}


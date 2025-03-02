#include "solve.h"

void t6_solve(char **a, int n, int (*cmp)(const char *, const char *))
{
	int i;
	for (i = 1; i < n; ++i)	append(a, i+1, a[i], find(a, i, a[i], cmp));
}

int find(char **arr, int n, char *a, int (*cmp)(const char *, const char *))
{
	int i;
	for (i=0; i<n; ++i) if (cmp(a, arr[i]) < 0) break;
	return i;
}

void append(char **arr, int n, char *a, int index)
{
	for (int i = n-1; i > index; --i) arr[i] = arr[i-1];
	arr[index] = a;
}


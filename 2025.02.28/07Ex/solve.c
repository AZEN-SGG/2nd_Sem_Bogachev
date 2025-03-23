#include "solve.h"

void t7_solve(char **a, int n, int (*cmp)(const char *, const char *))
{
	int i;
	for (i = 1; i < n; ++i)	append(a, i+1, a[i], find(a, i, a[i], cmp));
}

int find(char **a, int n, char *x, int (*cmp)(const char *, const char *)) {
	int avg = (n + (-1)*(n%2)) / 2;
	int comp;

	if (n == 0) return 0;
	
	comp = cmp(x, a[avg]);
	if (comp < 0) return find(a, avg, x, cmp);
	if (comp > 0) return avg+1 + find(a+(avg+1), n-(avg+1), x, cmp);
	else return avg;
}

void append(char **arr, int n, char *a, int index)
{
	for (int i = n-1; i > index; --i) arr[i] = arr[i-1];
	arr[index] = a;
}

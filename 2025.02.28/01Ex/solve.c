#include "solve.h"

int t1_solve(char **a, int n, char *x, int (*cmp)(const char *, const char *)) {
	int avg = (n + (-1)*(n%2)) / 2;
	int comp;

	if (n == 0) return 0;
	
	comp = cmp(x, a[avg]);
	if (comp < 0) return t1_solve(a, avg, x, cmp);
	if (comp > 0) return avg+1 + t1_solve(a+avg+1, n-(avg+1), x, cmp);
	else return avg;
}


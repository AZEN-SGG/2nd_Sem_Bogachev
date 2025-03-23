#include "solve.h"

void t9_solve(char **a, int n, int (*cmp)(const char *, const char *))
{
	while (n > 1)
	{
		int is_edge = 0, ind_x = findIndex(a, n, a[n/2], cmp);
		if (ind_x < n-ind_x)
		{
			if (ind_x == 0) is_edge = 1;
			t9_solve(a, ind_x, cmp);
			a += ind_x + is_edge;
			n -= ind_x + is_edge;
		} else 
		{
			t9_solve(a+ind_x, n-ind_x, cmp);
			n = ind_x;
		}
	}
}

int findIndex(char **a, int n, char *x, int (*cmp)(const char *, const char *))
{	
    int i = 0, j = n-1;
    char *temp;

    while (1) 
    {
        for (; i < n; i++) if (cmp(a[i], x) >= 0) break;
        for (; j >= 0; j--) if (cmp(a[j], x) <= 0) break;

        if (i >= j) break;
	temp = a[i];
	a[i] = a[j];
	a[j] = temp;

	i++, j--;
    }

    return i;
}

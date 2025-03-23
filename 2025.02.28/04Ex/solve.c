#include "solve.h"

void t4_solve(char **a, int n, int (*cmp)(const char *, const char *))
{
	char *temp;
	int i, j;
	for (i=n; i > 0; --i)
	{
		for (j=0; j < i-1; ++j) 
		{
			if (cmp(a[j], a[j+1]) >= 0)
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;				
			}
		}
	}
}


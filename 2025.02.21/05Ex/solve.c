#include "solve.h"

int t5_solve(char ** a, int n, char *s) {
	int i, j, k;
	for (i = 0, j = 0, k = 0; i < n; ++i) {
		if (!check(a[i], s)) {
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


bool check(char *a, char *s) {
	int i;
	int len_s = (int)strlen(s);
	int len_a = (int)strlen(a);
	int diff = len_a - len_s;

	if (diff < 0) return false;

	for (i = (len_a - 1); i > (diff - 1); --i) {
		if (a[i] != s[i - diff]) return false;
	}

	return true;
}

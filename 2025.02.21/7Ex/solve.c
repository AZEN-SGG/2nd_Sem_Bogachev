#include "solve.h"

int t7_solve(char ** a, int n, char *s) {
	bool fl_lst = false, fl_cur = false, fl_nxt = false;
	int i, j;

	if (strcmp(a[0], s) < 0) fl_cur = true;

	for (i = 1, j = 0; i < n; ++i) {
		if (strcmp(a[i], s) < 0) {
			fl_lst = true;
			fl_nxt = true;
		}

		if (!fl_lst) {
			if (j != (i-1)) {
				a[j] = a[i-1];
			}
			j++;
		} else {
			free(a[i-1]);
		}
		
		fl_lst = fl_cur;
		fl_cur = fl_nxt;
		fl_nxt = false;
	}

	if (fl_lst)
	{
		free(a[i-1]);
	} else {
		a[j++] = a[i-1];
	}

	for (i = j; i < n; ++i) a[i] = 0;

	return j;
}

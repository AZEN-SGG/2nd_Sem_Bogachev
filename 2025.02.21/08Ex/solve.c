#include "solve.h"

#define INF 97
#define EXTR 122
#define TO_UPPER 32

#define LOWER(a) (INF <= a && a <= EXTR)

int t8_solve(char ** a, int n, char *s) {
	bool fl_lst = false, fl_cur = false, fl_nxt = false;
	int i, j;

	fl_cur = is_inside(a[0], s);

	for (i = 1, j = 0; i < n; ++i) {
		if (is_inside(a[i], s)) {
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

bool is_inside(char *a, char *s)
{
	int len_s = (int)strlen(s);
	int len_a = (int)strlen(a);
	int i, j;

	if (len_s < len_a) return false;
	
	for (i = 0; i < len_s; ++i) {
		if (!ccmp(a[0], s[i])) {
			if (len_a > (len_s-len_a)) return false;

			for (j = 0; j < len_a; ++j) {
				if (ccmp(a[j], s[i + j]) != 0) break;
			}

			if (j == len_a) return true;
		}
	}

	return false;
}

int ccmp(char a, char b) {
	if (LOWER(a)) a -= TO_UPPER;
	if (LOWER(b)) b -= TO_UPPER;

	if (a < b) return -1;
	if (a > b) return 1;
	return 0;
}

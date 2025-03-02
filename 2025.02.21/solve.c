#include "solve.h"

int t1_solve(char ** a, int n, char *s) {
	int i, j;
	for (i = 0, j = 0; i < n; ++i) {
		if (strcmp(a[i], s) >= 0) 
		{
			if (i != j) a[j] = a[i];
			j++;
		} else free(a[i]);
	}

	for (i = j; i < n; ++i) a[i] = 0;

	return j;
}

int t2_solve(char ** a, int n, char *s) {
	int i, j;
	for (i = 0, j = 0; i < n; ++i) {
		if (!strstr(s, a[i])) {
			if (i != j)
			{
				a[j] = a[i];
			}
			j++;
		} else free(a[i]);
	}

	for (i = j; i < n; ++i) a[i] = 0;

	return j;
}

int t3_solve(char ** a, int n, char *s) {
	int i, j;
	for (i = 0, j = 0; i < n; ++i) {
		if (strpbrk(s, a[i])) {
			if (i != j) 
			{
				a[j] = a[i];
			}
			j++;	
		} else {
			free(a[i]);
		}	
	}
	
	for (i = j; i < n; ++i) a[i] = 0;

	return j;
}

int t4_solve(char ** a, int n, char *s) {
	size_t len_s = strlen(s);
	int i, j, k;
	for (i = 0, j = 0, k = 0; i < n; ++i) {
		if (len_s <= strlen(a[i])) {
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

int t6_solve(char ** a, int n, char *s) {
	int i, j, k;
	for (i = 0, j = 0, k = 0; i < n; ++i) {
		if (strpbrk(a[i], s)) {
			if (k > 1)
			{
				for (int x = 2; x < k; x++) free(a[i - x]);
				a[j++] = a[i - 1];
			}
			
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
			}
			k++;
		}
	}
	
	if (k > 1)
	{
		for (int x = 2; x < k; x++) free(a[i - x]);
		a[j++] = a[i - 1];
	}	

	for (i = j; i < n; ++i) a[i] = 0;

	return j;
}

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

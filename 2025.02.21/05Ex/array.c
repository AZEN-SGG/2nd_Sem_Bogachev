#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "io_status.h"
#include "array.h"


io_status read_array(char* a[], int n, const char * name)
{
	char buf[LEN] = {0};
	FILE *fp = 0;
	int i, j;

	if (!(fp = fopen(name, "r"))) return ERROR_OPEN;
	for (i = 0; i < n; i++) {
		if (!fgets(buf, sizeof(buf), fp))
		{
			fclose(fp);
			free_array(a, i);
			return ERROR_READ;
		}

		for (j = 0; buf[j]; j++)
		{
			if (buf[j] == '\n')
			{
				buf[j] = 0;
				break;
			}
		}

		a[i] = (char *)malloc((j+1) * sizeof(char));
		if (!a[i]) 
		{
			fclose(fp);
			free_array(a, i);
			return ERROR_MEM;
		}

		strcpy(a[i], buf);
	}

	fclose(fp);
	return SUCCESS;
}


void free_array(char ** a, int n)
{
	int i;
	for(i = 0; i < n; ++i) 
	{
		if (a[i]) 
		{
			free(a[i]);
			a[i] = 0;
		}
	}
}

void print_array(char ** a, int n, int m)
{
	int l = (n > m ? m : n);
	int i;
	for (i = 0; i < l; ++i) printf("%s\n", a[i]);
}

int delete_string(char ** a, int n, int i)
{
	free(a[i]);
	a[i] = a[n - 1];
	a[n - 1] = 0;
	return n - 1;
}


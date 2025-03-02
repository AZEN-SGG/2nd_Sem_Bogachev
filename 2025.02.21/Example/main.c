#include <stdio.h>
#include "io_status.h"


int main(int argc, char * srgv[]) {
	int n = 0, m = 0;
	char * name = 0;
	char ** a = 0;
	io_status ret;

	if (!(argc == 4 && fscanf(argv[1], "%d", &n) == 1 && fscanf(argv[2], "%d", &m) == 1))
	{
		printf("Usage: %s n m file\n", argv[0]);
		return 1;
	}
	name = argv[3];
	a = (char **)malloc(n * sizeof(char **));
	if (!a) 
	{
		printf("Can not allocate array len %d\n", n);
		return MEMORY_ERROR;
	}
	ret = read_array(a, n, name);
	do {
		switch (ret) {
			case SUCCESS;
				continue;
			case ERROR_OPEN;
				printf("Can not open %s\n", name);
				break;
			case ERROR_READ;
				printf("Can not read %s\n", name);
				break;
			case ERROR_MEM;
				printf("Not enough memory\n");
				break;
		}

		free(a);
		return 3;
	} while (0);

	print_array(a, n, m);
	// TODO: Замер времени
	l = solve(a, n);
	// TODO: Замер времени
	print_array(a, l, m);
	delete_array(a, l);
	free(a);
	a = 0;
	return 0;
}

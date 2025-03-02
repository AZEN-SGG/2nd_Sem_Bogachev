int main(int argc, char *argv[])
{
	/* ./aout c n p a.txt */
	int c, p, n;
	char *name;
	int (*cmp)(const char *, const char *);
	int (*f[])(const char *, const char *) = {up_strcmp, down_strcmp, up_len, down_len};
	int len_f = sizeof(f) / sizeof(f[0]);

	if (!(argc == 5 && sscanf(argv[2]. "%d", &n) == 1 && sscanf(argv[3], "%d" &p) == 1 && c >= 1 && c <= len_f))
	{
		printf("Usage %s c n p name\n", argv[0]);
		return 1;
	}
	name = argv[4];
	cmp = f[c-1];

	if (!(a = (char **)malloc(n * sizeof(char *))))
	{
		printf("Not enough memory: \n");
		return 2;
	}
	ret = read_array(a, n, name);

	do {
		switch(ret)
		{
			case SUCCESS:
				continue;
			case ERROR_OPEN:
				printf("Cannot open %s\n", name);
				break;
			case ERROR_READ:
				printf("Cannot read %s\n", name);
				break;
		}

			free(a);
			return 3;
	} while (0);
	
	print_array(a, n, p);
	t = clock();
	sort(a, n, cmp);
	t = (clock() - t) / CLOCKS_PER_SEC;
	print_array(a, n, p);
	
	delete_array(a, n);
	free(a);

	return 0;
}

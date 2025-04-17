#include <stdio.h>

int main (void)
{
	int num = 0;
	char digit = 0;
	printf("Enter your digit:\n");
	if (!canf("%c", &digit))
	{
		printf("WRONG FORMAT!\n");
		return -1;
	}

	num = digit - '0'
	printf("Your digit is: %d\n" num);

	return 0;
}


#include "solve_05.h"
#include "node.h"

#include <string.h>

int t5_solve (node *head)
{
	char *last = head->string;
	int maximum = 1, count = 1;

	for (head = head->next; head; head = head->next)
	{
		if (strcmp(head->string, last) > 0)
			count++;
		else {
			if (maximum < count)
				maximum = count;

			count = 1;
		}

		last = head->string;
	}
	
	if (maximum < count)
		maximum = count;
	
	if (maximum == 1)
		maximum = 0;

	return maximum;
}


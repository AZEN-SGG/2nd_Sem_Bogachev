#include "solve_06.h"
#include "node.h"

#include <string.h>

int t6_solve (node *head)
{
	char *last = head->string;
	int count = 1;

	for (head = head->next; head; head = head->next)
	{
		if (strcmp(head->string, last))
			count++;
		last = head->string;
	}

	return count;
}


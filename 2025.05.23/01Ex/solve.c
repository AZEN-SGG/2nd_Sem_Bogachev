#include "solve.h"
#include "node.h"

#include <string.h>

int t1_solve (node *head)
{
	char *maximum = head->string;
	int count = 1;

	for (head = head->next; head; head = head->next)
	{
		int cmp = strcmp(head->string, maximum);
		if (cmp	> 0) {
			maximum = head->string;
			count = 1;
		} else if (!cmp)
			count++;
	}

	return count;
}


#include "solve.h"
#include "node.h"

#include <string.h>

int t7_solve (node *head)
{
	char *last = head->string;
	int maximum = 0, count = 1;

	for (head = head->next; head; head = head->next)
	{
		if (strcmp(head->string, last))
			count++;
		else {
			if (maximum < (count-1))
				maximum = count-1;
			count = 0;	
		}
		last = head->string;
	}

	if (maximum < count)
		maximum = count;

	return maximum;
}


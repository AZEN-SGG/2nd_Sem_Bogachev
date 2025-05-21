#include "solve_07.h"
#include "node.h"

#include <string.h>

int t7_solve (node *head)
{
	char *last = head->string;
	int maximum = 0, count = 0, consist = 0;

	for (head = head->next; head; head = head->next)
	{
		if (strcmp(head->string, last) == 0) {
			if (maximum < count)
				maximum = count - 1;
			consist = 1;
			count = 0;
		} else 
			count += consist;	
		last = head->string;
	}

	return maximum;
}


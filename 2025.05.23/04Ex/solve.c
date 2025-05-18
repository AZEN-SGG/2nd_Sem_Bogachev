#include "solve.h"
#include "node.h"

#include <string.h>

int t4_solve (node *head)
{
	char *last = head->string;
	int maximum = 0, count = 0, local = 1, strict = 1;

	for (head = head->next; head; head = head->next)
	{
		int cmp = strcmp(head->string, last);
		if (cmp > 0) {
			count += local;
			local = 1;
			strict = 1;
		} else if (cmp < 0) {
			if (!strict)
				count += local;
			if (maximum < count)
				maximum = count;
			count = 0;
			local = 1;
			strict = 0;
		} else {
			local++;
		}
		last = head->string;
	}
	
	if (!strict)
		count += local;

	if (maximum < count)
		maximum = count;

	return maximum;
}


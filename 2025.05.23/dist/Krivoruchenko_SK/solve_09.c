#include "solve_09.h"
#include "node.h"
#include "io_node.h"

#include <string.h>
#include <stdlib.h>

node * t9_solve (node *head)
{
	int cmp_last, cmp_next;
	node *last, *curr, *next,
	     *deleted = NULL;
	cmp_last=cmp_next=0;
	last = head;
	if (!last)
		return NULL;
	curr = last->next;
	if (!curr)
		return head;

	for (next = curr->next; next; next = curr->next)
	{
		if (deleted)
			cmp_last = strcmp(curr->string, deleted->string);
		else
			cmp_last = strcmp(curr->string, last->string);
		cmp_next = strcmp(curr->string, next->string); // Как происходит обращение в память для структур?

		if ((cmp_last >= 0) && (cmp_next >= 0))
		{
			if (deleted)
				delete_node(deleted);
			deleted = curr;
			
			last->next = next; 
			curr = last;
		} else
		{
			if (deleted)
				delete_node(deleted);
			deleted = NULL;
		}
		last = curr;
		curr = next;
	}

	if (deleted)
		delete_node(deleted);

	return head;	
}


#include "solve_09.h"
#include "node.h"
#include "io_node.h"

#include <string.h>
#include <stdlib.h>

node * t9_solve (node *head)
{
	int cmp_last, cmp_next;
	node *last, *curr, *next,
	     *deleted;
	last=next=deleted=NULL;
	cmp_last=cmp_next=0;
	curr = head;
	if (!curr)
		return NULL;

	for (next = curr->next; next; next = curr->next)
	{
		if (deleted)
			cmp_last = strcmp(curr->string, deleted->string);
		else if (!last)
			cmp_last = 1;
		else
			cmp_last = strcmp(curr->string, last->string);
		cmp_next = strcmp(curr->string, next->string); // Как происходит обращение в память для структур?

		if ((cmp_last >= 0) && (cmp_next >= 0))
		{
			if (deleted)
				delete_node(deleted);
			deleted = curr;
			if (last) {
				last->next = next; 
				curr = last;
			} else {
				head = next;
				curr = NULL;
			}
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
		cmp_last = strcmp(curr->string, deleted->string);
	else if (!last)
		cmp_last = 1;
	else
		cmp_last = strcmp(curr->string, last->string);

	if (cmp_last >= 0)
	{
		delete_node(curr);
		if (last)
			last->next = NULL;
		else
			head = NULL;
		curr = NULL;
	}

	if (deleted)
		delete_node(deleted);

	return head;	
}


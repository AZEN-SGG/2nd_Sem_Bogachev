#include "io_node.h"
#include "node.h"
#include "status.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int get_length (node * head)
{
	node *curr;

	int i = 0;
	for (curr = head; curr; curr=curr->next)
		i++;

	return i;
}

void delete_list (node * head)
{
	node *curr, *next;
	for (curr = head; curr; curr = next) {
		next = curr->next;
		free(curr->string);
		free(curr);
	}
}

io_status read_list (node **list, const char *filename)
{
	FILE *fp = 0;
	char *string, buf[LEN_STR];
	node *head, *lunit, *unit;

	head = lunit = unit = NULL;

	if (!(fp = fopen(filename, "r"))) 
		return ERR_OPEN;

	while (fgets(buf, LEN_STR, fp))
	{
		unit = (node *)malloc(sizeof(node));
		if (!unit) {
			fclose(fp);
			delete_list(head);
			
			return ERR_MEM;
		}

		unit->next = NULL;
		
		buf[strcspn(buf, "\n")] = '\0';
		string = strdup(buf);
		if (!string) {
			fclose(fp);
			free(unit);
			delete_list(head);

			return ERR_MEM;
		}

		unit->string = string;
		if (!lunit) 
			head = unit;
		else
			lunit->next = unit;

		lunit = unit;
	}

	*list = head;

	fclose(fp);
	return SUCCESS;
}

void print_list (node *head, const int p)
{
	for (int i = 0; head && i < p; head = head->next, i++)
		printf("%s\n", head->string);
}


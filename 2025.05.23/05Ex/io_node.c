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

void delete_nodes (node *head, const int count)
{
	for (int i = 0; i < count; ++i)
	{
		node *temp = head;
		head = head->next;

		delete_node(temp);
	}
}

io_status read_list (node **list, const char *filename)
{
	FILE *fp = 0;
	char *string, buf[LEN_STR] = {0};
	node *head, *lunit, *unit;

	head = lunit = unit = NULL;

	if (!(fp = fopen(filename, "r"))) 
		return ERR_OPEN;

	while (fgets(buf, LEN_STR, fp))
	{
		int len = strcspn(buf, "\n");
		unit = (node *)malloc(sizeof(node));
		if (!unit) {
			fclose(fp);
			delete_list(head);
			
			return ERR_MEM;
		}

		unit->next = NULL;
		
		buf[len] = '\0';
		string = (char *)malloc((len+1) * sizeof(char));
		if (!string) {
			fclose(fp);
			free(unit);
			delete_list(head);

			return ERR_MEM;
		}

		strcpy(string, buf);

		unit->string = string;
		if (!lunit) 
			head = unit;
		else
			lunit->next = unit;

		lunit = unit;
	}
	
	if (!head)
		return ERR_READ;

	*list = head;

	fclose(fp);
	return SUCCESS;
}

void print_list (node *head, const int p)
{
	for (int i = 0; head && i < p; head = head->next, i++)
		printf("%s\n", head->string);
}


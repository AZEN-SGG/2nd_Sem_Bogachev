#ifndef NODE_H
#define NODE_H

#define LEN_STR 1234

struct _node;

typedef struct _node
{
	char *string;
	struct _node *next;
} node;

#endif

#define LEN 1234

struct _node;
typedef struct _node
  {
  char* string;
  struct _node* next;
  } node;
  
io_status read_list(node**, char*);
void print_list(node*, int);
void free_list(node*);
int get_length(node*);

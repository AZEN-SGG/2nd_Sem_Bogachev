#define LEN 1235

struct _node;
typedef struct _node
{
char *string;
struct _node* next;
} node;

int read_node(node **, const char *);

void print_node(int p, node* head);

void delete_node(node* head);

void copy_node(node* from, node* to);

//void delete_element(node* tmp1, node* tmp2, node* tmp3);

int node_len(node* head);

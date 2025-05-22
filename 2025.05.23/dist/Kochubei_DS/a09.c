#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solve.h"

int main(int argc, char** argv)
{
    int p=0;
    int len=0;
    double t=0;
    char* name;
    node* N;
    int status=0;
    if (argc!=3)
    {
        printf("Usage: %s p name\n", argv[0]);
        return -1;
    }
    if (sscanf(argv[1], "%d", &p)!=1)
    {
        printf("Usage: %s p name\n", argv[0]);
        return -1;
    }
    name=argv[2];
    status=read_node(&N, name);
    if (status==-1)
    {
        printf("Cannot open file\n");
        delete_node(N);
        return -1;
    }
    else if (status==-2)
    {
        printf("Cannot read file\n");
        delete_node(N);
        return -2;
    }
    else if (status==3)
    {
        printf("Cannot allocate memory\n");
        delete_node(N);
        return -2;
    }
    print_node(p, N);
    t=clock();
    N=solve9(N);
    t=(clock()-t)/CLOCKS_PER_SEC;
    len=node_len(N);
    print_node(p, N);
    printf ("%s : Task = %d Length = %d Elapsed = %.2f\n", argv[0], 9, len, t);
    delete_node(N);
    return 0;
}

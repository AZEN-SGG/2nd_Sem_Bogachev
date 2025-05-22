#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "add.h"

/*/
int read_node(char* name, node* head)
{
    char buf[LEN];
    node* tmp;
    FILE* fd;
    tmp=head;
    fd=fopen(name, "rt");
    if (fd==0)
    {
        tmp->next=0;
        return -1;
    }
    while(fgets(buf, LEN, fd))
    {
        size_t l=0;
        //printf("BUF: %s\n", buf);
        l=strlen(buf);
        if (
        tmp->string=(char*)malloc((l+1)*sizeof(char));
        if (tmp->string==0)
        {
            fclose(fd);
            tmp->next=0;
            return -3;
        }
        strcpy(tmp->string, buf);
        if (!feof(fd))
        {
            printf("NOT FEOF: %s\n", tmp->string);
            tmp->next=(node*)malloc(sizeof(node));
            if (tmp->next==0)
            {
                fclose(fd);
                tmp->next=0;
                return -3;
            }
            printf("Str: %s\n", tmp->string);
            tmp=tmp->next;
        }
        else
        {
            printf("FEOF: %s\n", tmp->string);
            tmp->next=0;
            return 0;
        }
        //size_t l=strcspn(buf, "\n");
        //buf[l]='\0';
        size_t l=0;
        l=strlen(buf);
        printf("Buf: %s\n", buf);
        printf("OK\n");
        tmp->string=(char*)malloc((l+1)*sizeof(char));
        if (tmp->string==0)
        {
            tmp->next=0;
            delete_node(head);
            fclose(fd);
            return -3;
        }
        print_node(100, head);
        strcpy(tmp->string, buf);
        tmp->next=(node*)malloc(sizeof(node));
        if (tmp->next==0)
        {
            delete_node(head);
            fclose(fd);
            return -3;
        }
        if (tmp->next==0) break;
        tmp=tmp->next;
    }
    tmp->string=0;
    fclose(fd);
    return 0;
}
/*/

int read_node(node ** HEAD, const char *name)
{
    char buf[LEN];
    FILE *fp = 0;
    node *head;
    node *tmp;
    int j;
    if (!(fp = fopen(name, "r"))) return -1;
    head = (node*)malloc(sizeof(node));
    head->next = 0;
    if (!fgets(buf, LEN, fp))
    {
        fclose(fp);
        free(head);
        return -2;
    }
    for (j = 0; buf[j] && buf[j] != '\n'; j++);
    buf[j] = '\0';
    head->string = (char *) malloc((j + 1) * sizeof(char));
    if (!head->string)
    {
        fclose(fp);
        free(head);
        return -2;
    }
    strcpy(head->string, buf);
 
    *HEAD = head;

    while (fgets(buf, LEN, fp))
    {
    tmp = (node*)malloc(sizeof(node));
    for (j = 0; buf[j] && buf[j] != '\n'; j++);
    buf[j] = '\0';
    tmp->string = (char *) malloc((j + 1) * sizeof(char));
    if (!head->string)
    {
        fclose(fp);
        free(tmp);
        delete_node(*HEAD);
        return -2;
    }
    head->next = tmp;
    head = tmp;
    strcpy(head->string, buf);
    head->next = 0;
    }
    if (!feof(fp))
    {
        fclose(fp);
        delete_node(*HEAD);
        return -2;
    }
    fclose(fp);
    return 0;

}
void print_node(int p, node* head)
{
    node* tmp;
    tmp=head;
    //printf("%s", head->string);
    for (int i=0; i<p; i++)
    {
        printf("%s\n", tmp->string);
        if (tmp->next==0) break;
        tmp=tmp->next;
    }
    printf("\n");
}

void delete_node(node* head)
{
    while(1)
    {
        node* pointer;
        free(head->string);
        pointer=head;
        head=head->next;
        free(pointer);
        if (head==0) break;
    }
}

void copy_node(node* from, node* to)
{
    if (to==0) return;
    to->next=from->next;
    to->string=from->string;
}

/*/
void delete_element(node* tmp1, node* tmp2, node* tmp3)
{
    free(tmp2->string);
    free(tmp2);
    tmp1->next=tmp3;
}
/*/

int node_len(node* head)
{
    node tmp;
    int res=1;
    copy_node(head, &tmp);
    while(tmp.next!=0)
    {
        res++;
        copy_node(tmp.next, &tmp);
        //printf("s: %s\n", tmp.string);
    }
    return res;
}

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "solve.h"

int solve1(node* head)
{
    char s[1]={'\0'};
    int cnt=0;
    char* mx=s;
    node tmp;

    copy_node(head, &tmp);
    while(1)
    {
        int r=0;

        r=strcmp(tmp.string, mx);
        if (r>0)
        {
            mx=tmp.string;
            cnt=1;
        }
        if (r==0)
        {
            cnt++;
        }
        if (tmp.next==0) break;
        copy_node(tmp.next, &tmp);
    }

    return cnt;
}

int solve2(node* head)
{
    int cnt=0;
    node tmp1;
    node tmp2;
    copy_node(head, &tmp1);

    if (head->next==0)
    {
        return 0;
    }
    copy_node(head->next, &tmp2);
    //printf("OK\n");
    while(1)
    {
        if (strcmp(tmp1.string, tmp2.string)<0)
        {
            //printf("%s\n", tmp2.string);
            cnt++;
        }
        if (tmp2.next==0) break;
        copy_node(&tmp2, &tmp1);
        copy_node(tmp2.next, &tmp2);
    }
    return cnt;
}

int solve3(node* head)
{
    char s[1]={'\0'};
    int cnt=0;
    node tmp1;
    node tmp2;
    node tmp3;
    if (head->next==0)
    {
        return 0;
    }
    tmp1.next=0;
    tmp1.string=s;
    copy_node(head, &tmp2);
    copy_node(head->next, &tmp3);
    while(1)
    {
        if (strcmp(tmp1.string, tmp2.string)<=0 && strcmp(tmp2.string, tmp3.string)>=0)
        {
            cnt++;
        }
        if (tmp3.next==0) break;
        copy_node(&tmp2, &tmp1);
        copy_node(&tmp3, &tmp2);
        copy_node(tmp3.next, &tmp3);
    }
    if (strcmp(tmp1.string, tmp2.string)<=0)
    {
        cnt++;
    }
    return cnt;
}

int solve4(node* head)
{
    char s[1]={'\0'};
    int index=0;
    int last_index=INT_MAX;
    int mx=0;
    node tmp1;
    node tmp2;
    node tmp3;
    if (head->next==0)
    {
        return 0;
    }
    tmp1.next=0;
    tmp1.string=s;
    copy_node(head, &tmp2);
    copy_node(head->next, &tmp3);
    while(1)
    {
        if (strcmp(tmp1.string, tmp2.string)<=0 && strcmp(tmp2.string, tmp3.string)>=0)
        {
            int d=index-last_index-1;
            if (d>mx)
            {
                mx=d;
            }
            last_index=index;

        }
        if (tmp3.next==0) break;
        copy_node(&tmp2, &tmp1);
        copy_node(&tmp3, &tmp2);
        copy_node(tmp3.next, &tmp3);
        index++;
    }
    if (strcmp(tmp1.string, tmp2.string)<=0)
    {
        int d=index-last_index-1;
        if (d>mx)
        {
            mx=d;
        }
        last_index=index;
    }
    return mx;
}

int solve5(node* head)
{
    int mx=0;
    int len=1;
    node tmp1;
    node tmp2;
    if (head->next==0)
    {
        return 1;
    }
    copy_node(head, &tmp1);
    copy_node(head->next, &tmp2);
    while(1)
    {
        if (strcmp(tmp2.string, tmp1.string)>0)
        {
            len++;
        }
        else
        {
            if (len>mx)
            {
                mx=len;
            }
            len=1;
        }
        if (tmp2.next==0) break;
        copy_node(&tmp2, &tmp1);
        copy_node(tmp2.next, &tmp2);
    }
    if (len>mx)
    {
        mx=len;
    }
    return mx;
}

int solve6(node* head)
{
    int cnt=0;
    int len=1;
    node tmp1;
    node tmp2;
    if (head->next==0)
    {
        return 1;
    }
    copy_node(head, &tmp1);
    copy_node(head->next, &tmp2);
    while(1)
    {
        if (strcmp(tmp2.string, tmp1.string)==0)
        {
            len++;
            //printf("%s %s\n", tmp1.string, tmp2.string);
        }
        else
        {
            if (len>=2)
            {
                cnt++;
            }
            len=1;
        }
        if (tmp2.next==0) break;
        copy_node(&tmp2, &tmp1);
        copy_node(tmp2.next, &tmp2);
    }
    if (len>=2)
    {
        cnt++;
    }
    return cnt;
}

int solve7(node* head)
{
    int index=0;
    int last_index=INT_MAX;
    int mx=0;
    int len=1;
    node tmp1;
    node tmp2;
    if (head->next==0)
    {
        return 1;
    }
    copy_node(head, &tmp1);
    copy_node(head->next, &tmp2);
    while(1)
    {
        if (strcmp(tmp2.string, tmp1.string)==0)
        {
            if (len==1)
            {
                int d=index-last_index-1;
                if (d>mx)
                {
                    mx=d;
                }
            }
            len++;
        }
        else
        {
            if (len>2)
            {
                last_index=index;
            }
            len=1;
        }
        if (tmp2.next==0) break;
        copy_node(&tmp2, &tmp1);
        copy_node(tmp2.next, &tmp2);
        index++;
    }
    return mx;
}

node* solve8(node* head)
{

    node tmp1;
    node tmp2;
    node tmp3;
    node* ptr1;
    node* ptr2;
    node* ptr3;
    if (head->next==0)
    {
        return head;
    }
    if (head->next->next==0)
    {
        if (strcmp(head->string, head->next->string)>=0)
        {
            node* res=head->next;
            free(head->string);
            free(head);
            return res;
        }
        else
        {
            return head;
        }
    }
    while(strcmp(head->string, head->next->string)>=0)
    {
        node* p=head->next;
        free(head->string);
        free(head);
        head=p;
        if (head->next==0) return head;
    }
    copy_node(head, &tmp1);
    copy_node(head->next, &tmp2);
    copy_node(head->next->next, &tmp3);
    ptr1=head;
    ptr2=head->next;
    ptr3=head->next->next;
    while(1)
    {
        if (strcmp(tmp2.string, tmp3.string)>=0)
        {
            //copy_node(ptr2, &last_thrown);
            ptr1->next=ptr3;
            free(ptr2->string);
            free(ptr2);
            ptr1=ptr3;
            if (ptr3->next==0) break;
            ptr2=ptr3->next;
            if (ptr2->next==0) break;
            else ptr3=ptr2->next;
            copy_node(ptr1, &tmp1);
            copy_node(ptr2, &tmp2);
            copy_node(ptr3, &tmp3);
        }
        else
        {
            if (ptr3->next==0) break;
            copy_node(&tmp2, &tmp1);
            copy_node(&tmp3, &tmp2);
            copy_node(tmp3.next, &tmp3);
            ptr1=ptr2;
            ptr2=ptr3;
            ptr3=ptr3->next;
        }
    }
    return head;

}



node* solve9(node* head)
{
    node* tmp1;
    node* tmp2;
    node* tmp3;
    int was_thrown=0;
    int last_eq=0;
    tmp1=head;
    if (head->next==0)
    {
        return head;
    }
    if (head->next->next==0)
    {
        return head;
    }
    tmp1=head;
    tmp2=head->next;
    tmp3=head->next->next;
    while(tmp3->next!=0)
    {
        if (was_thrown==0)
        {
            if (strcmp(tmp1->string, tmp2->string)<=0 && strcmp(tmp2->string, tmp3->string)>=0)
            {
                if (strcmp(tmp2->string, tmp3->string)==0)
                {
                    last_eq=1;
                }
                else
                {
                    last_eq=0;
                }
                free(tmp2->string);
                tmp2->string=0;
                was_thrown=1;
            }
            else
            {
                was_thrown=0;
            }
        }
        else
        {
            if (last_eq==1 && strcmp(tmp2->string, tmp3->string)>=0)
            {
                if (strcmp(tmp2->string, tmp3->string)==0)
                {
                    last_eq=1;
                }
                else
                {
                    last_eq=0;
                }
                free(tmp2->string);
                tmp2->string=0;
                was_thrown=1;
            }
            else
            {
                was_thrown=0;
            }
        }
        tmp1=tmp2;
        tmp2=tmp3;
        tmp3=tmp3->next;
    }
    tmp1=head;
    tmp2=head->next;
    tmp3=head->next->next;
    while(1)
    {
        if (tmp2->string==0)
        {
            free(tmp2);
            tmp1->next=tmp3;
            if (tmp3->next==0)
            {
                break;
            }
            tmp2=tmp3;
            tmp3=tmp3->next;
        }
        else
        {
            if (tmp3->next==0)
            {
                break;
            }
            tmp1=tmp2;
            tmp2=tmp3;
            tmp3=tmp3->next;
        }
    }
    return head;
}




node* solve10(node* head)
{
    node* tmp1;
    node* tmp2;
    node* tmp3;
    int last=0;
    if (head->next==0)
    {
        return head;
    }
    tmp1=head;
    tmp2=head->next;
    while(1)
    {
        if (strcmp(tmp1->string, tmp2->string)>=0)
        {
            free(tmp1->string);
            tmp1->string=0;
            last=1;
        }
        else
        {
            if (last==1)
            {
                free(tmp1->string);
                tmp1->string=0;
                last=0;
            }
        }
        if (tmp2->next==0)
        {
            break;
        }
        tmp1=tmp2;
        tmp2=tmp2->next;
    }

    if (last==1)
    {
        free(tmp2->string);
        tmp2->string=0;
    }
    tmp1=head;
    tmp2=head->next;
    if (head->next->next==0)
    {
        if (tmp1->string==0)
        {
            free(tmp1);
            free(tmp2);
            return 0;
        }
        else
        {
            return head;
        }
    }
    tmp3=head->next->next;
    while(1)
    {
        if (tmp2->string==0)
        {
            free(tmp2);
            tmp1->next=tmp3;
            if (tmp3->next==0)
            {
                if (tmp3->string==0)
                {
                    tmp1->next=0;
                    free(tmp3);
                }
                break;
            }
            tmp2=tmp3;
            tmp3=tmp3->next;
        }
        else
        {
            if (tmp3->next==0)
            {
                if (tmp3->string==0)
                {
                    tmp2->next=0;
                    free(tmp3);
                }
                break;
            }
            tmp1=tmp2;
            tmp2=tmp3;
            tmp3=tmp3->next;
        }
    }
    if (head->string==0)
    {
        node* ret=head->next;
        free(head);
        return ret;
    }
    return head;
}






/*/
node* solve9(node* head)
{
    char s[1]={'\0'};
    int was_thrown=0;
    node last_thrown;
    node tmp1;
    node tmp2;
    node tmp3;
    node* ptr1;
    node* ptr2;
    node* ptr3;
    last_thrown.next=0;
    last_thrown.string=s;
    if (head->next==0)
    {
        return head;
    }
    if (head->next->next==0)
    {
        return head;
    }
    copy_node(head, &tmp1);
    copy_node(head->next, &tmp2);
    copy_node(head->next->next, &tmp3);
    ptr1=head;
    ptr2=head->next;
    ptr3=head->next->next;
    while(ptr3->next!=0)
    {
        if (was_thrown==0)
        {
            if (strcmp(tmp2.string, tmp1.string)>=0 && strcmp(tmp2.string, tmp3.string)>=0)
            {
                copy_node(ptr2, &last_thrown);
                ptr1->next=ptr3;
                free(ptr2->string);
                free(ptr2);
                ptr1=ptr3;
                ptr2=ptr3->next;
                if (ptr2->next==0) break;
                else ptr3=ptr2->next;
                copy_node(ptr1, &tmp1);
                copy_node(ptr2, &tmp2);
                copy_node(ptr3, &tmp3);
                was_thrown=1;

            }
            else
            {
                copy_node(&tmp2, &tmp1);
                copy_node(&tmp3, &tmp2);
                copy_node(tmp3.next, &tmp3);
                ptr1=ptr2;
                ptr2=ptr3;
                ptr3=ptr3->next;
                was_thrown=0;
            }
        }
        else
        {
            if (strcmp(tmp2.string, last_thrown.string)>=0 && strcmp(tmp2.string, tmp3.string)>=0)
            {
                copy_node(ptr2, &last_thrown);
                ptr1->next=ptr3;
                free(ptr2->string);
                free(ptr2);
                ptr1=ptr3;
                ptr2=ptr3->next;
                if (ptr2->next==0) break;
                else ptr3=ptr2->next;
                copy_node(ptr1, &tmp1);
                copy_node(ptr2, &tmp2);
                copy_node(ptr3, &tmp3);
                was_thrown=1;

            }
            else
            {
                copy_node(&tmp2, &tmp1);
                copy_node(&tmp3, &tmp2);
                copy_node(tmp3.next, &tmp3);
                ptr1=ptr2;
                ptr2=ptr3;
                ptr3=ptr3->next;
                was_thrown=0;
            }
        }
    }
    return head;
}

node* solve10(node* head)
{

    char s[1]={'\0'};
    node base;
    int len=1;
    node tmp1;
    node tmp2;
    node* ptr0;
    node* ptr1;
    node* ptr2;
    node* start_falling;
    base.next=head;
    base.string=s;
    if (head->next==0)
    {
        return head;
    }
    copy_node(head, &tmp1);
    copy_node(head->next, &tmp2);
    ptr0=&base;
    ptr1=head;
    ptr2=head->next;
    while(1)
    {
        if (strcmp(tmp2.string, tmp1.string)<=0)
        {
            if (len==1) start_falling=ptr0;
            len++;
        }
        else
        {
            if (len>1)
            {
                node* save=start_falling->next;
                //printf("Start_falling: %s Start_next: %s Finish %s Ptr0: %s p1: %s p: %s  neext: %s\n", start_falling->string, start_falling->next->string, tmp2.string, ptr0->string, ptr1->string, ptr2->string, ptr2->next->string);
                print_node(100, base.next);
                start_falling->next=ptr2;
                //ptr1->next=0;
                //delete_node(save);
                while(1)
                {
                    node* p=save->next;
                    if (p==ptr2) break;
                    free(save->string);
                    free(save);
                    save=p;
                }
            }
            len=1;
        }
        if (tmp2.next==0)
        {
            break;
        }
        copy_node(&tmp2, &tmp1);
        copy_node(tmp2.next, &tmp2);
        ptr0=ptr1;
        ptr1=ptr2;
        ptr2=ptr2->next;
    }
    if (len>1)
    {
        node* save=start_falling->next;
        //printf("Start: %s Finish %s\n", start_falling->next->string, tmp2.string);
        start_falling->next=0;
        delete_node(save);
    }
    return base.next;
}






node* solve10(node* head)
{
    int flag=0;
    char s[1]={'\0'};
    node base;
    node tmp1;
    node tmp2;
    node tmp3;
    node* ptr1;
    node* ptr2;
    node* ptr3;
    node* save;
    base.next=head;
    base.string=s;
    if (head->next==0)
    {
        return head;
    }
    copy_node(&base, &tmp1);
    copy_node(head, &tmp2);
    copy_node(head->next, &tmp3);
    ptr1=&base;
    ptr2=head;
    ptr3=head->next;
    while(1)
    {
        if (flag==1)
            {
                save->next=ptr2;
                free(ptr1->string);
                free(ptr1);
                ptr1=ptr2;
                ptr2=ptr3;
                if (ptr3->next==0) break;
                ptr3=ptr3->next;
                if (ptr2->next==0) break;
                copy_node(ptr1, &tmp1);
                copy_node(ptr2, &tmp2);
                copy_node(ptr3, &tmp3);
                flag=0;

                ptr1->next=ptr3;
                free(ptr2->string);
                free(ptr2);
                ptr1=ptr3;
                if (ptr3->next==0) break;
                ptr2=ptr3->next;
                if (ptr2->next==0) break;
                else ptr3=ptr2->next;
                copy_node(ptr1, &tmp1);
                copy_node(ptr2, &tmp2);
                copy_node(ptr3, &tmp3);
                flag=0;
                printf("DELETED 2\n");
                print_node(100, base.next);
            }
            else
            {
                if (ptr3->next==0) break;
                copy_node(&tmp2, &tmp1);
                copy_node(&tmp3, &tmp2);
                copy_node(tmp3.next, &tmp3);
                ptr1=ptr2;
                ptr2=ptr3;
                ptr3=ptr3->next;
            }
        if (strcmp(tmp2.string,tmp3.string)>=0)
        {
                        save=ptr1;
            ptr1->next=ptr3;
            free(ptr2->string);
            free(ptr2);
            ptr1=ptr3;
            if (ptr3->next==0) break;
            ptr2=ptr3->next;
            if (ptr2->next==0) break;
            else ptr3=ptr2->next;
            copy_node(ptr1, &tmp1);
            copy_node(ptr2, &tmp2);
            copy_node(ptr3, &tmp3);
            flag=1;
            printf("DELETED 1\n");
            print_node(100, base.next);
        }

        else
        {
            if (flag==1)
            {
                save->next=ptr2;
                free(ptr1->string);
                free(ptr1);
                ptr1=ptr2;
                ptr2=ptr3;
                if (ptr3->next==0) break;
                ptr3=ptr3->next;
                if (ptr2->next==0) break;
                copy_node(ptr1, &tmp1);
                copy_node(ptr2, &tmp2);
                copy_node(ptr3, &tmp3);
                flag=0;

                ptr1->next=ptr3;
                free(ptr2->string);
                free(ptr2);
                ptr1=ptr3;
                if (ptr3->next==0) break;
                ptr2=ptr3->next;
                if (ptr2->next==0) break;
                else ptr3=ptr2->next;
                copy_node(ptr1, &tmp1);
                copy_node(ptr2, &tmp2);
                copy_node(ptr3, &tmp3);
                flag=0;
                printf("DELETED 2\n");
                print_node(100, base.next);
            }
            else
            {
                if (ptr3->next==0) break;
                copy_node(&tmp2, &tmp1);
                copy_node(&tmp3, &tmp2);
                copy_node(tmp3.next, &tmp3);
                ptr1=ptr2;
                ptr2=ptr3;
                ptr3=ptr3->next;
            }

        }

    }
    return base.next;
}
/*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
}Node;

Node *insert(Node *head, int data)
{
    Node *t, *p;
    t = (Node *)malloc(sizeof(Node));
    t->data = data;
    t->next =NULL;

    if(head)
    {
        p = head;
        while(p->next)
            p = p->next;
        p->next = t;
        return head;
    }
    else
        return t;
}

void display(Node *head)
{
    Node *start = head;
    while(start)
    {
        printf("%d ", start->data);
        start = start->next; 
    }
}

int main(void)
{
    int T, data;
    scanf("%d", &T);
    Node *head = NULL;
    while(T--)
    {
        scanf("%d", &data);
        head = insert(head, data);
    }
    display(head);
    return 0;
}

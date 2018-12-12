#include <stdlib.h>
#include <stdio.h>

typedef struct node_s{
    char c;
    struct node_s *next;
}node_t;

node_t *new_node(char c)
{
    node_t *node;
    node = (node_t *)malloc(sizeof(node));
    node->c = c;
    node->next = NULL;
    return node;
}

node_t *linked_list_insert(node_t *head, char c)
{
    node_t *p;
    p = head;
    while(p && p->next)
        p = p->next;

    if(head == NULL)
        head = new_node(c);
    else
        p->next = new_node(c);

    return head;
}

void linked_list_print(node_t *head)
{
    node_t *p;
    p = head;
    while(p)
    {
        putchar(p->c);
        p = p->next; 
    }
}

node_t *remove_node(node_t *head, char c)
{
    node_t *p, *n, *prev;

    while(head && (head->c == c))
    {
        n = head->next;
        free(head);
        head = n;
    }

    if(head != NULL)
    {
        p = prev = head;
        p = p->next;
        while(p)
        {
            if(p->c == c)
            {
                prev->next = p->next;
            }
            else
                prev = p;
            p = p->next;
        }
    }

    return head;
}

int main(int argc, char **argv)
{
    node_t *head;
    char c;

    head = NULL;
    while((c = getchar()) != '\n')
        head = linked_list_insert(head, c);

    head = remove_node(head, '3');
    linked_list_print(head);
    return 0;
}

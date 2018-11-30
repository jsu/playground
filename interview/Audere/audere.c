#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRUE    1
#define FALSE   0
#define MAX_PREFIX_SIZE  8

typedef struct node_s {
    char *name;
    struct node_s **next;
    int number;
}node_t;

node_t *create(char *name)
{
    node_t *node_p;
    node_p = (node_t *)malloc(sizeof(node_p));
    node_p->name = name;
    node_p->number = 0;
    node_p->next = NULL;
    return node_p;
}

/* next = TRUE | FALSE */
void print_map(node_t *node_p, int level, char *prefix, int last_child)
{
    /*
     *  K | L
     */

    /* 
     * Root
     * k t-1
     * |  k t-1-1
     * |  L t-1-2
     * |    k t-1-2-1
     * |    L t-1-2-1
     * L t-2 
     */
    node_t *item;
    int i, prefix_len;
    char current, *new_prefix;

    i = 0;
    item = node_p;
    prefix_len = strlen(prefix);
    new_prefix = (char *)malloc(sizeof(new_prefix) * MAX_PREFIX_SIZE);

    if(level != 0)
    {
        if(last_child)
            current = 'L';
        else
            current = 'K';

        if(prefix_len == 0)
            printf("%c %s\n", current, item->name);
        else
            printf("%s%c %s\n", prefix, current, item->name);
    }
    else
        printf("%s\n", item->name);

    strcpy(new_prefix, prefix);
    if(last_child)
        strcat(new_prefix, "  ");
    else
        strcat(new_prefix, "| ");
    for(i = 0; i < item->number; i++)
    {
        last_child = i == item->number - 1 ? TRUE : FALSE;
        if(level > 0)
            print_map(item->next[i], level + 1, new_prefix, last_child);
        else
            print_map(item->next[i], level + 1, "", last_child);
    }
}

int main(int argc, char **argv)
{
    node_t *p, *p1, *p2, *p11, *p12, *p121, *p122;
    int n;
    n = 2;
    p = create("Fluapi");

    p1 = create("f-1");
    p2 = create("f-2");

    p->next = (node_t **)malloc(sizeof(p->next) * n);
    p->number = n;
    p->next[0] = p1;
    p->next[1] = p2;

    p11 = create("f-1-1");
    p12 = create("f-1-2");

    p1->next = (node_t **)malloc(sizeof(p->next[0]->next) * n);
    p1->next[0] = p11;
    p1->next[1] = p12;
    p1->number = n;

    p121 = create("f-1-2-1");
    p122 = create("f-1-2-2");
    p12->number = 2;
    p12->next = (node_t **)malloc(sizeof(p->next[0]->next[1]->next));
    p12->next[0] = p121;
    p12->next[1] = p122;

    print_map(p, 0, "", FALSE);

    return 0;
}

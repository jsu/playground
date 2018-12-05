#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE    100 * 1000 * 1000
typedef struct node_s {
    int n;
    struct node_s *next;
}node_t;

node_t *push(node_t *root, int n)
{
    node_t *node, *p;
    node = (node_t *)malloc(sizeof(node));
    node->n = n;
    node->next = NULL;

    if(root == NULL)
    {
        root = node;
        return root;
    }

    p = root;
    while(p->next != NULL)
       p = p->next;
    p->next = node;

    return root;
}

node_t *reverse_list(node_t *root)
{
    node_t *current, *next, *prev;
    
    prev = next = NULL;
    current = root;
    while(current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    root = prev;
    return root;
}

node_t *int_to_list(int number)
{
    int n;
    node_t *root;
    root = NULL;

    if(number == 0)
    {
        root = (node_t *)malloc(sizeof(root));
        root->n = 0;
        root->next = NULL;
        return root;
    }

    while(number > 0)
    {
        n = number % 10;
        root = push(root, n);
        number /= 10;
    }
    return reverse_list(root);
}

int solution(int A, int B)
{
    /*
     * return -1 if result >= 1e8 
     */

    node_t *na, *nb;
    int result;
    na = int_to_list(A);
    nb = int_to_list(B);
    result = 0;
    while(na || nb)
    {
        if(result >= 100000000)
            return -1;
        
        if(na)
        {
            result *= 10;
            result += na->n;
            na = na->next;
        }

        if(nb)
        {
            result *= 10;
            result += nb->n;
            nb = nb->next;
        }
    }

    return result;
}

int main(int argc, char **argv)
{
    printf("%d\n", solution(123, 4567));
    printf("%d\n", solution(12345, 678));
    printf("%d\n", solution(1234, 0));
    return 0;
}

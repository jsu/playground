#include <stdlib.h>
#include <stdio.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int i1, i2, carry;
    struct ListNode *p, *p1, *p2, *root;
    root = (struct ListNode *)malloc(sizeof(struct ListNode));
    root->val = 0;
    root->next = NULL;

    p = NULL;
    p1 = l1;
    p2 = l2;
    carry = 0;
    while(p1 || p2 || carry)
    {
        if(p == NULL)
            p = root;
        else
        {
            p->next = (struct ListNode *)malloc(sizeof(struct ListNode));
            p = p->next;
            p->val = 0;
            p->next = NULL;
        }

        i1 = p1 ? p1->val : 0;
        i2 = p2 ? p2->val : 0;
        p->val = i1 + i2 + carry;
        carry = p->val / 10;
        p->val %= 10;

        p1 = p1 ? p1->next : NULL;
        p2 = p2 ? p2->next : NULL;
    }

    return root;
}

struct ListNode *addNode(struct ListNode *root, int value)
{
    struct ListNode *p, *current;
    current = root;

    if(root == NULL)
    {
        p = (struct ListNode *)malloc(sizeof(struct ListNode));
        p->val = value;
        p->next = NULL;
        root = p;
        return root;
    }

    while(current->next)
        current = current->next; 

    current->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    current = current->next;
    current->val = value;
    current->next = NULL;

    return root;
}

int main(int argc, char **argv)
{
    struct ListNode *l1, *l2, *r;

    l1 = NULL;
    l1 = addNode(l1, 4);
    l1 = addNode(l1, 5);
    l1 = addNode(l1, 2);
    l1 = addNode(l1, 2);
    l1 = addNode(l1, 9);
    l1 = addNode(l1, 3);
    l1 = addNode(l1, 8);
    l1 = addNode(l1, 9);
    l1 = addNode(l1, 2);

    l2 = NULL;
    l2 = addNode(l2, 0);
    l2 = addNode(l2, 7);
    l2 = addNode(l2, 6);
    l2 = addNode(l2, 1);
    l2 = addNode(l2, 6);
    l2 = addNode(l2, 5);
    l2 = addNode(l2, 0);
    l2 = addNode(l2, 6);
    l2 = addNode(l2, 7);
    
    r = addTwoNumbers(l1, l2);
    while(r)
    {
        printf("%d ", r->val);
        r = r->next; 
    }
    printf("\n");

    return 0;
}

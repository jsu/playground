#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

struct Node 
{
    char *name;
    struct Node *left;
    struct Node *right;
};

void print_tree(struct Node *n)
{
    /* in order */
    if(n == NULL)
        return;
    print_tree(n->left);
    printf("%s\n", n->name);
    print_tree(n->right);
}

struct Node *insert(struct Node *root, const char *str)
{
    struct Node *node;
    char *ptr;
    
    if(root == NULL)
    {
        node = (struct Node *)malloc(sizeof(*node));
        node->name = (char *)malloc(sizeof(*(node->name)) * (strlen(str) + 1));
        ptr = node->name;
        while((*ptr++ = *str++) != '\0');
        node->left = NULL;
        node->right = NULL;
        root = node;
    }
    else if(strcmp(root->name, str) >= 0)
        root->left = insert(root->left, str);
    else
        root->right = insert(root->right, str);

    return root;
}

int main(void)
{
    int n;
    char *fname, *email;
    struct Node *root = NULL;
    regex_t re;

    regcomp(&re, "[A-Za-z0-9._%+-]+@gmail\\.com", REG_EXTENDED);

    scanf("%d", &n);
    while(n--)
    {
        fname = (char *)malloc(sizeof(fname) * 21);
        email = (char *)malloc(sizeof(email) * 51);
        scanf("%s %s", fname, email);

        if(regexec(&re, email, 0, NULL, 0) == 0)
            root = insert(root, fname);

        free(email);
        free(fname);
    }
    regfree(&re);
    print_tree(root);

    return 0;
}

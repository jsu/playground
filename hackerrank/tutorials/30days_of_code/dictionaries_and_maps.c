#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode 
{
    char *name, *number;
    struct tnode *left, *right;
};

struct tnode *addtree(struct tnode *p, char *name, char *number)
{
    if(p == NULL)
    {
        p = (struct tnode *)malloc(sizeof(struct tnode));
        p->name = (char *)malloc(sizeof(*(p->name)) * (strlen(name) + 1));
        strcpy(p->name, name);
        p->number = (char *)malloc(sizeof(*(p->number)) * (strlen(number) + 1));
        strcpy(p->number, number);
        p->left = p->right = NULL; 
    }
    else if(strcmp(p->name, name) < 0)
        p->left = addtree(p->left, name, number);
    else
        p->right = addtree(p->right, name, number);
    return p;
}

struct tnode *search(struct tnode *p, const char *name)
{
    int cond;
    if(p != NULL)
    {
        if((cond = strcmp(p->name, name)) == 0)
            return p;
        else if(cond < 0)
            return search(p->left, name);
        else
            return search(p->right, name);
    }
    return p;
}

int main(int argc, char **argv)
{
    struct tnode *root, *current;
    int n, i, c, length;
    char *name, *number;

    length = 100;
    name = (char *)malloc(sizeof(*name) * length);
    number = (char *)malloc(sizeof(*number) * length);
    root = NULL;
    scanf("%d", &n);
    while(n--)
    {
        for(c = getchar(); c < 0x41;)
            c = getchar();
        for(i = 0; c != ' '; c = getchar(), i++)
            *(name + i) = c;
        *(name + i) = '\0';
        for(c = getchar(), i = 0; c != '\n' && c != EOF; c = getchar(), i++)
            *(number + i) = c;
        *(number + i) = '\0';
        root = addtree(root, name, number);
    }

    while(!feof(stdin))
    {
        for(c = getchar(); c < 0x41;)
            c = getchar();
        for(i = 0; c != '\n' && c != EOF; c = getchar(), i++)
            *(name + i) = c;
        *(name + i) = '\0';
        current = search(root, name);
        if(current == NULL)
            printf("Not found\n");
        else
            printf("%s=%s\n", current->name, current->number);
    }
    free(name);
    free(number);
    return 0;
}

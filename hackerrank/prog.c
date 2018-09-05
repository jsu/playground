#include <stdio.h>
#define MAXSIZE 100000
int top = -1;

int is_empty()
{
    if(top == -1)
        return 1;
    else
        return 0;
}

int is_full()
{
    if(top == MAXSIZE)
        return 1;
    else
        return 0;
}

int pop(int *stack)
{
    int data;

    if(!is_empty())
    {
        data = stack[top];
        top--;
        return data;
    }
    else
        return -1;
}

void push(int *stack, int data)
{
    if(!is_full())
    {
        top++;
        stack[top] = data; 
    }
}

int main(void)
{
    int stack[MAXSIZE];

    push(stack, 3);
    push(stack, 5);
    push(stack, 9);
    push(stack, 1);
    push(stack, 12);
    push(stack, 15);

    printf("Elements: \n");

    while(!is_empty()) {
        int data = pop(stack);
        printf("%d\n",data);
    }

}

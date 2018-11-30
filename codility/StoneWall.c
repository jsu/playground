// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");
#define STACK_SIZE 100 * 1000

typedef struct stack_s {
    int cursor;
    int *container;
}stack_t;

stack_t *create_stack()
{
    stack_t *stack;
    stack = (stack_t *)malloc(sizeof(stack));
    stack->cursor = -1;
    stack->container = (int *)malloc(sizeof(stack->container) * STACK_SIZE);
    return stack;
}

void push(stack_t *stack, int value)
{
    stack->cursor++;
    stack->container[stack->cursor] = value;
}

int pop(stack_t *stack)
{
    return stack->container[stack->cursor--];
}

int peek(stack_t *stack)
{
    return stack->container[stack->cursor];
}

int is_empty(stack_t *stack)
{
    return stack->cursor == -1 ? 1 : 0;
}

int solution(int H[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int i, count;
    stack_t *stack;
    stack = create_stack();
    
    count = 0;
    for(i = 0; i < N; i++)
    {
        while(!is_empty(stack) && H[i] < peek(stack))
            pop(stack);
        
        if(is_empty(stack) || H[i] > peek(stack))
        {
            push(stack, H[i]);
            count++;
        }
    }
    
    return count;
}

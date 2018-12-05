// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");
#define TRUE    1
#define FALSE   0

typedef struct stack_s {
    int cursor;
    int size;
    int *array;
}stack_t;

int is_full(stack_t *stack)
{
    return stack->cursor == stack->size - 1 ? TRUE : FALSE;
}

int is_empty(stack_t *stack)
{
    return stack->cursor == -1 ? TRUE : FALSE;
}

stack_t *create_stack(int size)
{
    stack_t *stack;
    stack = (stack_t *)malloc(sizeof(stack));
    stack->cursor = -1;
    stack->size = size;
    stack->array = (int *)malloc(sizeof(stack->array) * stack->size);
    
    return stack;
}

stack_t *push(stack_t *stack, int value)
{
    if(is_full(stack) == TRUE)
        return stack;
        
    stack->cursor++;
    stack->array[stack->cursor] = value;
    return stack;
}

int peek(stack_t *stack)
{
    if(is_empty(stack) == TRUE)
        return -1;
    
    return stack->array[stack->cursor];
}

int pop(stack_t *stack)
{
    if(is_empty(stack) == TRUE)
        return -1;
        
    return stack->array[stack->cursor--];
}

int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int i, index, count;
    stack_t *stack;
    stack = create_stack(N);
    
    for(i = 0; i < N; i++)
    {
        if(is_empty(stack) == TRUE || A[i] == peek(stack))
            push(stack, A[i]);
        else
            pop(stack);
    }
    
    index = -1;
    count = 0;
    for(i = 0; i < N; i++)
    {
        if(A[i] == peek(stack))
        {
            index = i;
            count++;
        }
    }
    
    if(count <= (N / 2))
        return -1;
        
    return index;
}

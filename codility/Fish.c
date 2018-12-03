#define STACK_SIZE 100 * 1000
#define UP      0
#define DOWN    1
#define TRUE    1
#define FALSE   0

typedef struct stack_s {
    int size;
    int cursor;
    int *array;
}stack_t;

stack_t *create_stack()
{
    stack_t *stack;
    stack = (stack_t *)malloc(sizeof(stack));
    stack->size = STACK_SIZE;
    stack->cursor = -1;
    stack->array = (int *)malloc(sizeof(stack->array) * stack->size);
    return stack;
}

int is_full(stack_t *stack)
{
    return stack->size - 1 == stack->cursor ? TRUE : FALSE;
}

int is_empty(stack_t *stack)
{
    return stack->cursor == -1 ? TRUE : FALSE;
}

int push(stack_t *stack, int value)
{
    /* error, stack is full */
    if(is_full(stack) == TRUE)
        return -1;
        
    stack->cursor++;
    stack->array[stack->cursor] = value;
    return 0;
}

int peek(stack_t *stack)
{
    return stack->array[stack->cursor];  
}

int pop(stack_t *stack)
{
    return stack->array[stack->cursor--];    
}

int count(stack_t *stack)
{
    return stack->cursor + 1;
}

int solution(int A[], int B[], int N) {
    // write your code in C99 (gcc 6.2.0)
    stack_t *stack;
    int i, first_ups;
    stack = create_stack();
    first_ups = 0;
    for(i = 0; i < N; i++)
    {
        if(B[i] == UP)
        {
            if(is_empty(stack) == FALSE)
                while(is_empty(stack) == FALSE && A[i] > peek(stack))
                    pop(stack);
            
            if(is_empty(stack) == TRUE)
                first_ups++;
        } 
        else
            push(stack, A[i]);
    }
    
    return count(stack) + first_ups;
}

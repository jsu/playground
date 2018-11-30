// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");
int stack_pos = -1;
int is_empty()
{
    if(stack_pos == -1)
        return 1;
    return 0;
}

void append(char *stack, char c)
{
    stack_pos++;
    stack[stack_pos] = c;
}

int pop(char *stack)
{
    char c;
    c = stack[stack_pos];
    stack_pos--;
    return c;
}

int solution(char *S) {
    // write your code in C99 (gcc 6.2.0)
    char *stack, c;
    int i, len;
    len = strlen(S);
    stack = (char *)malloc(sizeof(stack) * len / 2);
    
    if(len % 2)
        return 0;
        
    for(i = 0; i < len; i++)
    {
        if(S[i] == '{' || S[i] == '[' || S[i] == '(')
            append(stack, S[i]);
        else if(is_empty())
            return 0;
        else
        {
            c = pop(stack);
            if(c == '{' && S[i] == '}')
                continue;
            else if(c == '[' && S[i] == ']')
                continue;
            else if(c == '(' && S[i] == ')')
                continue;
            else
                return 0;
        }
    }
    
    if(is_empty())
        return 1;
    
    return 0;
}

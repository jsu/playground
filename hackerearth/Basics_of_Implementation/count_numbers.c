#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE (1 * 1024 * 1024) 
char *_BUFFER;

static int parseint()
{
    extern char *_BUFFER;
    int n;

    while(*_BUFFER < 0x21)
        _BUFFER++;
    for(n = 0; *_BUFFER >= 0x21; _BUFFER++)
        n = n * 10 + *_BUFFER - '0';
    
    return n;
}

int main()
{
    extern char *_BUFFER;
    char *_buffer;
    int t, n, state, count;

    _buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    _BUFFER = _buffer;
    fread(_BUFFER, sizeof(char), BUFFER_SIZE, stdin);
    t = parseint();
    while(t--)
    {
        n = parseint();
        _BUFFER++;
        state = 0;
        count = 0;
        while(n--)
        {
            if(*_BUFFER < 0x30 || *_BUFFER > 0x39)
                state = 0; 
            else if(state == 0)
            {
                state = 1;
                count++;
            }
            _BUFFER++;
        }
        printf("%d\n", count);
    }
    free(_buffer);

    return 0;
}

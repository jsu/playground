#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE (11 * 1024 * 1024) 
char *_BUFFER;
int BIT_SIZE, *_BIT;


void update(int x, int delta)
{
    extern int BIT_SIZE, *_BIT;
    int *ptr = _BIT;
    for(; x <= BIT_SIZE; x += x & -x)
        *(ptr + x) += delta;    
}

int query(int x)
{
    extern int *_BIT;
    int sum = 0, *ptr = _BIT;
    for(; x > 0; x -= x & -x)
        sum += *(ptr + x);
    return sum;
}

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
    /* t <= 100, q <= 1e4, size of string < 2e4, l <= r <= n */
    extern int BIT_SIZE, *_BIT;
    extern char *_BUFFER;
    int t, q, i, *_bit;
    char *input, *_buffer;

    _buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    _BUFFER = _buffer;
    fread(_BUFFER, sizeof(char), BUFFER_SIZE, stdin);
    t = parseint();
    while(t--)
    {
        BIT_SIZE = parseint();
        _bit = (int *)calloc(BIT_SIZE + 1, sizeof(int));
        _BIT = _bit;
        q = parseint();

        while(*_BUFFER < 0x21)
            _BUFFER++;
        input = _BUFFER;
        while(*_BUFFER > 0x57)
            _BUFFER++;

        while(q--)
        {
            update(parseint(), 1);
            update(parseint() + 1, -1);
        }

        for(i = 1; i <= BIT_SIZE; i++)
        {
            *input -= (query(i) % 26);
            if(*input < 'a')
                putchar(*input + 26);
            else
                putchar(*input);
            input++;
        }
        putchar('\n');
        free(_bit);
    }
    free(_buffer);

    return 0;
}

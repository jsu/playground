#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define _size 11000000
char _buffer[_size] = {'\0'};
char *_ptr = _buffer;

int BIT[102345];

void update(int x, int delta)
{
    
}

static int parseint()
{
    int n;

    while(*_ptr < 0x21)
        _ptr++;
    for(n = 0; *_ptr >= 0x21; _ptr++)
        n = n * 10 + *_ptr - '0';
    
    return n;
}

int main()
{
    /* t <= 100, q <= 1e4, size of string < 2e4, l <= r <= n */
    int t, q, n, i;
    int size = 20001, *counter;
    char *input;

    counter = (int *)calloc(size, sizeof(int));
    fread(_buffer, sizeof(char), _size, stdin);
    t = parseint();
    while(t--)
    {
        n = parseint();
        q = parseint();

        while(*_ptr < 0x21)
            _ptr++;
        input = _ptr;
        while(*_ptr > 0x57)
            _ptr++;

        while(q--)
        {
            counter[parseint() - 1] += 1;
            counter[parseint()] -= 1; 
        }

        for(i = 0; i < n; i++)
        {
            counter[i + 1] += counter[i];
            *input -= (counter[i] % 26);
            if(*input < 'a')
                putchar(*input + 26);
            else
                putchar(*input);
            input++;
            counter[i] = 0;
        }
        putchar('\n');
    }
    free(counter);

    return 0;
}

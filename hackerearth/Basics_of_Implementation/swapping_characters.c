#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE (1 * 1024 * 1024) 
char *B;

static int parseint()
{
    extern char *B;
    int n;

    while(*B < 0x21)
        B++;
    for(n = 0; *B >= 0x21; B++)
        n = n * 10 + *B - '0';
    
    return n;
}

int main()
{
    extern char *B;
    char *_buffer, *p_start, *p_end;
    int t, n;
    int i;

    _buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    B = _buffer;
    fread(B, sizeof(char), BUFFER_SIZE, stdin);
    t = parseint();
    while(t--)
    {
        n = parseint();
        B++;
        p_start = B;
        p_end = B + n - 1; 
        /* 
         * 1234567890
         * 2468097531
         * 123456789
         * 246897531
         */
        for(i = 1; i < n; i += 2)
            putchar(*(p_start + i));
        for(i = (n % 2) ? 0 : 1; i <= n; i += 2)
            putchar(*(p_end - i));
        putchar('\n');
        B += n;
    }
    free(_buffer);

    return 0;
}

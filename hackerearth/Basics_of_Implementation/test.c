#include <stdio.h>
 
#define _size (10 * 1024 * 1024) 
#define _xsize 11000000
char _buffer[_size] = {'\0'};
char *_ptr = _buffer;
 
int BIT[102345] = {0};
int n;
 
void update(int x, int delta)
{
    extern int n, BIT[];
    for(; x <= n; x += x & -x)
        BIT[x] += delta;    
}
 
int query(int x)
{
    extern int BIT[];
    int sum = 0;
    for(; x > 0; x -= x & -x)
        sum += BIT[x];
    return sum;
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
    extern int n;
    int t, q, i;
    char *input;
 
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
            /* BIT starts from 1 is a must */
            update(parseint(), 1);
            update(parseint() + 1, -1);
        }
 
        for(i = 1; i <= n; i++)
        {
            *input -= (query(i) % 26);
            if(*input < 'a')
                putchar(*input + 26);
            else
                putchar(*input);
            input++;
        }
        putchar('\n');
 
        for(i = 0; i <= n; i++)
            BIT[i] = 0;
    }
 
    return 0;
}

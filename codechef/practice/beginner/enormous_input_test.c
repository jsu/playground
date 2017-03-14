#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE (20 * 1024 * 1024)

char *BUFFER;

static int parseint()
{
    extern char *BUFFER;
    int n;

    while(*BUFFER < 0x21)
        BUFFER++;
    for(n = 0; *BUFFER >= 0x21; BUFFER++)
        n = n * 10 + *BUFFER - '0';
    
    return n;
}

int main(void)
{
    /* 
     * n, k <= 1e7
     * Ti < 1e9
     */
    extern char *BUFFER;
    int n, k, result = 0;
    char *_buffer;

    _buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    BUFFER = _buffer;
    fread(BUFFER, sizeof(char), BUFFER_SIZE, stdin);
    n = parseint();
    k = parseint();
    while(n--)
        if(parseint() % k == 0)
            result++;
    printf("%d\n", result);
    free(_buffer);

    return 0;
}

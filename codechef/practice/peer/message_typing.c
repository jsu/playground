#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE (10 * 1024 * 1024)
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
    /* 1 <= t <= 1e4, 1 <= s <= 1000 */
    int t, sum;
    char *buffer;
    
    buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    BUFFER = buffer;
    fread(BUFFER, sizeof(char), BUFFER_SIZE, stdin);
    t = parseint();
    while(t--)
    {
        sum = 0;
        while(*BUFFER < 0x61)
            BUFFER++;
        while(*BUFFER != '\n')
        {
            sum += *BUFFER - 96;
            BUFFER++; 
        }

        printf("%d\n", sum);
    }
    free(buffer);
    return 0;
}

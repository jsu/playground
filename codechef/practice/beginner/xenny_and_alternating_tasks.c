#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
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
    extern char *BUFFER;
    char *buffer;
    int t, n, i;
    uint64_t results[2];

    buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    BUFFER = buffer;
    fread(BUFFER, sizeof(char), BUFFER_SIZE, stdin);
    t = parseint();
    while(t--)
    {
        n = parseint();
        results[0] = 0;
        results[1] = 0;
        for(i = 0; i < n; i++)
            results[i % 2] += parseint();
        for(i = 1; i <= n; i++)
            results[i % 2] += parseint();

        if(results[0] > results[1])
            printf("%" PRIu64 "\n", results[1]);
        else
            printf("%" PRIu64 "\n", results[0]);
    }
    free(buffer);
    return 0;
}

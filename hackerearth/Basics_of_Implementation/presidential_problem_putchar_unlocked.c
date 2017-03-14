#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int parseint(void)
{
    int c, n;

    for(c = 0; c < 0x21;)
        c = getchar_unlocked();
    for(n = 0; c >= 0x21; c = getchar_unlocked())
        n = n * 10 + c - '0';
    
    return n;
}

int main()
{
    /* t <= 100, q <= 1e4, size of string < 2e4, l <= r <= n */
    int c, t, q, n, i, j;
    int size = 20001, *counter;
    char *buffer;

    counter = (int *)calloc(size, sizeof(int));
    buffer = (char *)malloc(sizeof(char) * size);
    t = parseint();
    while(t--)
    {
        j = n = parseint();
        q = parseint();
        i = 0;
        while((c = getchar_unlocked()) != EOF && c != '\n')
            if(j--)
                buffer[i++] = c;
        buffer[i] = '\0';

        while(q--)
        {
            counter[parseint() - 1] += 1;
            counter[parseint()] -= 1; 
        }

        for(i = 0; buffer[i] != '\0'; i++)
        {
            counter[i + 1] += counter[i];
            counter[i] %= 26;
            buffer[i] -= counter[i];
            if(buffer[i] < 'a')
                putchar(buffer[i] + 26);
            else
                putchar(buffer[i]);
            counter[i] = 0;
        }
        putchar('\n');
    }
    free(counter);
    free(buffer);

    return 0;
}

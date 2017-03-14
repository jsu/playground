#include <stdio.h>

static int parseint(void)
{
    int c, n;

    for(c = 0; c < 0x21;)
        c = getchar();
    for(n = 0; c >= 0x21; c = getchar())
        n = n * 10 + c - '0';

    return n;
}

int main(void)
{
    int i;

    while(scanf("%d", &i) && i != 42)
        printf("%d\n", i);

    return 0;
}

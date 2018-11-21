#include <stdio.h>

int main(void)
{
    char c;

    printf("Hello, World.\n");
    while((c = getchar()) != EOF)
        putchar(c);
    return 0;
}

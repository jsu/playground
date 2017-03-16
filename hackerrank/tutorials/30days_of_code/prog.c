#include <stdio.h>

int main(void)
{
    int i, j, n;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        for(j = n - 1; j > i; j--)
            putchar(' ');
        for(j = 0; j <= i; j++)
            putchar('#');
        putchar('\n');
    }
    return 0;
}

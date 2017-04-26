#include <stdio.h>

int factorial(int n)
{
    return n > 1 ? n * factorial(n - 1) : n;
}

int main(void)
{
    int n;
    scanf("%d", &n);
    printf("%d\n", factorial(n));
    return 0;
}

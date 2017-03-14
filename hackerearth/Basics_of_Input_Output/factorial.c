#include <stdio.h>

int main(int argc, char **argv)
{
    unsigned i, j;

    scanf("%d", &i);

    j = 1;
    for(j = 1 ; i > 1; i--)
        j *= i;

    printf("%d\n", j);

    return 0;
}

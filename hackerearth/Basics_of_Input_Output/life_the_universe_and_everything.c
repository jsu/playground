#include <stdio.h>

int main(int argc, char **argv)
{
    unsigned i;

    while(scanf("%d", &i) && i != 42)
        printf("%d\n", i);

    return 0;
}

#include <stdio.h>

int main(int argc, char **argv)
{
    unsigned l, r, k, counter;

    scanf("%d %d %d", &l, &r, &k);

    counter = 0;
    for(; l <= r ; l++)
        if(!(l % k))
            counter++;

    printf("%d", counter);

    return 0;
}

#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    uint64_t answer = 1;
    uint16_t size, input;

    scanf("%hu", &size);
    while(size--)
    {
        scanf("%hu", &input);
        answer = (input * answer) % (1000000000 + 7);
    }

    printf("%llu\n", answer);

    return 0;
}

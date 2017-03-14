#include <stdio.h>
#include <stdint.h>

static uint32_t parseint(void)
{
    int8_t c;
    uint32_t n;

    for(c = 0; c < 0x21;)
        c = getchar_unlocked();
    for(n = 0; c >= 0x21; c = getchar_unlocked())
        n = n * 10 + c - '0';

    return n;
}

int main(int argc, char **argv)
{
    /* n <= 1e5, a <= 1e9 */
    uint32_t i = 0, n;
    uint64_t answers[3] = {0};

    n = parseint();
    for(;;)
    {
        /* Faster without modulo operation? */
        if(i++ >= n)
            break;
        answers[0] += parseint();
        if(i++ >= n)
            break;
        answers[1] += parseint();
        if(i++ >= n)
            break;
        answers[2] += parseint();

        /* Modulo Operation
        answers[i % 3] += parseint();
        */
        
    }
    printf("%llu %llu %llu\n", answers[0], answers[1], answers[2]);

    return 0;
}

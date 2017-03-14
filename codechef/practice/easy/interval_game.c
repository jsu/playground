#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE (64 * 1024 * 1024)
char *BUFFER;

static int parseint()
{
    extern char *BUFFER;
    int n;

    while(*BUFFER < 0x21)
        BUFFER++;
    for(n = 0; *BUFFER >= 0x21; BUFFER++)
        n = n * 10 + *BUFFER - '0';
    
    return n;
}

int main(void)
{
    extern char *BUFFER;
    char *buffer;
    int64_t *p_start, *p_end, *p_current, *p_max_ending;
    int t, n, m, b, i, j;
    int64_t max_sum, sum, score, *a;

    buffer = (char *)malloc(sizeof(*buffer) * BUFFER_SIZE);
    BUFFER = buffer;
    fread(BUFFER, sizeof(*BUFFER), BUFFER_SIZE, stdin);
    t = parseint();
    while(t--)
    {
        n = parseint();
        m = parseint();
        a = (int64_t *)malloc(sizeof(*a) * n);
        for(i = 0; i < n; i++)
            a[i] = parseint();
        p_start = a;
        p_end = p_start + n - 1;
        score = 0;
        for(i = 0; i < m; i++)
        {
            b = parseint();
            p_current = p_start;
            sum = 0;
            for(j = 0; j < b; j++)
                sum += *(p_current++);
            max_sum = sum;
            p_max_ending = p_current - 1;
            for(; p_current <= p_end; p_current++)
            {
                sum = *p_current + sum - *(p_current - b);
                if(max_sum < sum)
                {
                    max_sum = sum;
                    p_max_ending = p_current; 
                }
            }
            p_start = p_max_ending - b + 2;
            p_end = p_max_ending - 1;
            score = i % 2 ? score - max_sum : score + max_sum;
        }
        printf("%" PRIu64 "\n", score);
        free(a);
    }
    free(buffer);

    return 0;
}

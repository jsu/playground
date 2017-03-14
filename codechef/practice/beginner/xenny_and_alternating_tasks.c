#include <stdio.h>
#include <stdint.h>

int main(void)
{
    int t, n, i, r;
    uint64_t results[2];

    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n); 
        results[0] = 0;
        results[1] = 0;
        for(i = 0; i < n; i++)
        {
            scanf("%d", &r); 
            results[i % 2] += r;
        }
        for(i = 1; i <= n; i++)
        {
            scanf("%d", &r); 
            results[i % 2] += r;
        }

        if(results[0] > results[1])
            printf("%llu", results[1]);
        else
            printf("%llu", results[0]);
    }
    return 0;
}

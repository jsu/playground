#include <stdio.h>
#include <stdlib.h>

static int parseint(void)
{
    int c, n;

    for(c = 0; c < 0x21;)
        c = getchar();
    for(n = 0; c >= 0x21; c = getchar())
        n = n * 10 + c - '0';

    return n;
}

int main(void)
{
    int t, n, i, j, k, max;
    int *temp, *sums;

    t = parseint();
    while(t--)
    {
        n = parseint();
        temp = (int *)malloc(sizeof(int) * n);
        sums = (int *)malloc(sizeof(int) * n);
        max = 0;
        for(i = 0; i < n; i++)
        {
            for(j = 0; j <= i ; j++)
            {
                k = parseint();
                if(i == 0)
                    sums[j] = k;
                else if(j == 0)
                    sums[j] = temp[j] + k;
                else if(j == i)
                    sums[j] = temp[j - 1] + k; 
                else if(temp[j] >= temp[j - 1])
                    sums[j] = temp[j] + k; 
                else if(temp[j] < temp[j - 1])
                    sums[j] = temp[j - 1] + k; 
                if(sums[j] > max)
                    max = sums[j];
            }
            if(i < n)
                for(j = 0; j <= i; j++)
                    temp[j] = sums[j]; 
        }
        printf("%d\n", max);
        free(temp);
        free(sums);
    }
    return 0;
}

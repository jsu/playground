#include <stdio.h>

unsigned int gcd(unsigned int u, unsigned int v)
{
    if(u == v)
        return u;
    if(u == 0)
        return v;
    if(v == 0)
        return u;

    if(~u & 1)
    {
        if(v & 1)
           return gcd(u >> 1, v);
        else
           return gcd(u >> 1, v >> 1) << 1; 
    }

    if(~v & 1)
        return gcd(u, v >> 1);
    if(u > v)
        return gcd((u - v) >> 1, v);
    
    return gcd((v - u) >> 1, u);
}

int main(void)
{
    unsigned int n, sum;
    int t;
    int i, j;

    scanf("%d", &t);
    while(t--)
    {
        scanf("%ud", &n);
        sum = 0;
        for(i = 2; i < n; i++)
            for(j = n; j > 0; j /= i)
                sum += j % i;
        printf("%d\n", (n - 2) / gcd(sum, n - 2));
    }
    return 0;
}

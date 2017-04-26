#include <stdio.h>

int main(void)
{
    int n, max, count;

    scanf("%d", &n);
    max = count = 0;
    while(n)
    {
        if(n & 0x1)
           count++;
        else
           count = 0;
        if(count > max) 
            max = count;
        n >>= 1;
    }
    printf("%d\n", max);

    return 0;
}

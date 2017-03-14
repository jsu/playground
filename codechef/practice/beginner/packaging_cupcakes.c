#include <stdio.h>

int main(void)
{
    /* 1 <= t <= 1000, 2 <= n <= 1e8 */
    int t, n;

    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n); 
        printf("%d\n", n / 2 + 1);
    }

    return 0;
}

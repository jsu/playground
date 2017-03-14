#include <stdio.h>

int main(void)
{
    /*
     * 0 < t < 1e5
     * 1 <= n <= 1e9
     */
    int t;
    unsigned n, result;

    scanf("%d", &t);
    while(t--)
    {
        result = 0;
        scanf("%u", &n);
        while(n >= 5)
        {
            n = n / 5;
            result += n;
        }
        printf("%u\n", result);
    }

    return 0;
}

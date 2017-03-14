#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* n <= 10000, 1 <= s, t <= 1000 */
    int n, s, t, ts = 0, tt = 0, r = 0;

    scanf("%d", &n);
    while(n--)
    {
        scanf("%d%d", &s, &t); 
        ts += s;
        tt += t;
        if(abs(ts - tt) > abs(r))
           r = ts - tt; 
    }
    printf("%d %d\n", r > 0 ? 1 : 2, abs(r));

    return 0;
}

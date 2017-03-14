#include <stdio.h>

int main(void)
{
    int i, t, p;
    scanf("%d", &t);

    while(t--)
    {
        scanf("%d", &p);
        if(p > 2048)
        {
            i = p / 2048;
            p %= 2048;
        }
        else
            i = 0;

        for(; p > 0; p -= p & -p)
            i++;
        printf("%d\n", i);
    }
    return 0;
}

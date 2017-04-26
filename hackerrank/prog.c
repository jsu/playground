#include <stdio.h>

int main(void)
{
    int x1, v1, x2, v2;
    scanf("%d %d %d %d", &x1, &v1, &x2, &v2);
    if(v1 <= v2)
        printf("NO\n");
    else if((x1 - x2) % (v2 - v1) == 0)
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}

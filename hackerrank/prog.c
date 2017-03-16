#include <stdio.h>

int main(void)
{
    int n, px, py, qx, qy;

    scanf("%d", &n);
    while(n--)
    {
        scanf("%d%d%d%d", &px, &py, &qx, &qy);
        printf("%d %d\n", qx - px + qx, qy - py + qy); 
    }

    return 0;
}

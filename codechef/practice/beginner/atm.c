#include <stdio.h>

int main(void)
{
    /*
     * 0 < x <= 2000
     * 0 <= y <= 2000
     */
    int x;
    float y;

    scanf("%d%f", &x, &y);

    if(x % 5 == 0 && x + 0.5 <= y)
        printf("%.2f\n", y - x - 0.5);
    else
        printf("%.2f\n", y);

    return 0;
}

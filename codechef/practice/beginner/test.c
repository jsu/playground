#include <stdio.h>

int main(void)
{
    int array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *p_low, *p_high;
    p_low = array;
    p_high = &array[9];
    printf("%d %d\n", *p_low, *p_high);
    p_low++;
    p_high--;
    printf("%d %d\n", *p_low, *p_high);
    while(p_low != p_high)
    {
        p_low++;
        printf("%d\n", *p_low);
    }
    return 0;
}

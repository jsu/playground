#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, *a;
    int i, max, *p_current, current_height, sum;

    scanf("%d", &n);
    a = (int *)malloc(sizeof(*a) * n);
    max = 0;
    for(i = 0; i < n; i++)
    {
        scanf("%d", a + i);
        if(*(a + i) > *(a + max))
            max = i;
    }

    current_height = *a;
    p_current = a + 1;
    sum = 0;
    for(i = 1; i < max; i++)
    {
        if(*p_current < current_height)
            sum += current_height - *p_current;
        else if(*p_current > current_height)
            current_height = *p_current;
        p_current++;
    }

    current_height = *(a + n - 1);
    p_current = a + n - 2;
    for(i = n - 2; i > max; i--)
    {
        if(*p_current < current_height)
            sum += current_height - *p_current;
        else if(*p_current > current_height)
            current_height = *p_current;
        p_current--;
    }

    printf("%d\n", sum);

    free(a);
    return 0;
}

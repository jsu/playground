#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compar(const void *a, const void *b)
{
    return *(int *)a > *(int *)b ? 1 : -1;
}

int main(void)
{
    int n, *a;
    int i, result;

    scanf("%d", &n);
    a = (int *)malloc(sizeof(*a) * n);
    for(i = 0; i < n; i++)
        scanf("%d", a + i);
    qsort(a, n, sizeof(*a), compar);
    result = 0;
    for(i = 0; i < n - 1; i++)
    {
        if(*(a + i + 1) - *(a + i) > 1)
        {
            result = 1;
            break; 
        }
    }
    if(result == 0)
        printf("YES\n");
    else
        printf("NO\n");
    free(a);
    return 0;
}

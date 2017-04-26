#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int **a;
    int i, j, length = 6, max, count;

    a = (int **)malloc(sizeof(*a) * length);
    for(i = 0; i < length; i++)
    {
        *(a + i) = (int *)malloc(sizeof(**a) * length);
        for(j = 0; j < length; j++)
            scanf("%d", *(a + i)+j);
    }
    max = count = -9 * 7;
    for(i = 0; i < length - 2 ; i++)
    {
        for(j = 0; j < length - 2; j++)
        {
            count = *(*(a + i) + j) + *(*(a + i) + j + 1) + *(*(a + i) + j + 2)
                  + *(*(a + i + 1) + j + 1)
                  + *(*(a + i + 2) + j) + *(*(a + i + 2) + j + 1) + *(*(a + i + 2) + j + 2); 
            if(count > max)
                max = count;
        }
    }
    printf("%d\n", max);
    for(i = 0; i < length; i++)
        free(*(a + i));
    free(a);
    return 0;
}

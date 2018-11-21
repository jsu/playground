#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i, n, *a, *ptr;

    scanf("%d\n", &n);
    a = (int *)malloc(n * sizeof(a));
    ptr = a;
    for(i = 0; i < n; i++)
        scanf("%d", ptr++); 
    for(i = 0; i < n; i++)
        printf("%d ", *(--ptr));
    return 0;
}

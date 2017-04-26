#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    int i, length;
    char c, *a, *end;
    scanf("%d", &n);
    scanf("\n");
    while(n--)
    {
        a = NULL;
        length = 0;
        while((c = getchar()) != EOF && c != '\n')
        {
            length++;
            a = (char *)realloc(a, sizeof(*a) * length);
            *(a + length - 1) = c;
        }
        end = a + length - 1;
        /*
         * a = 97, 0x61
         * z = 122, 0x7a
         */
        for(i = 0; i < length / 2 + length % 2; i++)
        {
            *(a + i) = *(a + i) - 0x60 + *(end - i) - 0x60;
            if(*(a + i) > 0x1a)
                *(a + i) -= 0x1a;
            *(a + i) += 0x60;
            putchar(*(a + i));
        }
        for(i = length / 2 - 1; i >= 0; i--)
            putchar(*(a + i));
        putchar('\n');
        free(a);
    }
    return 0;
}

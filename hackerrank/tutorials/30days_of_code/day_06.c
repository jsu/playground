#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int i, t, length;
    char c, *buffer;

    scanf("%d\n", &t);
    while(t--)
    {
        buffer = NULL;
        for(i = 0; (c = getchar()) != EOF && c != '\n'; i++)
        {
            buffer = (char *)realloc(buffer, (i + 1) * sizeof(buffer));
            *(buffer + i) = c;
        }
        length = i;
        for(i = 0; i < length; i += 2)
            putchar(*(buffer + i));
        putchar(' ');
        for(i = 1; i < length; i += 2)
            putchar(*(buffer + i));
        putchar('\n');
    }
    return 0;
}

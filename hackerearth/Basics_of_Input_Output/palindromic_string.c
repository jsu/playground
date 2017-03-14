#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    int8_t c, i, result;
    char input[101];
    char *p_start = input;
    char *p_end;

    for(i = 0; i < 101 && (c = getchar()) != EOF; i++)
        input[i] = c; 

    p_end = &input[i];
    result = 1;
    i /= 2;
    while(i--)
    {
        if(*(p_start++) != *(--p_end))
        {
            result = 0;
            break;
        }
    }

    if(result)
        printf("YES");
    else
        printf("NO");

    return 0;
}

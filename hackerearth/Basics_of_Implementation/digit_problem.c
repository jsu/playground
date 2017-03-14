#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    /* x <= 1e18, k <= 1e9 */
    uint8_t i;
    int k;
    char buffer[19];

    scanf("%s%d", buffer, &k);
    for(i = 0; buffer[i] != '\0' ; i++)
    {
        if(buffer[i] != '9' && k-- > 0)
            putchar('9');
        else
            putchar(buffer[i]);
    }
    putchar('\n');

    return 0;
}

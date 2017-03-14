#include <stdio.h>

int main(int argc, char **argv)
{
    int i, t, n, c;
    int prime_table[12] = {67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113};

    scanf("%d\n", &t);
    while(t--)
    {
        scanf("%d\n", &n);
        while(n-- && (c = getchar()) != EOF && c != '\n')
        {
            for(i = 0; i < 11; i++)
            {
                if(c > (113 + 109) / 2)
                {
                    c = 113;
                    break;
                }
                else if(c <= (prime_table[i] + prime_table[i+1]) / 2) 
                {
                    c = prime_table[i];
                    break;
                }
            }
            putchar(c); 
        }
        putchar('\n');
    }

    return 0;
}

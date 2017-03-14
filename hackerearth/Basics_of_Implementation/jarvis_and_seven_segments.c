#include <stdio.h>
#define MAX_SUM (6 - 1) * 7

int main(int argc, char **argv)
{
    int digit_map[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
    int c, t, i, j;
    char buffer[8];
    unsigned number, results, temp;

    scanf("%d\n", &t);
    while(t--)
    {
        results = MAX_SUM;
        scanf("%d\n", &i); 
        while(i--)
        {
            temp = 0;
            j = 0;
            while((c = getchar_unlocked()) != ' ' && c != '\n' && c != EOF)
            {
                if(temp >= results)
                    continue;
                buffer[j++] = c;
                temp += digit_map[c - '0'];
            }

            if(temp < results)
            {
                buffer[j] = '\0';
                sscanf(buffer, "%d", &number);
                results = temp;
            }
        }
        printf("%d\n", number);
    }

    return 0;
}

#include <stdio.h>
#include <stdint.h>

int main(void)
{
    /*
     * 1 <= t <= 25
     * 0 <= Ai <= 1
     * 1 <= N <= 1e5
     */
    int c;
    int8_t i, t, late;
    char buffer[3];
    unsigned due;

    i = 0;
    while((c = getchar()) != EOF && c != '\n')
        buffer[i++] = c;
    buffer[i] = '\0';
    sscanf(buffer, "%hhd", &t);
    while(t--)
    {
        late = 0;
        due = 0;
        /* By pass n */
        while((c = getchar()) != EOF && c != '\n')
            continue;
        while((c = getchar()) != EOF && c != '\n')
        {
            if(c == ' ')
                continue;

            if(c == '0')
            {
                late = 1;
                due += 1000;
            }

            if(late)
                due += 100;
        }
        printf("%d\n", due);
    }

    return 0;
}

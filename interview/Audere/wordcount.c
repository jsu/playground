#include <stdio.h>
#define IN   1  /* inside a word */
#define OUT  0  /* outside a word */
/* count lines, words, and characters in input */
int main(int argc, char **argv)
{
    char *s1 = "Wetest coders. Give us a try?";
    char *s2 = "forget CVs. . Save time. x x";
    char *s3 = "as df";
    char *s4 = " asdf";
    char *s5 = "asdf ";
    char *p, c;
    int counter, max, state;

    p = s3;
    max = counter = 0;
    state = OUT;
    while(*p != '\0')
    {
        if(*p == '.' || *p == '!' || *p == '?')
        {
            state = OUT;
            if(counter > max)
                max = counter;
            counter = 0;
        }
        else if(*p == ' ')
            state = OUT;
        else if(state == OUT)
        {
            state = IN;
            counter++;
        }
        c = *p;
        p++;
    }
    if(c == ' ' || state == IN)
        max = counter;
    printf("%d\n", max);

	return 0;
}

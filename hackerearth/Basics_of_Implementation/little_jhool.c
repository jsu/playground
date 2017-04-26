#include <stdio.h>

int main(void)
{
    int counter, flag;
    char c, pre;
    pre = NULL;
    flag = 0;
    counter = 1;
    while((c = getchar()) != EOF && c != '\n' && counter < 6)
    {
        counter = c == pre ? counter + 1 : 1;
        pre = c;
    }
    if(counter >= 6)
        printf("Sorry, sorry!\n");
    else
        printf("Good luck!\n");
    return 0;
}

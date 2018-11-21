#include <stdio.h>

#define MAX 40

int main(int argc, char **argv)
{
    int i = 4;
    double d = 4.0;
    char s[] = "HackerRank ";

    int j;
    double e;
    char c, t[MAX], *ptr;

    scanf("%d %lf\n", &j, &e);
    ptr = t;
    while((c = getchar()) != EOF && c != '\n')
        *(ptr++) = c;
    printf("%d\n%.1f\n%s%s", i + j, d + e, s, t); 

    return 0;
}

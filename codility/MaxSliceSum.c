// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");
#include <limits.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int i, e, s;
    e = 0;
    s = INT_MIN;
    for(i = 0; i < N; i++)
    {
        e = max(A[i], e + A[i]);
        s = max(s, e);
    }
    return s;
}

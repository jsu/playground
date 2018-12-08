// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");
#include <limits.h>
int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int i, min, max, profit;
    profit = 0;
    min = INT_MAX;
    max = INT_MIN;
    for(i = 0; i < N; i++)
    {
        if(A[i] < min)
        {
            min = A[i];
            max = INT_MIN;
        }
            
        if(A[i] > max)
        {
            max = A[i];
            
            if(max - min > profit)
                profit = max - min;
        }
    }
    return profit;
}

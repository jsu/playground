// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");
#include <math.h>

int solution(int N) {
    // write your code in C99 (gcc 6.2.0)
    int i, count, sqrt_N;
    
    if(N == 1)
        return 1;
        
    count = 0;
    /* 
     * precaculate sqrt(N) to avoid i * i < N being calc'd every time
     */
    sqrt_N = sqrt(N);
    for(i = 1; i <= sqrt_N; i++)
        if(N % i == 0)
            count += 2;
    
    if(sqrt_N * sqrt_N == N)
        count--;
        
    return count;
}

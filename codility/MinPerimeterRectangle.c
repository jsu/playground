// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");
#include <math.h>

int solution(int N) {
    // write your code in C99 (gcc 6.2.0)
    int i, sqrt_N;
    
    sqrt_N = sqrt(N);
    for(i = sqrt_N; i > 0; i--)
        if(N % i == 0)
            break;
            
    return 2 * (i + (N / i));
}

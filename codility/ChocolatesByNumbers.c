// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");

int gcd(int a, int b)
{
    if(a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}

int solution(int N, int M) {
    // write your code in C99 (gcc 6.2.0)
    /* (N * M / gcd(N, M)) / M => N / gcd(N, M) */ 
    return N / gcd(N, M);
}

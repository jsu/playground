// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");

int solution(int N) {
    // write your code in C99 (gcc 6.2.0)
    int i, count;
    count = 0;
    for(i = 1; i * i < N; i++)
        if(N % i == 0)
            count += 2;
    
    if(i * i == N)
        count++;

    return count;
}

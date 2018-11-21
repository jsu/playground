int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int i, *p;
    p = (int *)calloc(N + 1, sizeof(p));
    
    for(i = 0; i < N; i++)
        *(p + *(A + i)) = 1;
    
    for(i = 1; i < N + 1; i++)
        if(*(p + i) == 0)
            return i;
    
    return i;
}

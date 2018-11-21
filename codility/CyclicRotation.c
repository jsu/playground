struct Results solution(int A[], int N, int K) {
    struct Results result;
    // write your code in C99 (gcc 6.2.0)
    
    if(N == 0)
        return result;
        
    int i, r, counter, *p;
    p = (int *)malloc(N * sizeof(p));
    
    r = N - K % N;
    counter = 0;
    
    for(i = r; i < N; i++)
        *(p + counter++) = *(A + i);
        
    for(i = 0; i < r; i++)
        *(p + counter++) = *(A + i);
    
    result.A = p;
    result.N = N;
    return result;
}

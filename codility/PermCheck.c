int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int i, *p;
    p = (int *)calloc(N, sizeof(p));
    for(i = 0; i < N; i++)
    {
        /* out of bounds */
        if(*(A + i) > N)
            return 0;
            
        /* repeated */
        if(*(p + *(A + i)) == 1)
            return 0;
        
        *(p + *(A + i)) = 1;
    }
            
    return 1;
}

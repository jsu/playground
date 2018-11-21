int solution(int X, int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int i, *p, sum;
    p = (int *)calloc(X, sizeof(p));
    
    for(i = 0, sum = 0; i < N; i++)
    {
        if(*(p + *(A + i)) == 0)
        {
            if(++sum == X)
                return i;
            *(p + *(A + i)) = 1;
        }
    }
    
    return -1;
}

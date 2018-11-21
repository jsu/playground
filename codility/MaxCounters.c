int max(int a, int b)
{
    return a > b ? a : b;
}

struct Results solution(int N, int A[], int M) {
    struct Results result;
    // write your code in C99 (gcc 6.2.0)
    int i, *p, li, cm;
    p = (int *)calloc(N, sizeof(p));
    li = cm = 0;
    
    for(i = 0; i < M; i++)
    {
        if(*(A + i) > N)
            li = cm;
        else
        {
            *(p + *(A + i) - 1) = max(*(p + *(A + i) - 1), li);
            *(p + *(A + i) - 1) += 1;
            cm = max (*(p + *(A + i) - 1), cm);
        }
    }
    
    for(i = 0; i < N; i++)
        *(p + i) = max(*(p + i), li);

    result.C = p;
    result.L = N;
    return result;
}

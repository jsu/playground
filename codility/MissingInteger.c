#define SIZE_P 1000000

int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    /* -1e6 <= element <= 1e6 */
    int i, *p;
    p = (int *)calloc(SIZE_P, sizeof(p));
    for(i = 0; i < N; i++)
        if(*(A + i) > 0)
            *(p + *(A + i)) = 1;
            
    for(i = 1; i < SIZE_P; i++)
        if(*(p + i) == 0)
            return i;
            
    return 1;
}

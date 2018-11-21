int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int i, num;
    
    for(i = 0, num = 0; i < N; i++)
        num ^= *(A + i);
    
    return num;
}

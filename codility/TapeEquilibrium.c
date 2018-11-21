int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int i, left, right, diff, min;
    
    left = *A;
    for(i = 1, right = 0; i < N; i++)
        right += *(A + i);
    min = diff = abs(left - right);
    
    for(i = 1; i < N - 1; i++)
    {
        left += *(A + i);
        right -= *(A + i);
        diff = abs(left - right);
        if(diff < min)
            min = diff;
    }
    
    return min;
}

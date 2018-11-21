int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int i, total, counter;
    
    counter = 0;
    total = 0;
    
    for(i = 0; i < N; i++)
    {
        if(*(A + i) == 0)
            counter++;
        else
            total += counter;
            
        if(total > 1000000000)
            return -1;
    }
    
    return total;
}

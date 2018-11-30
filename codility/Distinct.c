// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");
#define IN  1
#define OUT 0

int compare (const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
  
int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int i, prev, count, status;
    
    qsort (A, N, sizeof(*A), compare);
    status = OUT;
    prev = 0;
    count = 0;
    for(i = 0; i < N; i++)
    {
        if(status == OUT)
        {
            count++;
            status = IN;
        }
        else if(A[i] != prev)
            count++;
        prev = A[i];
    }
    return count;
}

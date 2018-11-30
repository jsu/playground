TSET  -1

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int i, a, b;
    
    qsort(A, N, sizeof(*A), compare);
    a = b = NOTSET;
    for(i = 0; i < N; i++)
    {
        if(A[i] < 0)
            continue;
            
        if(a == NOTSET)
            a = A[i];
        else if(b == NOTSET)
            b = A[i];
        else
        {
			/*
			 * a + b > c => a > c - b
             * to avoid int overflow
             */
            if(a > A[i] - b)
                return 1;
            
            a = b;
            b = A[i];
        }
    }
    
    return 0;
}


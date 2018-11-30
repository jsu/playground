/* Solution 1 with sort */
int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    qsort(A, N, sizeof(*A), compare);
    
    if(A[N - 1] > 0 && A[0] * A[1] > A[N - 2] * A[N - 3])
        return A[0] * A[1] * A[N - 1];
    else
        return A[N - 1] * A[N - 2] * A[N - 3];
}


/* Solution 2 with book keeping */
/* a < b */
typedef struct min_s {
    int a;
    int b;
}min_t;

/* a > b > c */
typedef struct max_s {
    int a;
    int b;
    int c;
}max_t;

void update_min(min_t *min_values, int number)
{
    if(number < min_values->a)
    {
        min_values->b = min_values->a;
        min_values->a = number;
    }
    else if(number < min_values->b)
        min_values->b = number;
}

void update_max(max_t *max_values, int number)
{
    if(number > max_values->a)
    {
        max_values->c = max_values->b;
        max_values->b = max_values->a;
        max_values->a = number;
    }
    else if(number > max_values->b)
    {
        max_values->c = max_values->b;
        max_values->b = number;
    }
    else if(number > max_values->c)
        max_values->c = number;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int solution(int A[], int N) {
    // write your code in C99 (gcc 6.2.0)
    int i;
    min_t min_values;
    max_t max_values;
    min_values.a = min_values.b = 0;
    max_values.a = max_values.b = max_values.c = 0;
    
    for(i = 0; i < N; i++)
    {
        if(i == 0)
            max_values.a = min_values.a = A[i];
        else if(i == 1)
        {
            if(A[i] < min_values.a)
            {
                min_values.b = min_values.a;
                min_values.a = A[i];
            }
            else
                min_values.b = A[i];
            
            if(A[i] > max_values.a)
            {
                max_values.b = max_values.a;
                max_values.a = A[i];
            }
            else
                max_values.b = A[i];
        }
        else if(i == 2)
        {
            if(A[i] > max_values.a)
            {
                max_values.c = max_values.b;
                max_values.b = max_values.a;
                max_values.a = A[i];
            }
            else if(A[i] > max_values.b)
            {
                max_values.c = max_values.b;
                max_values.b = A[i];
            }
            else
                max_values.c = A[i];
            update_min(&min_values, A[i]);
        }
        else
        {
            update_min(&min_values, A[i]);
            update_max(&max_values, A[i]);
        }
    }
    
    return max(max_values.a * max_values.b * max_values.c,
               min_values.a * min_values.b * max_values.a);
}

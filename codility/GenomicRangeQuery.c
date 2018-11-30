#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");

typedef struct acgt_s {
    int a;
    int c;
    int g;
    int t;
}acgt_t;

struct Results {
	int *A;
	int M;
};

struct Results solution(char *S, int P[], int Q[], int M) {
    struct Results result;
    // write your code in C99 (gcc 6.2.0)
    /* acgt
       1234 */
    int i, a, c, g, t, len, *results;
    results = (int *)malloc(sizeof(results) * M);
    
    len = strlen(S);
    acgt_t *acgt_a, p, q;
    acgt_a = (acgt_t *)calloc(len + 1, sizeof(acgt_a));
    a = c = g = t = 0;
    for(i = 0; i < len; i++)
    {
        if(S[i] == 'A')
            a++;
        else if(S[i] == 'C')
            c++;
        else if(S[i] == 'G')
            g++;
        else if(S[i] == 'T')
            t++;
        
        acgt_a[i + 1].a = a;
        acgt_a[i + 1].c = c;
        acgt_a[i + 1].g = g;
        acgt_a[i + 1].t = t;
    }
    
    for(i = 0; i < M; i++)
    {
        p = acgt_a[P[i]];
        q = acgt_a[Q[i] + 1];
        if(q.a - p.a > 0)
            results[i] = 1;
        else if(q.c - p.c > 0)
            results[i] = 2;
        else if(q.g - p.g > 0)
            results[i] = 3;
        else if(q.t - p.t > 0)
            results[i] = 4;
    }
    
    result.A = results;
    result.M = M;
    return result;
}

int main(int argc, char **argv)
{
    struct Results r;
    char *S = "CAGCCTA";
    int i, M = 3;
    int P[] = {2, 5, 0};
    int Q[] = {4, 5, 6};
    r = solution(S, P, Q, M); 
    for(i = 0; i < r.M; i++)
        printf("%d: %d\n", i, r.A[i]);

    return 0;
}

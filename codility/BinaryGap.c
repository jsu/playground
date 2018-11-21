#define TRUE    1
#define FALSE   0

int solution(int N) {
    // write your code in C99 (gcc 6.2.0)
    int i, pos, max, counter, enabled;
    
    enabled = FALSE;
    max = counter = 0;
    
    /* 2^31 = 2,147,483,648 */
    for(i = 0; i < 31; i++)
    {
        pos = N >> i;
        if(pos & 1)
        {
            enabled = TRUE;
            if(counter > max)
                max = counter;
            counter = 0;
        }
        else if(enabled)
            counter++;
    }
    
    return max;
}

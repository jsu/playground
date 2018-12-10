// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");
#include <stdbool.h>
#define IN  true
#define OUT false

int solution(char *S) {
    // write your code in C99 (gcc 6.2.0)
    char *p;
    int status, max_length, letters, digits, curr_length;
    bool invalid;
    
    max_length = curr_length = -1;
    letters = digits = 0;
    status = OUT;
    invalid = false;
    for(p = S; *p != '\0'; p++)
    {
        if(status == OUT && *p != ' ')
        {
            curr_length = letters = digits = 0;
            invalid = false;
            status = IN;
        }
        else if(*p == ' ' || *(p + 1) == '\0')
        {
            status = OUT;
            if(letters % 2 != 0)
                invalid = true;
            if(digits % 2 != 1)
                invalid = true;
            if(invalid == false && curr_length > max_length)
                max_length = curr_length;
        }
        
        if(*p >= '0' && *p <= '9')
            digits++;
        else if(*p >= 'A' && *p <= 'Z')
            letters++;
        else if(*p >= 'a' && *p <= 'z')
            letters++;
        else
            invalid = true;
            
        if(invalid == false)
            curr_length++;
    }
    return max_length;
}

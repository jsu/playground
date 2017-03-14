#include <stdio.h>
#include <stdint.h>

int main(void)
{
    /* t <= 100, n <= 100 */
    /* 100! = 9.332621544E157 */
    int8_t t, n;
    uint8_t i, position;
    uint16_t carry, r[159];

    scanf("%hhd", &t);
    while(t--)
    {
        scanf("%hhd", &n);
        position = 0;
        for(i = n; i > 0; i /= 10)
            r[position++] = i % 10;

        for(n -= 1; n > 1; n--)
        {
            carry = 0;
            for(i = 0; i < position; i++)
            {
                r[i] = r[i] * n + carry;
                carry = r[i] / 10;
                r[i] %= 10;
            } 

            while(carry)
            {
                r[position++] = carry % 10;
                carry /= 10; 
            }
        }

        while(position--)
            printf("%d", r[position]);
        printf("\n");
    }

    return 0;
}

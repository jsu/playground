#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    /* int8 */
    printf("int8\n");
    printf("%d\n", 0x7f);
    printf("%u\n", 0xff);
    printf("12345678901234567890\n");
    /* int16 */
    printf("int16\n");
    printf("%d\n", 0x7fff);
    printf("%u\n", 0xffff);
    printf("12345678901234567890\n");
    /* int32 */
    printf("int32\n");
    printf("%d\n", 0x7fffffff);
    printf("%u\n", 0xffffffff);
    printf("12345678901234567890\n");
    /* int64 */
    printf("int64\n");
    printf("12345678901234567890\n");
    printf("%ld\n", 0x7fffffffffffffff);
    printf("%lu\n", 0xffffffffffffffff);
    return 0;
}

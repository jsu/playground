#include <stdio.h>
#include <inttypes.h>

int main(int argc, char **argv)
{
    /* int8 */
    printf("int8\n");
    printf("%" PRId8 "\n", 0x7f);
    printf("%" PRIu8 "\n", 0xff);
    printf("12345678901234567890\n");
    /* int16 */
    printf("int16\n");
    printf("%" PRId16 "\n", 0x7fff);
    printf("%" PRIu16 "\n", 0xffff);
    printf("12345678901234567890\n");
    /* int32 */
    printf("int32\n");
    printf("%" PRId32 "\n", 0x7fffffff);
    printf("%" PRIu32 "\n", 0xffffffff);
    printf("%" PRIo32 "\n", 0xffffffff);
    printf("0x%" PRIx32 "\n", 0xffffffff);
    printf("12345678901234567890\n");
    /* int64 */
    printf("int64\n");
    printf("%" PRId64 "\n", 0x7fffffffffffffff);
    printf("%" PRIu64 "\n", 0xffffffffffffffff);
    printf("12345678901234567890\n");
    return 0;
}

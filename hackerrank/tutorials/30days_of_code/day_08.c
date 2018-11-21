#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 1024

typedef struct hash_item_s
{
    char *key;
    int value;
    struct hash_item_s *next;
}hash_item_t;

typedef struct hash_table_s
{
    hash_item_t **array;
}hash_table_t;

void put(hash_table_t *table, char *key, int value)
{
    hash_item_t *item, *prev;
    size_t index;
    
}

int main(int argc, char **argv)
{
    return 0;
}

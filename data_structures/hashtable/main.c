#include <stdlib.h>
#include <stdio.h>
#define TABLE_SIZE 1024

typedef struct hash_item_s
{
    char key;
    int value;
    struct hash_item_s *next;
}hash_item_t;

typedef struct hash_table_s
{
    hash_item_t **array;
}hash_table_t;

void put(hash_table_t *table, char key, int value)
{
    hash_item_t *item, *prev;
    size_t index;

    index = (size_t)key;
    index %= TABLE_SIZE;

    if(table->array[index] == NULL)
    {
        item = (hash_item_t *)malloc(sizeof(item));
        item->key = key;
        item->value = value;
        item->next = NULL;
        table->array[index] = item;
    }
    else
    {
        item = table->array[index];
        prev = NULL;
        while(item)
        {
            if(item->key == key)
            {
                item->value = value; 
                break;
            }
            prev = item;
            item = item->next; 
        } 
        if(item == NULL)
        {
            item = (hash_item_t *)malloc(sizeof(item));
            item->key = key;
            item->value = value;
            item->next = NULL;
            prev->next = item;
        }
    }
}

int get(hash_table_t *table, char key)
{
    hash_item_t *item;
    size_t index;

    index = (size_t)key;
    index %= TABLE_SIZE;

    item = table->array[index];
    while(item)
    {
        if(item->key == key)
           return item->value; 
        item = item->next;
    }

    return -1;
}

int main(int argc, char **argv)
{
    int index;
    hash_table_t *table;

    table = (hash_table_t *)malloc(sizeof(table));
    table->array = (hash_item_t **)malloc(sizeof(table->array) * TABLE_SIZE);
    for(index=0; index<TABLE_SIZE; index++)
        table->array[index] = NULL; 

    put(table, 'a', 10);
    put(table, 'A', 97);
    printf("%d\n", get(table, 'A'));
    return 0;
}

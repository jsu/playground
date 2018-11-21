#include <stdlib.h>

#define TABLE_SIZE 1024

typedef struct hash_item_s
{
	int key;
	int value;
	struct hash_item_s *next;
}hash_item_t;

typedef struct hash_table_s
{
	hash_item_t **array;
}hash_table_t;

void put(hash_table_t *table, int key, int value)
{
    hash_item_t *item, *prev;
	size_t index = (size_t)key;	
	index %= TABLE_SIZE;

    if(table->array[index] == NULL)
    {
        item = (hash_item_t *)malloc(sizeof(hash_item_t));
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
            item = (hash_item_t *)malloc(sizeof(hash_item_t));
            item->key = key;
            item->value = value;
            item->next = NULL;
            prev->next = item;
        }
    }
}

int get(hash_table_t *table, int key)
{
    hash_item_t *item;
    size_t index = (size_t)key;
    index %= TABLE_SIZE;

    if(table->array[index] == NULL)
	    return -1;

    item = table->array[index];
    while(item)
    {
        if(item->key == key)
            return item->value;
        item = item->next;
    }

    return -1;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target) {
	int i, j, *result;
	hash_table_t *table;
	table = (hash_table_t *)malloc(sizeof(table));
	table->array = (hash_item_t **)calloc(TABLE_SIZE, sizeof(hash_item_t *));

	result = (int *)malloc(sizeof(result) * 2);

	for(i=0; i<numsSize; i++)
	{
		if((j = get(table, target - nums[i])) != -1)
		{
			result[0] = j;
			result[1] = i;
		}
		else
			put(table, nums[i], i);
	}

	return result;
}

int main(int argc, char **argv)
{
    int a[] = {2, 7, 11, 15}, *r;
    r = twoSum(a, 4, 9);
    printf("%d %d\n", r[0], r[1]);
	return 0;
}

#include <stdlib.h>
#include <stdio.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target) {
	int i, j, *result;

	result = (int *)malloc(sizeof(int) * 2);

	for(i=0; i<numsSize; i++)
    {
        for(j=i+1; j<numsSize; j++)
        {
            if(nums[i] == target - nums[j])
            {
                result[0] = i;
                result[1] = j; 
                return result;
            }
        }
    }

	return NULL;
}

int main(int argc, char **argv)
{
	int nums[] = {11, 15, 2, 7};
    int *r;
    r = twoSum(nums, 4, 9);
    printf("%d %d\n", r[0], r[1]);
	return 0;
}

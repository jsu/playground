#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int *array, int low, int high)
{
    int pivot = array[low];
    int i_low = low, i_high = high;

    while(i_low <= high && i_high >= low)
    {
        while(array[i_low] < pivot && i_low < high)
            i_low++;

        while(array[i_high] > pivot && i_high > low)
            i_high--;

        if(i_low >= i_high)
            break;

        swap(&array[i_low], &array[i_high]); 
        i_low++;
        i_high--;
    }
    return i_high;
}

void quicksort(int *array, int low, int high)
{
    int pivot;
    if(low >= high)
        return;

    pivot = partition(array, low, high);
    quicksort(array, low, pivot);
    quicksort(array, pivot + 1, high);
}

int main(void)
{
    /* t <= 1e6, 0 <= input <= 1e6 */
    int t, i;
    int *inputs;

    scanf("%d", &t);
    inputs = (int *)malloc(sizeof(int) * t);
    for(i = 0; i < t; i++)
        scanf("%d", inputs + i);

    quicksort(inputs, 0, t-1);

    for(i = 0; i < t; i++)
        printf("%d\n", *(inputs + i));

    free(inputs);

    return 0;
}

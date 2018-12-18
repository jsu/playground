int search(int* nums, int numsSize, int target) {
    int first, last, mid;
    first = 0;
    last = numsSize - 1;
    while(first <= last)
    {
        mid = (first + last) / 2;
        if(nums[mid] > target)
            last = mid - 1;
        else if(nums[mid] < target)
            first = mid + 1;
        else
            return mid;
    }
    return -1;
}

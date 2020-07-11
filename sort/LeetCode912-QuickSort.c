

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

//QuickSort
//i j ---->   p
//0 3 2 1 3 5 8

void swap(int *a, int *b){
    int temp = a[0];
    a[0] = b[0];
    b[0] = temp;
    return;
}

void QuickSort(int *nums, int front, int back){
    if(front >= back){
        return;
    }else if(front - back == 1){
        if(nums[back] < nums[front]){
            swap(&nums[back], &nums[front]);
        }
    }
    int pivot = nums[back];
    int i = front - 1;
    int j = front - 1;
    
    while(j + 1 != back){
        j++;
        if(nums[j] < pivot){
            swap(&nums[i + 1], &nums[j]);
            i++;
        }
    }
    swap(&nums[i + 1], &nums[back]);
    
    QuickSort(nums, front, i);
    QuickSort(nums, i + 2, back);
    return; 
}


int* sortArray(int* nums, int numsSize, int* returnSize){
    QuickSort(nums, 0, numsSize - 1);
    *(returnSize) = numsSize;
    return nums;
}

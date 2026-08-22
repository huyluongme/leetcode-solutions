/*
 * Problem    : 15. 3Sum
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : Aug 22, 2026
 * Language   : C
 * Difficulty : Medium
 * Tags       : Array, Two Pointers, Sorting
 * Link       : https://leetcode.com/problems/3sum
 *
 * Time       : O(n^2)
 * Space      : O(1)
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int compareIntegers(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;

    if (numsSize < 3) {
        *returnColumnSizes = NULL;
        return NULL;
    }

    qsort(nums, numsSize, sizeof(int), compareIntegers);

    int capacity = 64;
    int** res = (int**)malloc(capacity * sizeof(int*));
    *returnColumnSizes = (int*)malloc(capacity * sizeof(int));

    for (int i = 0; i < numsSize - 2; ++i) {
        if (nums[i] > 0)
            break;

        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int left = i + 1;
        int right = numsSize - 1;

        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];

            if (sum < 0) {
                left++;
            } else if (sum > 0) {
                right--;
            } else {
                if (*returnSize >= capacity) {
                    capacity *= 2;
                    res = (int**)realloc(res, capacity * sizeof(int*));
                    *returnColumnSizes = (int*)realloc(*returnColumnSizes, capacity * sizeof(int));
                }

                res[*returnSize] = (int*)malloc(3 * sizeof(int));
                res[*returnSize][0] = nums[i];
                res[*returnSize][1] = nums[left];
                res[*returnSize][2] = nums[right];
                (*returnColumnSizes)[*returnSize] = 3;
                (*returnSize)++;

                left++;
                right--;

                while (left < right && nums[left] == nums[left - 1]) left++;
                while (left < right && nums[right] == nums[right + 1]) right--;
            }
        }
    }

    return res;
}

int main()
{
    int nums[] = {-1,0,1,2,-1,-4};
    int numsSize = sizeof(nums)/sizeof(nums[0]);
    int returnSize;
    int* returnColumnSizes;
    int** res;

    res = threeSum(nums, numsSize, &returnSize, &returnColumnSizes);

    for (int i = 0; i < returnSize; ++i) {
        printf("[");

        for (int j = 0; j < returnColumnSizes[i]; ++j) {
            printf("%d", res[i][j]);

            if (j < returnColumnSizes[i] - 1)
                printf(", ");
        }

        printf("]\n");
    }

    return 0;
}

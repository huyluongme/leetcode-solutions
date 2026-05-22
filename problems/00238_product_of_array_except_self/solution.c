/*
 * Problem    : 238. Product of Array Except Self
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : May 22, 2026
 * Language   : C
 * Difficulty : Medium
 * Tags       : Array, Prefix Sum
 * Link       : https://leetcode.com/problems/product-of-array-except-self
 *
 * Time       : O(n)
 * Space      : O(n)
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    if (numsSize == 0) {
        *returnSize = 0;
        return NULL;
    }

    int* result = (int*)malloc(numsSize * sizeof(int));
    int prefixProduct = 1;
    result[0] = 1;

    for (int i = 1; i < numsSize; i++) {
        prefixProduct *= nums[i - 1];
        result[i] = prefixProduct;
    }

    int suffixProduct = 1;
    for (int i = numsSize - 1; i >= 0; i--) {
        result[i] *= suffixProduct;
        suffixProduct *= nums[i];
    }

    *returnSize = numsSize;
    return result;
}

int main()
{
    int nums[] = {1, 2, 3, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;

    int* result = productExceptSelf(nums, numsSize, &returnSize);

    printf("[");
    for (int i = 0; i < returnSize; i++) {
        printf("%d", result[i]);
        if (i < returnSize - 1)
            printf(", ");
    }
    printf("]\n");

    free(result);

    return 0;
}
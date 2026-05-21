/*
 * Problem    : 347. Top K Frequent Elements
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : May 21, 2026
 * Language   : C
 * Difficulty : Medium
 * Tags       : Array, Hash Table, Divide and Conquer, Sorting, Heap (Priority Queue), Bucket Sort, Counting, Quickselect
 * Link       : https://leetcode.com/problems/top-k-frequent-elements
 *
 * Time       : O(n)
 * Space      : O(n)
 */

#include <stdio.h>
#include <stdlib.h>

#define OFFSET  10000
#define RANGE   20001

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    // freq[i] is the frequency of number (i - OFFSET)
    int* freq = (int*)calloc(RANGE, sizeof(int));

    for (int i = 0; i < numsSize; ++i)
        freq[nums[i] + OFFSET]++;

    // bucketSize[f] = number of values that appear f times
    int* bucketSize = (int*)calloc(numsSize + 1, sizeof(int));

    for (int i = 0; i < RANGE; ++i)
        if (freq[i])
            bucketSize[freq[i]]++;

    // buckets[f] contains the numbers that appear f times
    int** buckets = (int**)calloc(numsSize + 1, sizeof(int*));

    for (int f = 1; f <= numsSize; ++f)
        if (bucketSize[f])
            buckets[f] = (int*)malloc(sizeof(int) * bucketSize[f]);

    int* bucketIndex = (int*)calloc(numsSize + 1, sizeof(int));

    for (int i = 0; i < RANGE; ++i) {
        if (freq[i]) {
            int count = freq[i];
            int value = i - OFFSET;

            buckets[count][bucketIndex[count]] = value;
            bucketIndex[count]++;
        }
    }

    int* res = (int*)malloc(sizeof(int) * k);
    *returnSize = 0;

    for (int f = numsSize; f >= 1 && *returnSize < k; --f) {
        for (int i = 0; i < bucketSize[f] && *returnSize < k; ++i) {
            res[*returnSize] = buckets[f][i];
            (*returnSize)++;
        }
    }

    for (int f = 1; f <= numsSize; ++f)
        free(buckets[f]);

    free(freq);
    free(bucketSize);
    free(bucketIndex);
    free(buckets);

    return res;
}

int main()
{
    int nums[] = {1, 1, 1, 2, 2, 3};
    int numsSize = sizeof(nums)/sizeof(nums[0]);
    int k = 2;
    int returnSize = 0;

    int* res = topKFrequent(nums, numsSize, k, &returnSize);

    printf("[");
    for (int i = 0; i < returnSize; ++i) {
        printf("%d", res[i]);

        if (i < returnSize - 1)
            printf(", ");
    }
    printf("]\n");

    return 0;
}

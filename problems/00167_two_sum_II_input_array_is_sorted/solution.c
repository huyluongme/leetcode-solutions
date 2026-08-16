/*
 * Problem    : 167. Two Sum II - Input Array Is Sorted
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : Aug 16, 2026
 * Language   : C
 * Difficulty : Medium
 * Tags       : Array, Two Pointers, Binary Search
 * Link       : https://leetcode.com/problems/two-sum-ii-input-array-is-sorted
 *
 * Time       : O(n)
 * Space      : O(1)
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int left, right;
    int* res;

    left = 0;
    right = numbersSize - 1;
    *returnSize = 0;

    while (left < right) {
        int sum = numbers[left] + numbers[right];
        if (sum == target) {
            res = (int*)malloc(sizeof(int) * 2);
            res[0] = left + 1;
            res[1] = right + 1;
            *returnSize = 2;
            break;
        }

        if (sum < target) left++;
        if (sum > target) right--;
    }

    return res;
}

int main()
{
    int numbers[] = {2, 7, 11, 15};
    int numbersSize = sizeof(numbers) / sizeof(numbers[0]);
    int target = 9;
    int returnSize;

    int* res = twoSum(numbers, numbersSize, target, &returnSize);

    if (returnSize == 2)
        printf("[%d, %d]\n", res[0], res[1]);

    free(res);

    return 0;
}


/*
 * Problem    : 704. Binary Search
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : Oct 18, 2026
 * Language   : C
 * Difficulty : Easy
 * Tags       : Array, Binary Search
 * Link       : https://leetcode.com/problems/binary-search
 *
 * Time       : O(log n)
 * Space      : O(1)
 */

#include <stdio.h>

int search(int* nums, int numsSize, int target) {
    int left, mid, right;

    left = 0;
    right = numsSize - 1;
    mid = (left + right) / 2;

    while (left <= right) {
        if (nums[mid] == target)
            return mid;

        if (nums[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;

        mid = (left + right) / 2;
    }

    return -1;
}

int main()
{
    int nums[] = {-1, 0, 3, 5, 9, 11};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int target = 9;

    printf("%d\n", search(nums, numsSize, target));

    return 0;
}

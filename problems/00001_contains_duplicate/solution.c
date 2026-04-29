/*
 * Problem    : 217. Contains Duplicate
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : April 26, 2026 
 * Language   : C
 * Difficulty : Easy
 * Tags       : Array, Hash Table, Sorting
 * Link       : https://leetcode.com/problems/contains-duplicate
 *
 * Time       : O(nlogn)
 * Space      : O(logn)
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return *(int*)a > *(int*)b;
}

bool containsDuplicate(int* nums, int numSize) {
    qsort(nums, numSize, sizeof(nums[0]), compare);

    for (int i = 0; i < numSize - 1; ++i)
        if (nums[i] == nums[i + 1])
            return true;

    return false;
}

int main() {
    int nums[] = {1, 2, 3, 1};
    int numSize = sizeof(nums)/sizeof(nums[0]);

    if (containsDuplicate(nums, numSize))
        printf("true\n");
    else
        printf("false\n");

    return 0;
}


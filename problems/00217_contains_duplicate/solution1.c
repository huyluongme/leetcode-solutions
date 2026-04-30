/*
 * Problem    : 217. Contains Duplicate
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : April 26, 2026
 * Language   : C
 * Difficulty : Easy
 * Tags       : Array, Hash Table, Sorting
 * Link       : https://leetcode.com/problems/contains-duplicate
 *
 * Time       : O(n)
 * Space      : O(n)
 */

#include <stdio.h>
#include <stdbool.h>

#define TABLE_SIZE 100003 /* load factor 0.5 */

int hashFunc(int key) {
    /* Shift the key to handle negative numbers */
    return (int)(((long long)key + 1000000000LL) % TABLE_SIZE);
}

bool containsDuplicate(int* nums, int numSize) {
    int hash_table[TABLE_SIZE];
    bool bucket_used[TABLE_SIZE] = {false};

    for (int i = 0; i < numSize; ++i) {
        int index = hashFunc(nums[i]);

        while (bucket_used[index]) {
            if (hash_table[index] == nums[i])
                return true;

            /* Linear probing to find the next available slot */
            index = (index + 1) % TABLE_SIZE;
        }

        hash_table[index] = nums[i];
        bucket_used[index] = true;
    }

    return false;
}

int main() {
    int nums[] = {1, 2, 3, 4};
    int numSize = sizeof(nums)/sizeof(nums[0]);

    if (containsDuplicate(nums, numSize))
        printf("true\n");
    else
        printf("false\n");

    return 0;
}


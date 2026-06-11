/*
 * Problem    : 128. Longest Consecutive Sequence
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : June 11, 2026
 * Language   : C
 * Difficulty : Medium
 * Tags       : Array, Hash Table, Union-Find
 * Link       : https://leetcode.com/problems/longest-consecutive-sequence/
 *
 * Time       : O(N)
 * Space      : O(N)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INF 1000000001

int longestConsecutive(int* nums, int numsSize) {
    if (numsSize == 0) return 0;
    
    // Step 1: Calculate hash table capacity (mod) as the next power of 2
    // keeping the load factor <= 50% to minimize hash collisions.
    // Also track 'shift' to extract the highest bits for Fibonacci hashing.
    unsigned int mod = 1;
    unsigned int shift = 32;
    while (mod < (unsigned int)numsSize * 2) {
        mod <<= 1;
        shift--;
    }
    unsigned int mask = mod - 1; // Mask used for quick bitwise AND index mapping
    
    // Step 2: Allocate memory on the Heap to avoid Stack Overflow on large inputs
    int* set = (int*)malloc(mod * sizeof(int));
    int* uniq = (int*)malloc(numsSize * sizeof(int));
    if (!set || !uniq) {
        if (set) free(set);
        if (uniq) free(uniq);
        return 0;
    }
    
    int uniqn = 0;
    int best = 0;
    
    // Step 3: Initialize hash table with INF (representing empty slot)
    for (unsigned int i = 0; i < mod; ++i) {
        set[i] = INF;
    }
    
    // Step 4: Populate the hash table and collect unique elements to 'uniq' array
    for (int i = 0; i < numsSize; ++i) {
        int val = nums[i];
        
        // Fibonacci Hashing: Multiply by golden ratio constant and shift right to get index
        unsigned int hash = ((unsigned int)val * 2654435761u) >> shift;
        
        // Linear probing: Resolve collisions by checking adjacent cells (highly cache friendly)
        while (set[hash] != INF && set[hash] != val) {
            hash = (hash + 1) & mask;
        }
        
        // If the value is not in the set, add it and save to the unique list
        if (set[hash] == INF) {
            uniq[uniqn++] = val;
            set[hash] = val;
        }
    }
    
    // Step 5: Find the longest consecutive sequence
    for (int i = 0; i < uniqn; ++i) {
        int val = uniq[i];
        
        // Check if 'val' is the START of a sequence (i.e. 'val - 1' is NOT in the set)
        unsigned int hash = ((unsigned int)(val - 1) * 2654435761u) >> shift;
        while (set[hash] != INF && set[hash] != val - 1) {
            hash = (hash + 1) & mask;
        }
        
        // If 'val - 1' is not found, 'val' is the starting element of a sequence
        if (set[hash] == INF) {
            int len = 1;
            // Scan for next consecutive elements: val + 1, val + 2, ...
            for (int j = val + 1; ; j++, len++) {
                unsigned int cur_hash = ((unsigned int)j * 2654435761u) >> shift;
                while (set[cur_hash] != INF && set[cur_hash] != j) {
                    cur_hash = (cur_hash + 1) & mask;
                }
                
                // Sequence ends when next value is not present in the set
                if (set[cur_hash] == INF)
                    break;
            }
            // Update the maximum sequence length found
            if (len > best)
                best = len;
        }
    }
    
    // Step 6: Free allocated resources
    free(set);
    free(uniq);
    return best;
}

int main()
{
    int nums[] = {100,4,200,1,3,2};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int result = longestConsecutive(nums, numsSize);
    printf("%d\n", result);

    return 0;
}
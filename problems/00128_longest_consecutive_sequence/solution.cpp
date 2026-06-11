/*
 * Problem    : 128. Longest Consecutive Sequence
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : June 11, 2026
 * Language   : C++
 * Difficulty : Medium
 * Tags       : Array, Hash Table, Union-Find
 * Link       : https://leetcode.com/problems/longest-consecutive-sequence/
 *
 * Time       : O(N)
 * Space      : O(N)
 */

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int numsSize = nums.size();
        if (numsSize == 0) return 0;
        
        const int INF = 1000000001;
        
        // Step 1: Calculate hash table capacity (mod) as the next power of 2
        // keeping the load factor <= 50% to minimize hash collisions.
        unsigned int mod = 1;
        unsigned int shift = 32;
        while (mod < (unsigned int)numsSize * 2) {
            mod <<= 1;
            shift--;
        }
        unsigned int mask = mod - 1;
        
        // Step 2: Use vectors as flat contiguous arrays (avoiding individual node allocations)
        vector<int> set(mod, INF);
        vector<int> uniq;
        uniq.reserve(numsSize);
        
        int best = 0;
        
        // Step 3: Populate the hash table and collect unique elements
        for (int val : nums) {
            // Fibonacci Hashing for uniform distribution and minimal collisions
            unsigned int hash = ((unsigned int)val * 2654435761u) >> shift;
            
            // Linear probing (highly cache-friendly)
            while (set[hash] != INF && set[hash] != val) {
                hash = (hash + 1) & mask;
            }
            if (set[hash] == INF) {
                uniq.push_back(val);
                set[hash] = val;
            }
        }
        
        // Step 4: Scan unique values to find the longest consecutive sequence
        for (int val : uniq) {
            // Check if 'val' is the START of a sequence (i.e. 'val - 1' is NOT in the set)
            unsigned int hash = ((unsigned int)(val - 1) * 2654435761u) >> shift;
            while (set[hash] != INF && set[hash] != val - 1) {
                hash = (hash + 1) & mask;
            }
            
            // If 'val - 1' is not present, we start counting
            if (set[hash] == INF) {
                int len = 1;
                for (int j = val + 1; ; j++, len++) {
                    unsigned int cur_hash = ((unsigned int)j * 2654435761u) >> shift;
                    while (set[cur_hash] != INF && set[cur_hash] != j) {
                        cur_hash = (cur_hash + 1) & mask;
                    }
                    if (set[cur_hash] == INF)
                        break;
                }
                best = max(best, len);
            }
        }
        
        return best;
    }
};

int main() {
    Solution solution;
    vector<int> nums = {100, 4, 200, 1, 3, 2};
    cout << solution.longestConsecutive(nums) << endl;
    return 0;
}

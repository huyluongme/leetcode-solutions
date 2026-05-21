/*
 * Problem    : 347. Top K Frequent Elements
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : May 21, 2026
 * Language   : C++
 * Difficulty : Medium
 * Tags       : Array, Hash Table, Divide and Conquer, Sorting, Heap (Priority Queue), Bucket Sort, Counting, Quickselect
 * Link       : https://leetcode.com/problems/top-k-frequent-elements
 *
 * Time       : O(n)
 * Space      : O(n)
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int n = nums.size();

        // freq[num] is the frequency of num
        unordered_map<int, int> freq;

        for (int num : nums)
            freq[num]++;

        // buckets[f] contains the numbers that appear f times
        vector<vector<int>> buckets(n + 1);

        for (auto& [num, count] : freq)
            buckets[count].push_back(num);

        vector<int> res;

        for (int f = buckets.size() - 1; f >= 0; --f) {
            for (int num : buckets[f]) {
                res.push_back(num);

                if (res.size() == k)
                    return res;
            }
        }

        return res;
    }
};

int main()
{
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    int k = 2;
    Solution sol;

    vector<int> result = sol.topKFrequent(nums, k);

    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i < result.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    return 0;
}
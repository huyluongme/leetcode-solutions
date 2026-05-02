/*
 * Problem    : 1. Two Sum
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : May 2, 2026
 * Language   : C++
 * Difficulty : Easy
 * Tags       : Junior, Array, Hash Table
 * Link       : https://leetcode.com/problems/two-sum
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
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> table;

        for (int i = 0; i < nums.size(); ++i) {
            int complement = target - nums[i];

            if (table.count(complement))
                return {table[complement], i};

            table[nums[i]] = i;
        }

        return {};
    }
};

int main()
{
    Solution s;

    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    vector<int> res = s.twoSum(nums, target);

    cout << "[" << res[0] << ", " << res[1] << "]\n";

    return 0;
}


/*
 * Problem    : 217. Contains Duplicate
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : April 29, 2026
 * Language   : C++
 * Difficulty : Easy
 * Tags       : Array, Hash Table, Sorting
 * Link       : https://leetcode.com/problems/contains-duplicate
 *
 * Time       : O(nlogn)
 * Space      : O(logn)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool contrainsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        for (auto i = 0; i < nums.size() - 1; ++i)
            if (nums[i] == nums[i + 1])
                return true;

        return false;
    }
};

int main()
{
    Solution s;
    vector<int> nums = {1, 2, 3, 1};

    if (s.contrainsDuplicate(nums))
        cout << "true\n";
    else
        cout << "false\n";

    return 0;
}


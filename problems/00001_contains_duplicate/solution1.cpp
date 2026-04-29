/*
 * Problem    : 217. Contains Duplicate
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : April 29, 2026
 * Language   : C++
 * Difficulty : Easy
 * Tags       : Array, Hash Table, Sorting
 * Link       : https://leetcode.com/problems/contains-duplicate
 *
 * Time       : O(n)
 * Space      : O(n)
 */

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool contrainsDuplicate(vector<int>& nums) {
        unordered_set<int> hash_table;

        for (auto x : nums) {
            if (hash_table.count(x))
                return true;

            hash_table.insert(x);
        }
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


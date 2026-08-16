/*
 * Problem    : 167. Two Sum II - Input Array Is Sorted
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : Aug 16, 2026
 * Language   : C++
 * Difficulty : Medium
 * Tags       : Array, Two Pointers, Binary Search
 * Link       : https://leetcode.com/problems/two-sum-ii-input-array-is-sorted
 *
 * Time       : O(n)
 * Space      : O(1)
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;
        vector<int> res;

        while (left < right) {
            int sum = numbers[left] + numbers[right];

            if (sum == target) {
                res.push_back(left + 1);
                res.push_back(right + 1);
                break;
            }

            if (sum < target) left++;

            if (sum > target) right--;
        }

        return res;
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


/*
 * Problem    : 704. Binary Search
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : Oct 18, 2026
 * Language   : C++
 * Difficulty : Easy
 * Tags       : Array, Binary Search
 * Link       : https://leetcode.com/problems/binary-search
 *
 * Time       : O(log n)
 * Space      : O(1)
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        int mid = (left + right) / 2;

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
};

int main()
{
    Solution sol;
    vector<int> nums = {-1, 0, 3, 5, 9, 11};
    int target = 9;

    cout << sol.search(nums, target) << '\n';
 
    return 0;
}


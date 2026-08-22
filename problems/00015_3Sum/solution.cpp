/*
 * Problem    : 15. 3Sum
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : Aug 22, 2026
 * Language   : C++
 * Difficulty : Medium
 * Tags       : Array, Two Pointers, Sorting
 * Link       : https://leetcode.com/problems/3sum
 *
 * Time       : O(n^2)
 * Space      : O(1)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        int n = nums.size();
        if (n < 3) return res;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 2; ++i) {
            if (nums[i] > 0)
                break;

            if (i > 0 && nums[i] == nums[i - 1])
                continue;

            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum < 0) {
                    left++;
                } else if (sum > 0) {
                    right--;
                } else {
                    res.push_back({nums[i], nums[left], nums[right]});
                    left++;
                    right--;

                    while (left < right && nums[left] == nums[left - 1]) left++;
                    while (left < right && nums[right] == nums[right + 1]) right--;
                }
            }
        }

        return res;
    }
};

int main()
{
    Solution s;
    vector<int> nums = {-1, 0, 1, 2, -1, -4};

    vector<vector<int>> res = s.threeSum(nums);

    for (const auto& triplet : res) {
        cout << "[";
        for (size_t i = 0; i < triplet.size(); ++i) {
            cout << triplet[i];
            if (i < triplet.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }

    return 0;
}

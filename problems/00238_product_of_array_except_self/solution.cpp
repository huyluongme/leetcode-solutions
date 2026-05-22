/*
 * Problem    : 238. Product of Array Except Self
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : May 22, 2026
 * Language   : C++
 * Difficulty : Medium
 * Tags       : Array, Prefix Sum
 * Link       : https://leetcode.com/problems/product-of-array-except-self
 *
 * Time       : O(n)
 * Space      : O(n)
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<int> productExceptSelf(vector<int> &nums) {
        int n = nums.size();
        vector<int> result(n, 1);
        int prefixProduct = 1;

        for (int i = 0; i < n; i++) {
            result[i] *= prefixProduct;
            prefixProduct *= nums[i];
        }

        int suffixProduct = 1;
        for (int i = n - 1; i >= 0; i--) {
            result[i] *= suffixProduct;
            suffixProduct *= nums[i];
        }

        return result;
    }
};

int main()
{
    vector<int> nums = {1, 2, 3, 4};
    Solution solution;
    vector<int> result = solution.productExceptSelf(nums);

    cout << "[";
    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1)
            cout << ", ";
    }
    cout << "]\n";

    return 0;
}

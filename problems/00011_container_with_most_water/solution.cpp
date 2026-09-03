/*
 * Problem    : 11. Container With Most Water
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : Sep 4, 2026
 * Language   : C++
 * Difficulty : Medium
 * Tags       : Array, Two Pointers, Greedy
 * Link       : https://leetcode.com/problems/container-with-most-water
 *
 * Time       : O(n)
 * Space      : O(1)
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int res = 0;

        while (left < right) {
            int width = right - left;
            int h = min(height[left], height[right]);
            int area = width * h;
            res = (area > res) ? area : res;

            if (height[left] < height[right]) left++;
            else right--;
        }

        return res;
    }
};

int main()
{
    Solution s;

    vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int res = s.maxArea(height);

    cout << res << "\n";

    return 0;
}


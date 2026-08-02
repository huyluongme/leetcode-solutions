/*
 * Problem    : 84. Largest Rectangle in Histogram
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : August 03, 2026
 * Language   : C++
 * Difficulty : Hard
 * Tags       : Array, Stack, Monotonic Stack
 * Link       : https://leetcode.com/problems/largest-rectangle-in-histogram
 *
 * Time       : O(n)
 * Space      : O(n)
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        if (n == 0) return 0;

        stack<int> st;
        int maxArea = 0;

        for (int i = 0; i < n; ++i) {
            while (!st.empty() && heights[i] < heights[st.top()]) {
                int top = st.top();
                st.pop();
                int height = heights[top];
                int width = st.empty() ? i : i - st.top() - 1;
                int area = height * width;
                if (area > maxArea) {
                    maxArea = area;
                }
            }
            st.push(i);
        }

        while (!st.empty()) {
            int top = st.top();
            st.pop();
            int height = heights[top];
            int width = st.empty() ? n : n - st.top() - 1;
            int area = height * width;
            if (area > maxArea) {
                maxArea = area;
            }
        }

        return maxArea;
    }
};

int main() {
    vector<int> heights = {2,1,5,6,2,3};
    Solution sol;
    int result = sol.largestRectangleArea(heights);
    cout << "Largest rectangle area: " << result << endl;
    return 0;
}

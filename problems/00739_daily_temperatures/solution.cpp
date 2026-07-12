/*
 * Problem    : 739. Daily Temperatures
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : July 12, 2026
 * Language   : C++
 * Difficulty : Medium
 * Tags       : Staff, Array, Stack, Monotonic Stack
 * Link       : https://leetcode.com/problems/daily-temperatures
 *
 * Time       : O(n)
 * Space      : O(n)
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> ans;
        for (int i = 0; i < temperatures.size(); ++i) {
            ans.push_back(0);
        }

        stack<int> st;

        for (int i = 0; i < temperatures.size(); ++i) {
            while (!st.empty() && temperatures[st.top()] < temperatures[i]) {
                ans[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
        }

        return ans;
    }
};

int main()
{
    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};
    Solution* sol = new Solution();
    vector<int> result = sol->dailyTemperatures(temperatures);

    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}
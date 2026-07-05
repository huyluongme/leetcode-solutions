/*
 * Problem    : 20. Valid Parentheses
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : May 2, 2026
 * Language   : C++
 * Difficulty : Easy
 * Tags       : String, Stack
 * Link       : https://leetcode.com/problems/valid-parentheses
 *
 * Time       : O(n)
 * Space      : O(n)
 */

#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];

            if (c == '(' || c == '{' || c == '[')
                st.push(c);
            else {
                if (st.empty())
                    return false;

                char top = st.top();
                st.pop();

                if (c == ')' && top != '(')
                    return false;

                if (c == '}' && top != '{')
                    return false;

                if (c == ']' && top != '[')
                    return false;
            }
        }

        return st.empty();
    }
};

int main()
{
    Solution s;

    string s1 = "()[]{}";
    cout << s.isValid(s1) << endl;

    string s2 = "(]";
    cout << s.isValid(s2) << endl;

    string s3 = "([)]";
    cout << s.isValid(s3) << endl;

    string s4 = "{[]}";
    cout << s.isValid(s4) << endl;

    string s5 = "(((((";
    cout << s.isValid(s5) << endl;

    return 0;
}

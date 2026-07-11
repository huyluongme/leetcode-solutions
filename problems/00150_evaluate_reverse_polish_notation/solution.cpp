/*
 * Problem    : 150. Evaluate Reverse Polish Notation
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : July 11, 2026
 * Language   : C++
 * Difficulty : Medium
 * Tags       : Array, Math, Stack
 * Link       : https://leetcode.com/problems/evaluate-reverse-polish-notation
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
    int evalRPN(vector<string>& tokens) {
        stack<int> s;

        for (string token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int op2 = s.top();
                s.pop();
                int op1 = s.top();
                s.pop();
                if (token == "+") {
                    s.push(op1 + op2);
                } else if (token == "-") {
                    s.push(op1 - op2);
                } else if (token == "*") {
                    s.push(op1 * op2);
                } else if (token == "/") {
                    s.push(op1 / op2);
                }
            } else {
                s.push(stoi(token));
            }
        }        

        return s.top();
    }
};

int main()
{
    Solution s;
    vector<string> tokens1 = {"4", "13", "5", "/", "+" };
    cout << s.evalRPN(tokens1) << endl;
    vector<string> tokens2 = {"2", "1", "+", "3", "*" };
    cout << s.evalRPN(tokens2) << endl;
    vector<string> tokens3 = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+" };
    cout << s.evalRPN(tokens3) << endl;
    vector<string> tokens4 = {"4", "13", "5", "/", "+" };
    cout << s.evalRPN(tokens4) << endl;
    vector<string> tokens5 = {"2", "1", "+", "3", "*" };
    cout << s.evalRPN(tokens5) << endl;

    return 0;
}

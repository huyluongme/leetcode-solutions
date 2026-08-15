/*
 * Problem    : 125. Valid Palindrome
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : August 15, 2026
 * Language   : C++
 * Difficulty : Easy
 * Tags       : Two Pointers, String
 * Link       : https://leetcode.com/problems/valid-palindrome
 *
 * Time       : O(n)
 * Space      : O(1)
 */

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int left, right;

        left = 0;
        right = s.size() - 1;

        while (left < right) {
            if (!isalnum(s[left])) {
                left++;
                continue;
            }

            if (!isalnum(s[right])) {
                right--;
                continue;
            }

            if (tolower(s[left]) != tolower(s[right]))
                return false;

            left++;
            right--;
        }

        return true;
    }
};

int main()
{
    string s = "A man, a plan, a canal: Panama";

    Solution sol;
    sol.isPalindrome(s) ? cout << "true\n" : cout << "false\n";

    return 0;
}

/*
 * Problem    : 242. Valid Anagram
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : April 30, 2026
 * Language   : C++
 * Difficulty : Easy
 * Tags       : String, Sorting, Hash Table
 * Link       : https://leetcode.com/problems/valid-anagram
 *
 * Time       : O(n)
 * Space      : O(n)
 */

#include <iostream>

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        int s_len = s.size();
        int t_len = t.size();
        int alphabet_cnt_s[26] = {0};
        int alphabet_cnt_t[26] = {0};

        if (s_len != t_len)
            return false;

        for (int i = 0; i < s_len; ++i) {
            alphabet_cnt_s[(int)s[i] - 97]++;
            alphabet_cnt_t[(int)t[i] - 97]++;
        }

        for (int i = 0; i < 26; ++i)
            if (alphabet_cnt_s[i] != alphabet_cnt_t[i])
                return false;

        return true;
    }
};

int main()
{
    string s = "anagram", t = "nagaram";
    Solution s1;

    if (s1.isAnagram(s, t))
        printf("true\n");
    else
        printf("false\n");

    return 0;
}


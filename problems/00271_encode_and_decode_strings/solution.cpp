/*
 * Problem    : 271. Encode and Decode Strings
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : May 22, 2026
 * Language   : C++
 * Difficulty : Medium
 * Tags       : Array, String, Design
 * Link       : https://leetcode.com/problems/encode-and-decode-strings
 *
 * Time       : O(n), where n is the total length of all strings in the input vector.
 * Space      : O(n), where n is the total length of all strings in the input vector.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    string encode(vector<string> &strs) {
        string encoded;

        for (const string &str: strs)
            encoded += to_string(str.size()) + "#" + str;

        return encoded;
    }

    vector<string> decode(string s) {
        vector<string> decoded;
        int size = s.size();
        int i = 0;

        while (i < size) {
            int j = i;

            while (s[j] != '#')
                j++;

            int length = stoi(s.substr(i, j - i));
            decoded.push_back(s.substr(j + 1, length));
            i = j + 1 + length;
        }

        return decoded;
    }
};

int main()
{
    vector<string> strs = {"Hello", "World"};
    Solution solution;
    string encoded = solution.encode(strs);
    vector<string> decoded = solution.decode(encoded);

    cout << "[";
    for (size_t i = 0; i < decoded.size(); i++) {
        cout << "\"" << decoded[i] << "\"";
        if (i < decoded.size() - 1)
            cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}
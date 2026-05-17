/*
 * Problem    : 49. Group Anagrams
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : May 17, 2026
 * Language   : C++
 * Difficulty : Medium
 * Tags       : Array, Hash Table, String, Sorting
 * Link       : https://leetcode.com/problems/group-anagrams
 *
 * Time       : O(N * K log K), where N is the number of strings and K is the maximum length of a string
 * Space      : O(N * K), for storing the anagram groups
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anagramGroups;

        for (const string& str : strs) {
            string key = str;
            sort(key.begin(), key.end());
            anagramGroups[key].push_back(str);
        }

        vector<vector<string>> res;
        res.reserve(anagramGroups.size());

        for (auto& group : anagramGroups)
            res.push_back(move(group.second));

        return res;
    }
};

int main()
{
    Solution sol;
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};

    vector<vector<string>> res = sol.groupAnagrams(strs);

    printf("[");

    for (size_t i = 0; i < res.size(); ++i) {
        printf("[");

        for (size_t j = 0; j < res[i].size(); ++j) {
            printf("\"%s\"", res[i][j].c_str());
            if (j < res[i].size() - 1)
                printf(",");
        }

        printf("]");

        if (i < res.size() - 1)
            printf(",");
    }

    printf("]\n");

    return 0;
}

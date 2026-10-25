/*
 * Problem    : 74. Search a 2D Matrix
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : Oct 25, 2026
 * Language   : C++
 * Difficulty : Medium
 * Tags       : Array, Binary Search, Matrix
 * Link       : https://leetcode.com/problems/search-a-2d-matrix
 *
 * Time       : O(log(m * n)) where m is the number of rows and n is the number of columns in the matrix
 * Space      : O(1)
 */

#include <stdio.h>
#include <vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if (m == 0) return false;
        int n = matrix[0].size();
        if (n == 0) return false;

        int left = 0;
        int right = m * n - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int row = mid / n;
            int col = mid % n;
            int midValue = matrix[row][col];

            if (midValue == target)
                return true;
            else if (midValue < target)
                left = mid + 1;
            else
                right = mid - 1;
        }

        return false;
    }
};

int main()
{
    vector<vector<int>> matrix = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };
    int target = 3;

    Solution solution;
    bool result = solution.searchMatrix(matrix, target);
    if (result) {
        printf("Target %d found in the matrix.\n", target);
    } else {
        printf("Target %d not found in the matrix.\n", target);
    }

    return 0;
}
/*
 * Problem    : 36. Valid Sudoku
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : May 22, 2026
 * Language   : C++
 * Difficulty : Medium
 * Tags       : Array, Hash Table, Matrix
 * Link       : https://leetcode.com/problems/valid-sudoku
 *
 * Time       : O(1), since the board size is fixed (9x9).
 * Space      : O(1), since we are using a fixed amount of space to store the state of rows, columns, and boxes.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool isValidSudoku(vector<vector<char>> &board) {
        int rows[9] = {0};
        int cols[9] = {0};
        int boxes[9] = {0};

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char c = board[i][j];

                if (c == '.')
                    continue;

                int num = c - '1';
                int boxIndex = (i / 3) * 3 + (j / 3);

                if ((rows[i] & (1 << num)) ||
                    (cols[j] & (1 << num)) ||
                    (boxes[boxIndex] & (1 << num)))
                    return false;

                rows[i] |= (1 << num);
                cols[j] |= (1 << num);
                boxes[boxIndex] |= (1 << num);
            }
        }
        return true;
    }
};

int main()
{
    vector<vector<char>> board = {
        {'5', '.', '3', '.', '.', '.', '.', '.', '6'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '8', '8', '3', '8', '8', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '7', '9', '.'}
    };
    Solution solution;
    bool isValid = solution.isValidSudoku(board);
    cout << (isValid ? "true" : "false") << endl;

    return 0;
}
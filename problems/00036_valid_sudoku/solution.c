/*
 * Problem    : 36. Valid Sudoku
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : May 22, 2026
 * Language   : C
 * Difficulty : Medium
 * Tags       : Array, Hash Table, Matrix
 * Link       : https://leetcode.com/problems/valid-sudoku
 *
 * Time       : O(1), since the board size is fixed (9x9).
 * Space      : O(1), since we are using a fixed amount of space to store the state of rows, columns, and boxes.
 */

#include <stdio.h>

bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    int rows[9] = {0};
    int cols[9] = {0};
    int boxes[9] = {0};

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize[i]; j++) {
            char c = board[i][j];

            if (c == '.')
                continue;

            int num = c - '1';
            int boxIndex = (i / 3) * 3 + (j / 3);

            /*
             * Check if the number has already been seen in the current row, column, or 3x3 box.
             * use bitwise operations to check and set the bits corresponding to the number.
             * If the bit is already set, it means the number has been seen before, and the board is not valid.
             * If the bit is not set, we set it to indicate that the number has been seen in the current row, column, and box.
             * This approach allows us to efficiently track the presence of numbers in rows, columns, and boxes using bit manipulation,
             * which is more memory-efficient than using separate data structures like hash sets or arrays.
             */
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

int main()
{
    char* board[] = {
        "5.3.....6",
        "6..195...",
        ".98....6.",
        "8...6...3",
        "4..8.3..1",
        "7...2...6",
        ".6....28.",
        "...419..5",
        "....8..79"
    };
    int boardSize = sizeof(board) / sizeof(board[0]);
    int boardColSize[] = {9, 9, 9, 9, 9, 9, 9, 9, 9};

    bool result = isValidSudoku(board, boardSize, boardColSize);
    printf("%s\n", result ? "true" : "false");

    return 0;
}
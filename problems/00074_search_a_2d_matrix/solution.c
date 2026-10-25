/*
 * Problem    : 74. Search a 2D Matrix
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : Oct 25, 2026
 * Language   : C
 * Difficulty : Medium
 * Tags       : Array, Binary Search, Matrix
 * Link       : https://leetcode.com/problems/search-a-2d-matrix
 *
 * Time       : O(log(m * n)) where m is the number of rows and n is the number of columns in the matrix
 * Space      : O(1)
 */

#include <stdio.h>
#include <stdbool.h>

bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    /* convert 1D index to 2D coordinates */
    #define getRowCol(index, colSize, row, col) \
        do { \
            row = index / colSize; \
            col = index % colSize; \
        } while (0)

    int left = 0;
    int right = matrixSize * matrixColSize[0] - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int row, col;
        getRowCol(mid, matrixColSize[0], row, col);
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

int main()
{
    int r0[] = {1, 3, 5, 7};
    int r1[] = {10, 11, 16, 20};
    int r2[] = {23, 30, 34, 60};
    int* matrix[] = {r0, r1, r2};
    int matrixSize = 3;
    int matrixColSize[] = {4, 4, 4};
    int target = 3;

    bool result = searchMatrix(matrix, matrixSize, matrixColSize, target);
    if (result) {
        printf("Target %d found in the matrix.\n", target);
    } else {
        printf("Target %d not found in the matrix.\n", target);
    }

    return 0;
}

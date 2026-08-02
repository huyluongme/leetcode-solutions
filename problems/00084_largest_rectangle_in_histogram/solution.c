/*
 * Problem    : 84. Largest Rectangle in Histogram
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : August 03, 2026
 * Language   : C
 * Difficulty : Hard
 * Tags       : Array, Stack, Monotonic Stack
 * Link       : https://leetcode.com/problems/largest-rectangle-in-histogram
 *
 * Time       : O(n)
 * Space      : O(n)
 */

#include <stdio.h>
#include <stdlib.h>

int largestRectangleArea(int* heights, int heightsSize) {
    int sp = -1;
    int *stack = (int*)malloc(heightsSize * sizeof(int));
    int maxArea = 0;

    for (int i = 0; i < heightsSize; ++i) {
        while (sp != -1 && heights[i] < heights[stack[sp]]) {
            int top = stack[sp--];
            int height = heights[top];
            int width = sp == -1 ? i : i - stack[sp] - 1;
            int area = height * width;
            if (area > maxArea) {
                maxArea = area;
            }
        }
        stack[++sp] = i;
    }

    while (sp != -1) {
        int top = stack[sp--];
        int height = heights[top];
        int width = sp == -1 ? heightsSize : heightsSize - stack[sp] - 1;
        int area = height * width;
        if (area > maxArea) {
            maxArea = area;
        }
    }

    free(stack);
    return maxArea;
}

int main()
{
    int heights[] = {2,1,5,6,2,3};
    int heightsSize = sizeof(heights) / sizeof(heights[0]);
    int result = largestRectangleArea(heights, heightsSize);
    printf("Largest rectangle area: %d\n", result);
    return 0;
}

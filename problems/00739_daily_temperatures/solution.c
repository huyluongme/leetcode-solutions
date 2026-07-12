/*
 * Problem    : 739. Daily Temperatures
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : July 12, 2026
 * Language   : C
 * Difficulty : Medium
 * Tags       : Staff, Array, Stack, Monotonic Stack
 * Link       : https://leetcode.com/problems/daily-temperatures
 *
 * Time       : O(n)
 * Space      : O(n)
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    int* ans = (int*)malloc(sizeof(int) * temperaturesSize);

    for (int i = 0; i < temperaturesSize; ++i)
        ans[i] = 0;

    int* stack = (int*)malloc(sizeof(int) * temperaturesSize);
    int top = -1;

    for (int i = 0; i < temperaturesSize; ++i) {
        while (top != -1 && temperatures[stack[top]] < temperatures[i]) {
            ans[stack[top]] = i - stack[top];
            top--;
        }
        top++;
        stack[top] = i;
    }

    *returnSize = temperaturesSize;

    free(stack);
    return ans;
}

int main()
{
    int temperatures[] = {73, 74, 75, 71, 69, 72, 76, 73};
    int temperaturesSize = sizeof(temperatures) / sizeof(temperatures[0]);
    int returnSize;
    int* result = dailyTemperatures(temperatures, temperaturesSize, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}

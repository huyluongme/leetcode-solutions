/*
 * Problem    : 11. Container With Most Water
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : Sep 4, 2026
 * Language   : C
 * Difficulty : Medium
 * Tags       : Array, Two Pointers, Greedy
 * Link       : https://leetcode.com/problems/container-with-most-water
 *
 * Time       : O(n)
 * Space      : O(1)
 */

#include <stdio.h>
#include <stdlib.h>

int maxArea(int* height, int heightSize) {
    int left, right, res = 0;

    left = 0;
    right = heightSize - 1;

    while (left < right) {
        int width = right - left;
        int h = (height[left] < height[right] ? height[left] : height[right]);
        int area = width * h;
        res = (area > res) ? area : res;

        if (height[left] < height[right]) left++;
        else right--;
    }

    return res;
}

int main()
{
    int height[] = {1,8,6,2,5,4,8,3,7};
    int heightSize = sizeof(height) / sizeof(height[0]);
    int max = maxArea(height, heightSize);

    printf("%d\n", max);

    return 0;
}
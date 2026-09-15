/*
 * Problem    : 42. Trapping Rain Water
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : Sep 13, 2026
 * Language   : C
 * Difficulty : Hard
 * Tags       : Array, Two Pointers, Dynamic Programming, Stack, Monotonic Stack
 * Link       : https://leetcode.com/problems/trapping-rain-water
 *
 * Time       : O(n)
 * Space      : O(1)
 */

#include <stdio.h>

int trap(int* height, int heightSize) {
    int left = 0, right = heightSize - 1;
    int left_max = 0, right_max = 0;
    int water = 0;

    while (left <= right) {
        if (height[left] <= height[right]) {
            if (height[left] >= left_max)
                left_max = height[left];
            else
                water += left_max - height[left];

            left++;
        }
        else {
            if (height[right] >= right_max)
                right_max = height[right];
            else
                water += right_max - height[right];

            right--;
        }
    }

    return water;
}

int main()
{
    int height[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int heightSize = sizeof(height)/sizeof(height[0]);

    printf("%d\n", trap(height, heightSize));

    return 0;
}

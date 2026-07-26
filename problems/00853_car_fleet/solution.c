/*
 * Problem    : 853. Car Fleet
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : July 26, 2026
 * Language   : C
 * Difficulty : Medium
 * Tags       : Array, Stack, Sorting, Monotonic Stack
 * Link       : https://leetcode.com/problems/car-fleet
 *
 * Time       : O(N log N) - due to sorting cars by position
 * Space      : O(N)       - for storing car structs array
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int position;
    double time;
} Car;

int compareCars(const void* a, const void* b) {
    Car* carA = (Car*)a;
    Car* carB = (Car*)b;
    // Sort in descending order of position
    if (carB->position > carA->position) return 1;
    if (carB->position < carA->position) return -1;
    return 0;
}

int carFleet(int target, int* position, int positionSize, int* speed, int speedSize) {
    (void)speedSize;
    if (positionSize == 0) return 0;

    Car* cars = (Car*)malloc(sizeof(Car) * positionSize);
    for (int i = 0; i < positionSize; i++) {
        cars[i].position = position[i];
        cars[i].time = (double)(target - position[i]) / speed[i];
    }

    // Sort cars by position descending (from closest to target to farthest)
    qsort(cars, positionSize, sizeof(Car), compareCars);

    int fleets = 0;
    double maxTime = 0.0; // Monotonic stack top representation

    for (int i = 0; i < positionSize; i++) {
        // If current car takes strictly more time than the fleet ahead,
        // it cannot catch up and forms a new fleet.
        if (cars[i].time > maxTime) {
            fleets++;
            maxTime = cars[i].time;
        }
    }

    free(cars);
    return fleets;
}

int main()
{
    int target = 12;
    int position[] = {10, 8, 0, 5, 3};
    int speed[] = {2, 4, 1, 1, 3};
    int n = sizeof(position) / sizeof(position[0]);

    int result = carFleet(target, position, n, speed, n);
    printf("Number of car fleets: %d\n", result); // Expected output: 3

    return 0;
}
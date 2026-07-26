/*
 * Problem    : 853. Car Fleet
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : July 26, 2026
 * Language   : C++
 * Difficulty : Medium
 * Tags       : Array, Stack, Sorting, Monotonic Stack
 * Link       : https://leetcode.com/problems/car-fleet
 *
 * Time       : O(n log n)
 * Space      : O(n)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        if (n == 0) return 0;

        // Pair: {position, time_to_reach_target}
        vector<pair<int, double>> cars(n);
        for (int i = 0; i < n; ++i) {
            cars[i] = {position[i], static_cast<double>(target - position[i]) / speed[i]};
        }

        // Sort cars by position descending (closest to target first)
        sort(cars.begin(), cars.end(), [](const pair<int, double>& a, const pair<int, double>& b) {
            return a.first > b.first;
        });

        int fleets = 0;
        double maxTime = 0.0; // Monotonic stack top representation

        for (int i = 0; i < n; ++i) {
            // If current car takes strictly more time than the fleet ahead,
            // it cannot catch up and forms a new fleet.
            if (cars[i].second > maxTime) {
                fleets++;
                maxTime = cars[i].second;
            }
        }

        return fleets;
    }
};

int main()
{
    int target = 12;
    vector<int> position = {10, 8, 0, 5, 3};
    vector<int> speed = {2, 4, 1, 1, 3};

    Solution sol;
    int result = sol.carFleet(target, position, speed);

    cout << "Number of car fleets: " << result << endl; // Expected output: 3

    return 0;
}
# Two Pointer Fundamentals

## Table of Contents
1. [Introduction](#introduction)
2. [How Two Pointers Work](#how-two-pointers-work)
3. [Basic Concepts](#basic-concepts)
4. [Common Patterns & Use Cases](#common-patterns--use-cases)
   - [1. Opposite-Direction Pointers (Converging)](#1-opposite-direction-pointers-converging)
   - [2. Fast & Slow Pointers (Same Direction)](#2-fast--slow-pointers-same-direction)
   - [3. Sorted-Array K-Sum (Fixed Pointer + Two Pointers)](#3-sorted-array-k-sum-fixed-pointer--two-pointers)
   - [4. Greedy Boundary Shrinking](#4-greedy-boundary-shrinking)
   - [5. Precomputed Prefix/Suffix Bounds](#5-precomputed-prefixsuffix-bounds)
5. [Complexity Analysis](#complexity-analysis)
6. [Best Practices](#best-practices)
7. [Key Takeaways](#key-takeaways)

## Introduction

The **two pointer** technique uses two indices (pointers) that traverse a data structure — typically an array or string — instead of using nested loops. By moving the pointers according to some rule based on the values they point to, many $O(n^2)$ brute-force problems can be solved in $O(n)$ or $O(n \log n)$ time, usually with $O(1)$ extra space.

It's less a data structure than a *traversal strategy*, and it shows up constantly in array/string problems, especially when the input is **sorted** or when you're searching for **pairs, triplets, or subranges** that satisfy some condition.

## How Two Pointers Work

### The Basic Process

1. Place two indices, `left` and `right`, at meaningful starting positions (e.g., both ends of the array, or both starting at index `0`).
2. Inspect the values at `left` and `right` (or `left` and `left + 1`, depending on the pattern).
3. Decide which pointer(s) to move based on a comparison — usually to shrink a search space or skip values that can't be part of the answer.
4. Repeat until the pointers cross or meet, or until a stopping condition is satisfied.

```
Opposite-direction (converging):

  left ──>                          <── right
  [ 2 , 7 , 11 , 15 , 18 , 24 , 30 ]
    ^                            ^
  left=0                     right=6

Same-direction (fast & slow):

  slow ──>
  [ a , b , c , c , d ]
        fast ──>
```

## Basic Concepts

### Key Properties

- **Monotonic progress**: at least one pointer always moves closer to the other (or in the same direction), guaranteeing the algorithm terminates in at most $O(n)$ steps.
- **Search space reduction**: each comparison eliminates at least one candidate index from further consideration — this is what turns $O(n^2)$ into $O(n)$.
- **Sorted input helps a lot**: many two-pointer patterns (opposite-direction sum, k-sum) rely on the array being sorted so that moving a pointer has a predictable effect on the sum/comparison.
- **In-place, $O(1)$ extra space**: unlike hash-table approaches, two pointers usually don't need auxiliary storage beyond the pointers themselves (aside from the output).

## Common Patterns & Use Cases

### 1. Opposite-Direction Pointers (Converging)

Start `left` at the beginning and `right` at the end, then move them toward each other based on a comparison. This is the classic pattern for checking a property that reads from both ends at once (palindromes) or for finding a pair with a target sum in a **sorted** array.

**Example A: Valid Palindrome (LeetCode 125)**

Skip non-alphanumeric characters from both ends and compare case-insensitively; if every pair matches before the pointers meet, the string is a palindrome.

```cpp
bool isPalindrome(string s) {
    int left = 0, right = s.size() - 1;

    while (left < right) {
        if (!isalnum(s[left])) { left++; continue; }
        if (!isalnum(s[right])) { right--; continue; }

        if (tolower(s[left]) != tolower(s[right]))
            return false;

        left++;
        right--;
    }

    return true;
}
```

Full solution: [solution.cpp](../../problems/00125_valid_palindrome/solution.cpp)

**Example B: Two Sum II - Input Array Is Sorted (LeetCode 167)**

Because the array is sorted, if `numbers[left] + numbers[right]` is too small, only increasing `left` can help; if it's too large, only decreasing `right` can help. This avoids checking every pair.

```cpp
vector<int> twoSum(vector<int>& numbers, int target) {
    int left = 0, right = numbers.size() - 1;

    while (left < right) {
        int sum = numbers[left] + numbers[right];

        if (sum == target) return {left + 1, right + 1};
        if (sum < target) left++;
        else right--;
    }

    return {};
}
```

Full solution: [solution.cpp](../../problems/00167_two_sum_II_input_array_is_sorted/solution.cpp)

### 2. Fast & Slow Pointers (Same Direction)

Both pointers move forward (never backward), but at different rates or under different conditions — one advances every step (`fast`), the other only advances when a condition holds (`slow`). Common for in-place array de-duplication/compaction and cycle detection in linked lists (e.g. Floyd's algorithm).

```cpp
// In-place removal of duplicates from a sorted array
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;

    int slow = 0;
    for (int fast = 1; fast < nums.size(); fast++) {
        if (nums[fast] != nums[slow]) {
            slow++;
            nums[slow] = nums[fast];
        }
    }

    return slow + 1;
}
```

### 3. Sorted-Array K-Sum (Fixed Pointer + Two Pointers)

Sort the array, fix one (or more) index with an outer loop, then use the opposite-direction two-pointer pattern on the remaining subarray to find the rest of the sum. Skipping duplicate values at each level avoids duplicate triplets/quadruplets in the result.

**Example: 3Sum (LeetCode 15)**

```cpp
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    int n = nums.size();
    sort(nums.begin(), nums.end());

    for (int i = 0; i < n - 2; ++i) {
        if (nums[i] > 0) break;                         // no valid triplet possible from here on
        if (i > 0 && nums[i] == nums[i - 1]) continue;   // skip duplicate anchors

        int left = i + 1, right = n - 1;

        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];

            if (sum < 0) {
                left++;
            } else if (sum > 0) {
                right--;
            } else {
                res.push_back({nums[i], nums[left], nums[right]});
                left++;
                right--;

                while (left < right && nums[left] == nums[left - 1]) left++;   // skip duplicate left
                while (left < right && nums[right] == nums[right + 1]) right--; // skip duplicate right
            }
        }
    }

    return res;
}
```

Full solution: [solution.cpp](../../problems/00015_3Sum/solution.cpp)

*Note: 4Sum extends this pattern by adding one more fixed outer loop before the same two-pointer inner scan.*

### 4. Greedy Boundary Shrinking

The pointers start at the widest possible boundary and shrink inward, always discarding the side that *cannot* improve the answer. This works when you can prove that keeping the "worse" boundary can never lead to a better result than moving past it.

**Example: Container With Most Water (LeetCode 11)**

The area is bounded by `min(height[left], height[right]) * (right - left)`. Moving the taller boundary inward can only shrink the width without possibly increasing the limiting height, so it's always safe (and only useful) to move the **shorter** side.

```cpp
int maxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int res = 0;

    while (left < right) {
        int width = right - left;
        int h = min(height[left], height[right]);
        res = max(res, width * h);

        if (height[left] < height[right]) left++;
        else right--;
    }

    return res;
}
```

Full solution: [solution.cpp](../../problems/00011_container_with_most_water/solution.cpp)

### 5. Precomputed Prefix/Suffix Bounds

Some problems need, for each position, the maximum (or minimum) seen so far from *both* directions. Instead of precomputing two full arrays (`leftMax[]` / `rightMax[]`, $O(n)$ space), two pointers moving inward can track running maximums on the fly and resolve each index in $O(1)$ extra space.

**Example: Trapping Rain Water (LeetCode 42)**

The water trapped above index `i` is `min(leftMax, rightMax) - height[i]`. At each step, advance whichever side has the smaller running max — that side's water level is already determined regardless of what the far side eventually reaches.

```cpp
int trap(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int left_max = 0, right_max = 0;
    int water = 0;

    while (left < right) {
        if (height[left] <= height[right]) {
            if (height[left] >= left_max) left_max = height[left];
            else water += left_max - height[left];
            left++;
        } else {
            if (height[right] >= right_max) right_max = height[right];
            else water += right_max - height[right];
            right--;
        }
    }

    return water;
}
```

Full solution: [solution.cpp](../../problems/00042_trapping_rain_water/solution.cpp)

*Note: this same problem can also be solved with a monotonic stack — see [Stack Fundamentals](../stack/) — but the two-pointer version needs only $O(1)$ extra space instead of $O(n)$.*

---

## Complexity Analysis

### Time Complexity

| Pattern | Time Complexity | Notes |
|---------|------------------|-------|
| Opposite-direction (palindrome, pair sum) | $O(n)$ | Each pointer moves at most $n$ times total. |
| Fast & slow | $O(n)$ | `fast` visits every element once. |
| K-Sum (fixed + two pointers) | $O(n^{k-1})$ | $O(n \log n)$ sort + $(k-2)$ nested loops, innermost is $O(n)$ two-pointer scan. 3Sum is $O(n^2)$. |
| Greedy boundary shrinking | $O(n)$ | Each step strictly shrinks the window by moving exactly one pointer. |
| Prefix/suffix bounds via two pointers | $O(n)$ | Replaces two $O(n)$ precomputed arrays with $O(1)$ running state. |

### Space Complexity

- **Auxiliary space**: $O(1)$ for the pointers themselves and any running aggregates (sum, max seen so far).
- **Output space**: not counted against the technique — e.g., 3Sum's result list is required output, not overhead.
- Sorting (when required, e.g. for k-sum patterns) adds $O(\log n)$ to $O(n)$ space depending on the sort implementation, and $O(n \log n)$ time.

---

## Best Practices

### 1. Sort First When the Pattern Needs Monotonic Behavior
Opposite-direction sum-matching and k-sum patterns only work correctly because moving a pointer has a *predictable* effect on the running sum — that requires sorted input.

```cpp
sort(nums.begin(), nums.end()); // required before two-pointer k-sum
```

### 2. Guard the Loop Condition Consistently
Use `left < right` (not `<=`) when the pointers must not point at the same or overlapping elements, otherwise you risk double-counting or reading the same index as both "left" and "right".

### 3. Skip Duplicates Explicitly in K-Sum Problems
Without an explicit duplicate-skip step, k-sum patterns produce duplicate triplets/quadruplets in the result even though the underlying two-pointer logic is otherwise correct.

```cpp
while (left < right && nums[left] == nums[left - 1]) left++;
```

### 4. Prove the Greedy Move Is Safe Before Coding It
For patterns like Container With Most Water, always moving the "worse" pointer only works because you can prove the discarded pointer position can never produce a strictly better answer later. If that proof doesn't hold for your problem, two pointers may give a wrong answer — verify with a brute-force check on small inputs first.

### 5. Watch for Off-by-One Errors at the Boundaries
`right = size() - 1` (not `size()`), and remember empty or single-element inputs (`size() < 2`) often need an early return before the main loop.

---

## Key Takeaways

- **Two indices, one pass**: replaces nested-loop $O(n^2)$ brute force with a single linear scan in most cases.
- **Opposite-direction** pointers converge toward each other; **fast & slow** pointers move in the same direction at different rates.
- **Sorted input unlocks k-sum patterns**: fix outer indices with a loop, solve the remaining 2-sum with converging pointers.
- **Greedy correctness must be proven**, not assumed — the technique only works when moving one pointer is provably never worse than the alternative.
- **$O(1)$ extra space** is the main advantage over hash-table or precomputed-array alternatives to the same problems.

---

**References:**
- Two Pointer Technique: [GeeksforGeeks](https://www.geeksforgeeks.org/dsa/two-pointers-technique/)
- Sliding Window & Two Pointers: [LeetCode Explore](https://leetcode.com/explore/learn/card/array-and-string/)

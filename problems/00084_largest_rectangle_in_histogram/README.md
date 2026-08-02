# 84. Largest Rectangle in Histogram

## 1. Problem Overview
Given an array of integers `heights` representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

- **Problem Link**: [LeetCode - 84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram)
- **Difficulty**: Hard
- **Algorithm**: **Monotonic Stack (Monotonic Increasing Stack)**
- **Complexity**:
  - **Time Complexity**: $\mathcal{O}(N)$ — Each bar index is pushed and popped from the stack at most once.
  - **Space Complexity**: $\mathcal{O}(N)$ — Auxiliary space used by the stack.

---

## 2. Core Mechanism (Monotonic Stack)

### Key Concept
For a bar at index `top` with height $H = \text{heights}[\text{top}]$, we want to determine the maximum width of a rectangle of height $H$ extending both to the left and to the right:

1. **Right Boundary**:
   - When iterating at index `i` such that $\text{heights}[i] < \text{heights}[\text{top}]$, the bar at index `top` **cannot extend further to the right**.
   - Index `i` serves as the right boundary (exclusive, meaning it extends up to `i - 1`).

2. **Left Boundary**:
   - In a monotonic increasing stack, the element directly below `top` (denoted as `st.top()`) is the nearest bar to the left that is strictly shorter than $\text{heights}[\text{top}]$.
   - The left boundary extends to `st.top() + 1` (inclusive).
   - If the stack becomes empty after popping `top`, it means $\text{heights}[\text{top}]$ was the smallest bar so far and can extend all the way to index `0`.

3. **Width and Area Calculation**:
   - If stack is **not empty**: $\text{width} = i - \text{st.top}() - 1$
   - If stack is **empty**: $\text{width} = i$
   - $\text{area} = \text{height} \times \text{width}$

---

## 3. Step-by-Step Visualization (Dry Run)

Example input: `heights = [2, 1, 5, 6, 2, 3]` ($N = 6$)

### Initial Histogram:
```text
      6    |        ██  
      5    |     ██ ██  
      4    |     ██ ██  
      3    |     ██ ██    ██
      2    | ██  ██ ██ ██ ██
      1    | ██ ██ ██ ██ ██ ██
           +------------------
Index:        0  1  2  3  4  5
Height:       2  1  5  6  2  3
```

---

### Phase 1: Iterating through the array (`i` from 0 to 5)

| Step `i` | Value `heights[i]` | Action | Area Calculation | Stack State (Indices) | `maxArea` |
| :---: | :---: | :--- | :--- | :--- | :---: |
| **0** | **2** | Push `0` | Stack empty $\rightarrow$ No pop | `[0]` | `0` |
| **1** | **1** | `1 < heights[0]` (2)<br>$\rightarrow$ **Pop 0** | `height = heights[0] = 2`<br>Stack empty $\rightarrow$ `width = i = 1`<br>$\rightarrow$ `area = 2 * 1 = 2` | `[]` | `2` |
| | | Push `1` | Push index 1 to stack | `[1]` | `2` |
| **2** | **5** | `5 >= heights[1]` (1)<br>$\rightarrow$ Push `2` | No pop | `[1, 2]` | `2` |
| **3** | **6** | `6 >= heights[2]` (5)<br>$\rightarrow$ Push `3` | No pop | `[1, 2, 3]` | `2` |
| **4** | **2** | `2 < heights[3]` (6)<br>$\rightarrow$ **Pop 3** | `height = heights[3] = 6`<br>`st.top() = 2` $\rightarrow$ `width = 4 - 2 - 1 = 1`<br>$\rightarrow$ `area = 6 * 1 = 6` | `[1, 2]` | `6` |
| | | `2 < heights[2]` (5)<br>$\rightarrow$ **Pop 2** | `height = heights[2] = 5`<br>`st.top() = 1` $\rightarrow$ `width = 4 - 1 - 1 = 2`<br>$\rightarrow$ `area = 5 * 2 = 10` | `[1]` | **`10`** |
| | | `2 >= heights[1]` (1)<br>$\rightarrow$ Stop pop $\rightarrow$ Push `4` | Push index 4 to stack | `[1, 4]` | `10` |
| **5** | **3** | `3 >= heights[4]` (2)<br>$\rightarrow$ Push `5` | No pop | `[1, 4, 5]` | `10` |

---

### Phase 2: Processing remaining elements in Stack

Use $N = 6$ as the common right boundary for all remaining indices in the stack:

| Action | Area Calculation | Stack State | `maxArea` |
| :--- | :--- | :--- | :---: |
| **Pop 5** | `height = heights[5] = 3`<br>`st.top() = 4` $\rightarrow$ `width = 6 - 4 - 1 = 1`<br>$\rightarrow$ `area = 3 * 1 = 3` | `[1, 4]` | `10` |
| **Pop 4** | `height = heights[4] = 2`<br>`st.top() = 1` $\rightarrow$ `width = 6 - 1 - 1 = 4`<br>$\rightarrow$ `area = 2 * 4 = 8` | `[1]` | `10` |
| **Pop 1** | `height = heights[1] = 1`<br>Stack empty $\rightarrow$ `width = N = 6`<br>$\rightarrow$ `area = 1 * 6 = 6` | `[]` | **`10`** |

---

### Final Result

The maximum rectangle area is **`10`**, formed by the bars at index 2 and 3 with a shared height of 5 and width of 2.

```text
      6    |        ██  
      5    |     ▒▒ ▒▒        <-- Largest Rectangle (Height: 5, Width: 2)
      4    |     ▒▒ ▒▒            Area = 5 * 2 = 10
      3    |     ▒▒ ▒▒    ██
      2    | ██  ▒▒ ▒▒ ██ ██
      1    | ██  ▒▒ ▒▒ ██ ██
           +------------------
Index:        0  1  2  3  4  5
```

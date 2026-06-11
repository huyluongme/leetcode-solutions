# 128. Longest Consecutive Sequence — Algorithm Idea & Optimization in C

This document explains the core idea behind the optimal $O(N)$ time complexity solution for the "Longest Consecutive Sequence" problem, alongside C-specific low-level performance optimization techniques.

---

## 1. Core Idea

### Problem Statement
Given an unsorted array of integers `nums`, find the length of the longest consecutive elements sequence. The algorithm must run in $O(N)$ time.

*Example*:
- **Input**: `nums = [100, 4, 200, 1, 3, 2]`
- **Output**: `4` (the longest consecutive sequence is `[1, 2, 3, 4]`).

---

### Optimal $O(N)$ Strategy
A simple approach is sorting the array and finding consecutive segments. However, sorting takes $O(N \log N)$ time. To achieve $O(N)$, we must use a **Hash Set** to check for the existence of elements in $O(1)$ average time.

Simply iterating through every number and counting consecutive values starting from it can still degrade to $O(N^2)$ (e.g., if the array is already fully sorted).

To guarantee linear $O(N)$ time complexity, we apply the following rule: **Only start counting a sequence from its absolute minimum element (the Start of Sequence).**

1. Populate all elements in the array into a custom **Hash Set** for $O(1)$ lookup times while deduplicating entries (storing unique elements in the `uniq` array).
2. For each unique element `val` in `uniq`:
   - Check if `val - 1` exists in the Hash Set.
   - **If `val - 1` exists in the set**: Skip `val`. Since `val` is not the beginning of the sequence, the sequence containing it will eventually be counted starting from its smallest element.
   - **If `val - 1` does NOT exist in the set**: This means `val` is the starting element of a sequence. We start a loop to count the length of the sequence (`val`, `val + 1`, `val + 2`, ...).
3. Update the maximum length found so far (`best`).

> **Proof of $O(N)$ Time Complexity**:
> Each element is visited at most twice: once when checking if it can start a sequence (via `val - 1`), and at most once more inside the counting loop (each sequence is scanned exactly once). This guarantees that the total step count is linear relative to $N$.

---

## 2. C-Specific Implementation & Performance Optimization

Since C does not have a built-in Hash Set (like C++'s `std::unordered_set` or Java's `HashSet`), we implement a high-performance custom hash set utilizing low-level hardware optimizations:

### A. Power of Two Sizing
Instead of using an arbitrary size, the hash set size `mod` is rounded up to the next power of 2 such that the load factor is at most 50% (`mod >= 2 * numsSize`).
This yields two major benefits:
- It significantly reduces hash collisions.
- It replaces the slow CPU division/modulo operator (`%`) with a single-cycle bitwise AND (`&`) operation:
  $$\text{index} = \text{hash} \ \& \ (\text{mod} - 1)$$

### B. Fibonacci Hashing (Shift-Right)
To prevent adversarial test cases (e.g., arithmetic progressions with step sizes matching powers of 2 that would cause all elements to collide in the same bucket), we apply **Fibonacci Hashing**:
$$\text{hash} = (\text{val} \times 2654435761\text{u}) \gg \text{shift}$$
- The multiplier $2654435761\text{u} \approx 2^{32} \times (\frac{\sqrt{5}-1}{2})$ is the golden ratio fraction of a 32-bit integer.
- The multiplication effectively scatters the input bit values across the entire $2^{32}$ range.
- Shifting right by `shift` (where $\text{shift} = 32 - \log_2(\text{mod})$) extracts the highest, most well-distributed bits, minimizing collision risks.

### C. Linear Probing & Cache Locality
When a hash collision occurs, the algorithm searches adjacent cells: `hash = (hash + 1) & mask`.
- Linear probing is exceptionally cache-friendly. When a cache line is loaded from system memory, neighboring cells are automatically fetched into the CPU L1/L2 cache. Probing contiguous memory locations avoids slow RAM accesses.

### D. Avoiding Stack Overflow
Rather than using Variable Length Arrays (VLA) on the stack (which can easily cause crash/Segmentation Faults on LeetCode when $N = 10^5$, as it requires $>1.6$ MB of stack space), memory for the hash set and unique list is dynamically allocated on the heap via `malloc` and freed at the end of the function.

---

## 3. Algorithm Flowchart

```mermaid
graph TD
    A[Start] --> B{numsSize == 0?}
    B -- Yes --> C[Return 0]
    B -- No --> D[Compute mod as next power of 2]
    D --> E[Malloc set and uniq on Heap]
    E --> F[Insert elements into set & collect unique values in uniq]
    F --> G[Iterate over each val in uniq]
    G --> H{val - 1 in set?}
    H -- Yes --> I[Skip element]
    H -- No --> J[Start counting sequence from val + 1]
    J --> K[Search val + 2, val + 3... until INF encountered]
    K --> L[Update best length]
    I --> M[Move to next element]
    L --> M
    M --> N{Processed all uniq elements?}
    N -- No --> G
    N -- Yes --> O[Free memory and return best]
```

## 4. Complexity Analysis

- **Time Complexity**: $O(N)$ on average and in the worst case, thanks to Fibonacci hashing distribution and the start-of-sequence filtering.
- **Space Complexity**: $O(N)$ memory overhead to hold the `set` table and `uniq` array.

---

## 5. Step-by-Step Visualization

Let's walk through the execution of the algorithm with a sample input:
$$\text{nums} = [100, 4, 200, 1, 3, 2]$$

### Step 1: Capacity & Parameter Initialization
1. `numsSize = 6`.
2. Compute table capacity `mod`:
   * $6 \times 2 = 12$. The next power of 2 is **16**.
   * Therefore, `mod = 16`, `mask = 15` (binary `1111`), and `shift = 28` (since $16 = 2^4 \implies 32 - 4 = 28$).
3. Initialize a `set` array of size 16 filled with `INF`.
4. Initialize an empty `uniq` vector.

---

### Step 2: Populating the Hash Table & Deduplication
For each value in `nums`, we calculate `hash = (val * 2654435761u) >> 28`. If a collision occurs, we probe adjacent cells `(hash + 1) & 15`.

*   **Insert `100`**:
    *   $\text{hash} = (100 \times 2654435761) \gg 28 = 13$.
    *   `set[13]` is `INF`.
    *   Action: Set `set[13] = 100` and append `100` to `uniq`.
*   **Insert `4`**:
    *   $\text{hash} = (4 \times 2654435761) \gg 28 = 7$.
    *   `set[7]` is `INF`.
    *   Action: Set `set[7] = 4` and append `4` to `uniq`.
*   **Insert `200`**:
    *   $\text{hash} = (200 \times 2654435761) \gg 28 = 10$.
    *   `set[10]` is `INF`.
    *   Action: Set `set[10] = 200` and append `200` to `uniq`.
*   **Insert `1`**:
    *   $\text{hash} = (1 \times 2654435761) \gg 28 = 9$.
    *   `set[9]` is `INF`.
    *   Action: Set `set[9] = 1` and append `1` to `uniq`.
*   **Insert `3`**:
    *   $\text{hash} = (3 \times 2654435761) \gg 28 = 13$.
    *   `set[13]` is `100` (**collision!**).
    *   Probe cell: `(13 + 1) & 15 = 14`.
    *   `set[14]` is `INF`.
    *   Action: Set `set[14] = 3` and append `3` to `uniq`.
*   **Insert `2`**:
    *   $\text{hash} = (2 \times 2654435761) \gg 28 = 3$.
    *   `set[3]` is `INF`.
    *   Action: Set `set[3] = 2` and append `2` to `uniq`.

**State of variables at the end of Insertion:**
*   `uniq = [100, 4, 200, 1, 3, 2]`
*   `set` bucket layout:
    ```
    Index:  0   1   2   3   4   5   6   7   8   9   10  11  12  13   14  15
    Value: INF INF INF  2  INF INF INF  4  INF  1  200 INF INF 100   3  INF
    ```

---

### Step 3: Scanning and Counting Sequences
We iterate through `uniq` to look for sequence starts and count lengths:

1.  **Process `val = 100`**:
    *   Check `val - 1 = 99`. Its hash lookup finds `INF` (not in `set`).
    *   **Decision**: `100` is a sequence start.
    *   Scan upwards (`101`, `102`...): `101` lookup finds `INF`.
    *   Sequence length: **`1`** (`[100]`). Update `best = 1`.
2.  **Process `val = 4`**:
    *   Check `val - 1 = 3`. Its hash lookup finds `3` at index 14.
    *   **Decision**: `4` is **not** a sequence start. Skip it.
3.  **Process `val = 200`**:
    *   Check `val - 1 = 199`. Its hash lookup finds `INF`.
    *   **Decision**: `200` is a sequence start.
    *   Scan upwards (`201`...): `201` lookup finds `INF`.
    *   Sequence length: **`1`** (`[200]`). Update `best = max(1, 1) = 1`.
4.  **Process `val = 1`**:
    *   Check `val - 1 = 0`. Its hash lookup finds `INF`.
    *   **Decision**: `1` is a sequence start.
    *   Scan upwards:
        *   `2`: Found in `set[3]`.
        *   `3`: Found in `set[14]`.
        *   `4`: Found in `set[7]`.
        *   `5`: Lookup finds `INF` (stop).
    *   Sequence length: **`4`** (`[1, 2, 3, 4]`). Update `best = max(1, 4) = 4`.
5.  **Process `val = 3`**:
    *   Check `val - 1 = 2`. Its hash lookup finds `2` at index 3.
    *   **Decision**: `3` is **not** a sequence start. Skip it.
6.  **Process `val = 2`**:
    *   Check `val - 1 = 1`. Its hash lookup finds `1` at index 9.
    *   **Decision**: `2` is **not** a sequence start. Skip it.

### Step 4: Termination
The algorithm finishes iterating over `uniq` and returns `best = 4`.


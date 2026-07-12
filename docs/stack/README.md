# Stack Fundamentals

## Table of Contents
1. [Introduction](#introduction)
2. [How Stacks Work](#how-stacks-work)
3. [Basic Concepts](#basic-concepts)
4. [Basic Implementation in C/C++](#basic-implementation-in-cc)
5. [Stack Types & Implementations](#stack-types--implementations)
6. [Common Operations](#common-operations)
7. [Common Patterns & Use Cases](#common-patterns--use-cases)
8. [Complexity Analysis](#complexity-analysis)
9. [Best Practices](#best-practices)

## Introduction

A **stack** is a linear data structure that follows the **Last-In, First-Out (LIFO)** principle. This means that the last element added to the stack will be the first one to be removed. 

Analogies for a stack include:
- A stack of dinner plates (you add/remove from the top)
- A deck of cards
- The "Undo" mechanism in text editors
- The back/forward history in web browsers

## How Stacks Work

### The Basic Process

1. **Push**: Adding an element to the top of the stack.
2. **Pop**: Removing the top element from the stack.
3. **Peek/Top**: Inspecting the top element without removing it.

```
Push (Insert) ──>  [ Element 3 ]  ──> Pop (Delete)
                   [ Element 2 ]
                   [ Element 1 ]
                   └───────────┘
                       Stack
```

## Basic Concepts

### Key Properties

- **LIFO (Last-In, First-Out)**: The element at the top is the only accessible element.
- **Top**: The pointer or reference to the last inserted element.
- **Overflow**: Attempting to push an element onto a stack that has reached its maximum capacity.
- **Underflow**: Attempting to pop or peek an element from an empty stack.

## Basic Implementation in C/C++

### Using C++ Standard Library (Recommended)

#### C++ `std::stack`

In C++, `std::stack` is a container adaptor. By default, it uses `std::deque` as its underlying container, but it can also be configured to use `std::vector` or `std::list`.

```cpp
#include <stack>
#include <iostream>

using namespace std;

int main() {
    // Declare a stack of integers
    stack<int> s;
    
    // Push elements
    s.push(10);
    s.push(20);
    s.push(30);
    
    // Check size
    cout << "Stack size: " << s.size() << endl; // Output: 3
    
    // Access and print the top element
    cout << "Top element: " << s.top() << endl; // Output: 30
    
    // Pop the top element
    s.pop();
    cout << "Top element after pop: " << s.top() << endl; // Output: 20
    
    // Check if empty
    if (!s.empty()) {
        cout << "Stack is not empty" << endl;
    }
    
    // Emptying the stack
    while (!s.empty()) {
        cout << "Popping: " << s.top() << endl;
        s.pop();
    }
    
    return 0;
}
```

**Output:**
```
Stack size: 3
Top element: 30
Top element after pop: 20
Stack is not empty
Popping: 20
Popping: 10
```

#### Changing the Underlying Container

You can specify a different container (like `std::vector` or `std::list`) to back `std::stack`:

```cpp
#include <stack>
#include <vector>
#include <list>
#include <iostream>

using namespace std;

int main() {
    // Stack backed by std::vector
    stack<int, vector<int>> vectorStack;
    
    // Stack backed by std::list
    stack<int, list<int>> listStack;
    
    vectorStack.push(5);
    listStack.push(10);
    
    cout << "Vector-backed stack top: " << vectorStack.top() << endl;
    cout << "List-backed stack top: " << listStack.top() << endl;
    
    return 0;
}
```

---

## Stack Types & Implementations

You can implement a stack from scratch using either a **fixed-size array** (or dynamic array) or a **linked list**.

### 1. Array-Based Stack Implementation

An array-based implementation is fast, has great cache locality, but typically has a fixed maximum size (unless using a dynamic array like `std::vector`).

```cpp
#include <iostream>

using namespace std;

class ArrayStack {
private:
    static const int MAX_SIZE = 1000;
    int arr[MAX_SIZE];
    int topIndex;

public:
    ArrayStack() {
        topIndex = -1; // Stack is empty
    }

    // Push an element
    bool push(int val) {
        if (topIndex >= MAX_SIZE - 1) {
            cout << "Stack Overflow!" << endl;
            return false;
        }
        arr[++topIndex] = val;
        return true;
    }

    // Pop the top element
    bool pop() {
        if (topIndex < 0) {
            cout << "Stack Underflow!" << endl;
            return false;
        }
        topIndex--;
        return true;
    }

    // Get the top element
    int top() {
        if (topIndex < 0) {
            cout << "Stack is empty!" << endl;
            return -1; // Or throw exception
        }
        return arr[topIndex];
    }

    // Check if empty
    bool empty() {
        return topIndex < 0;
    }

    // Get the size
    int size() {
        return topIndex + 1;
    }
};

int main() {
    ArrayStack s;
    s.push(5);
    s.push(15);
    s.push(25);

    cout << "Top: " << s.top() << " | Size: " << s.size() << endl;
    s.pop();
    cout << "Top after pop: " << s.top() << " | Size: " << s.size() << endl;

    return 0;
}
```

### 2. Linked List-Based Stack Implementation

A linked list-based implementation grows dynamically and doesn't suffer from stack overflow (unless memory is completely exhausted), but requires extra memory for pointers and has poorer cache locality.

```cpp
#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedListStack {
private:
    Node* head;
    int count;

public:
    LinkedListStack() : head(nullptr), count(0) {}

    ~LinkedListStack() {
        while (!empty()) {
            pop();
        }
    }

    // Push an element (insert at the beginning of list)
    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        count++;
    }

    // Pop the top element
    bool pop() {
        if (empty()) {
            cout << "Stack Underflow!" << endl;
            return false;
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
        return true;
    }

    // Get the top element
    int top() {
        if (empty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return head->data;
    }

    // Check if empty
    bool empty() {
        return head == nullptr;
    }

    // Get size
    int size() {
        return count;
    }
};

int main() {
    LinkedListStack s;
    s.push(100);
    s.push(200);
    s.push(300);

    cout << "Top: " << s.top() << " | Size: " << s.size() << endl;
    s.pop();
    cout << "Top after pop: " << s.top() << " | Size: " << s.size() << endl;

    return 0;
}
```

### Implementation Comparison

| Feature | Array-Based | Linked List-Based |
|---------|-------------|-------------------|
| **Size Limit** | Fixed (unless dynamically resized) | Dynamic (only limited by heap memory) |
| **Time Complexity** | $O(1)$ for all operations | $O(1)$ for all operations |
| **Memory Efficiency** | High (no pointer overhead) | Low (overhead of pointers per node) |
| **Cache Locality** | Excellent (elements are contiguous) | Poor (elements are scattered in memory) |

---

## Common Operations

### 1. Push
Adds an element to the top.
```cpp
s.push(element);
```

### 2. Pop
Removes the top element. Does not return the element in C++ standard library.
```cpp
s.pop();
```

### 3. Top
Retrieves the top element without removing it.
```cpp
int element = s.top();
```

### 4. Size & Empty
Retrieves count of elements and checks if stack is empty.
```cpp
size_t count = s.size();
bool isEmpty = s.empty();
```

---

## Common Patterns & Use Cases

Stacks are extremely useful for problems that involve matching, nested structures, tracking history, or keeping track of elements in a specific order (like backtracking or monotone properties).

### 1. Parentheses / Bracket Matching (Nested Structures)

Since brackets must close in the reverse order they were opened (LIFO), stack is the perfect fit.

**Example: Valid Parentheses (LeetCode 20)**

```cpp
#include <stack>
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

bool isValid(string s) {
    stack<char> st;
    unordered_map<char, char> mapping = {
        {')', '('},
        {'}', '{'},
        {']', '['}
    };
    
    for (char c : s) {
        // If it is a closing bracket
        if (mapping.count(c)) {
            // Check if top matches the opening bracket
            if (st.empty() || st.top() != mapping[c]) {
                return false;
            }
            st.pop(); // Match found, pop
        } else {
            // It is an opening bracket, push to stack
            st.push(c);
        }
    }
    
    return st.empty(); // Should be empty if all matched
}

int main() {
    cout << boolalpha;
    cout << "isValid(\"()[]{}\"): " << isValid("()[]{}") << endl; // true
    cout << "isValid(\"(]\"): " << isValid("(]") << endl;         // false
    return 0;
}
```

### 2. Monotonic Stack

A **monotonic stack** is a stack that maintains its elements in a sorted order (either strictly/non-strictly increasing or decreasing) from bottom to top. It is a powerful pattern used to solve range query problems—especially **Next Greater/Smaller Element (NGE)** or **Previous Greater/Smaller Element (PGE)**—in linear $O(n)$ time complexity, compared to the naive $O(n^2)$ approach.

#### Types of Monotonic Stacks

| Type | Order (Bottom to Top) | Push Condition (New element $x$) | Typical Use Case |
|------|------------------------|----------------------------------|------------------|
| **Monotonic Increasing** | Increasing (e.g., `1, 3, 5, 8`) | Pop elements $\ge x$ before pushing | Find the next smaller element |
| **Monotonic Decreasing** | Decreasing (e.g., `8, 5, 3, 1`) | Pop elements $\le x$ before pushing | Find the next greater element |

#### Key Concept & Logic
When iterating through the array:
1. If the current element violates the monotonic property, we pop elements from the stack until the property is restored.
2. The popped elements have found their boundary (their "next greater/smaller" element), and we update their results.
3. We then push the current element onto the stack.
4. Since each element is pushed and popped at most once, the time complexity is amortized **$O(n)$**.

---

**Example A: Next Greater Element (Classic Pattern)**
Find the next greater element for each element in an array. If none exists, return `-1`.

```cpp
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

vector<int> nextGreaterElement(const vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st; // Stores elements (or indices)
    
    for (int i = n - 1; i >= 0; i--) {
        // Pop elements smaller than current element
        while (!st.empty() && st.top() <= nums[i]) {
            st.pop();
        }
        
        // The top of the stack is the next greater element
        if (!st.empty()) {
            result[i] = st.top();
        }
        
        st.push(nums[i]);
    }
    return result;
}

int main() {
    vector<int> nums = {2, 1, 2, 4, 3};
    vector<int> res = nextGreaterElement(nums);
    
    for (int num : res) {
        cout << num << " "; // Output: 4 2 4 -1 -1
    }
    cout << endl;
    return 0;
}
```

---

**Example B: Daily Temperatures (LeetCode 739)**

Given an array of integers `temperatures` representing the daily temperatures, return an array `answer` such that `answer[i]` is the number of days you have to wait after the $i$-th day to get a warmer temperature. If there is no future day for which this is possible, keep `answer[i] == 0` instead.

*   **Intuition:** We need to find the distance to the next warmer day (the next greater element). We can use a **Monotonic Decreasing Stack**.
*   **Indices on Stack:** Instead of storing temperature values directly, we store the **indices** of the days. This allows us to calculate the day difference using `current_index - stack_top_index`.

##### Trace Walkthrough (`temperatures = [73, 74, 75, 71, 69, 72, 76, 73]`)

| Index $i$ | Temp | Stack Status (before push) | Action & Pops | Result Array `ans` | Stack (after push) |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **0** | 73 | `[]` | Empty. Push index `0`. | `[0,0,0,0,0,0,0,0]` | `[0]` |
| **1** | 74 | `[0]` | `74 > temp[0]` (73). Pop `0`. `ans[0] = 1 - 0 = 1`. Push `1`. | `[1,0,0,0,0,0,0,0]` | `[1]` |
| **2** | 75 | `[1]` | `75 > temp[1]` (74). Pop `1`. `ans[1] = 2 - 1 = 1`. Push `2`. | `[1,1,0,0,0,0,0,0]` | `[2]` |
| **3** | 71 | `[2]` | `71 < temp[2]` (75). Push `3`. | `[1,1,0,0,0,0,0,0]` | `[2, 3]` |
| **4** | 69 | `[2, 3]` | `69 < temp[3]` (71). Push `4`. | `[1,1,0,0,0,0,0,0]` | `[2, 3, 4]` |
| **5** | 72 | `[2, 3, 4]` | `72 > temp[4]` (69). Pop `4`, `ans[4] = 5 - 4 = 1`. <br> `72 > temp[3]` (71). Pop `3`, `ans[3] = 5 - 3 = 2`. <br> `72 < temp[2]` (75). Push `5`. | `[1,1,0,2,1,0,0,0]` | `[2, 5]` |
| **6** | 76 | `[2, 5]` | `76 > temp[5]` (72). Pop `5`, `ans[5] = 6 - 5 = 1`. <br> `76 > temp[2]` (75). Pop `2`, `ans[2] = 6 - 2 = 4`. Push `6`. | `[1,1,4,2,1,1,0,0]` | `[6]` |
| **7** | 73 | `[6]` | `73 < temp[6]` (76). Push `7`. | `[1,1,4,2,1,1,0,0]` | `[6, 7]` |

##### C++ Implementation (Using `std::stack`)
Refer to the C++ implementation file: [solution.cpp](../../problems/00739_daily_temperatures/solution.cpp)

```cpp
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> ans;
        for (int i = 0; i < temperatures.size(); ++i) {
            ans.push_back(0);
        }

        stack<int> st; // Monotonic decreasing stack storing indices

        for (int i = 0; i < temperatures.size(); ++i) {
            // Pop elements smaller than current element and record their distance
            while (!st.empty() && temperatures[st.top()] < temperatures[i]) {
                ans[st.top()] = i - st.top();
                st.pop();
            }
            st.push(i);
        }

        return ans;
    }
};

int main()
{
    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};
    Solution* sol = new Solution();
    vector<int> result = sol->dailyTemperatures(temperatures);

    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << " ";
    }
    cout << endl;

    delete sol;
    return 0;
}
```

##### C Implementation (Using Array-based Stack)
Refer to the C implementation file: [solution.c](../../problems/00739_daily_temperatures/solution.c)

```c
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
        // While stack is not empty and current temperature is greater than temperatures[stack[top]]
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
```

---

### 3. Expression Evaluation & Conversion

Evaluating postfix expressions (Reverse Polish Notation) or converting infix to postfix.

**Example: Evaluate Reverse Polish Notation (LeetCode 150)**

```cpp
#include <stack>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int evalRPN(vector<string>& tokens) {
    stack<int> st;
    
    for (const string& token : tokens) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int val2 = st.top(); st.pop();
            int val1 = st.top(); st.pop();
            
            if (token == "+") st.push(val1 + val2);
            else if (token == "-") st.push(val1 - val2);
            else if (token == "*") st.push(val1 * val2);
            else if (token == "/") st.push(val1 / val2);
        } else {
            st.push(stoi(token));
        }
    }
    return st.top();
}

int main() {
    vector<string> rpn = {"2", "1", "+", "3", "*"}; // (2 + 1) * 3 = 9
    cout << "Result: " << evalRPN(rpn) << endl; // Output: 9
    return 0;
}
```

---

## Complexity Analysis

For standard operations on a stack (regardless of array or list representation):

### Time Complexity

| Operation | Time Complexity | Notes |
|-----------|-----------------|-------|
| **Push**  | $O(1)$          | Amortized $O(1)$ for dynamic arrays if resizing occurs. |
| **Pop**   | $O(1)$          | Always $O(1)$ since it only removes the top element. |
| **Top**   | $O(1)$          | Direct access to the top element. |
| **Size**  | $O(1)$          | Usually stored as a member variable. |
| **Empty** | $O(1)$          | Simply checks if size/pointer is zero. |

### Space Complexity

- **Overall Storage**: $O(n)$ where $n$ is the number of elements in the stack.
- **Auxiliary Space per Operation**: $O(1)$ auxiliary space.

---

## Best Practices

### 1. Always Check `empty()` Before calling `top()` or `pop()`
Calling `top()` or `pop()` on an empty stack results in undefined behavior (segmentation fault or runtime crash).

```cpp
// DANGEROUS:
stack<int> s;
int x = s.top(); // CRASH!

// SAFE:
if (!s.empty()) {
    int x = s.top();
    s.pop();
}
```

### 2. Choose the Underlying Container Wisely
- Use `std::deque` (default) if you need a general-purpose, chunk-allocated stack that doesn't reallocate large contiguous blocks of memory.
- Use `std::vector` if you want contiguous cache-friendly storage and don't mind occasional rehashing/expansion.
- Use `std::list` if you want to avoid contiguous reallocations entirely and need strictly constant-time insertion/removal without reallocations, although it has extra overhead per element.

### 3. Clear Stacks in Loops
When using stacks inside loops (e.g. processing multi-testcase datasets), remember to clear the stack if it is declared outside the loop:

```cpp
// Good practice to ensure stack is fresh
while (!s.empty()) {
    s.pop();
}
```

---

## Key Takeaways

- **LIFO (Last-In, First-Out)**: Stacks operate entirely from one end.
- **Standard Adaptor**: In C++, prefer using `<stack>`'s `std::stack`.
- **Recursion**: Under the hood, recursion uses the system call stack. Any recursive algorithm can be converted to an iterative one using an explicit stack.
- **Monotonic Stacks**: A key technique in array/string range queries to find the next greater/smaller element in linear time.

---

**References:**
- C++ Stack Documentation: [cppreference.com](https://en.cppreference.com/w/cpp/container/stack)
- Stack Data Structure Wikipedia: [wikipedia.org](https://en.wikipedia.org/wiki/Stack_(abstract_data_type))

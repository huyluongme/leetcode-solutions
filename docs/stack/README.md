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

### 2. Monotonic Stack (Next Greater Element)

A **monotonic stack** maintains its elements in a sorted order (increasing or decreasing). It's used to solve "next greater/smaller element" problems in $O(n)$ time.

**Example: Next Greater Element**

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

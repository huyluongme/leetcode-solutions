# Hash Table Fundamentals

## Table of Contents
1. [Introduction](#introduction)
2. [How Hash Tables Work](#how-hash-tables-work)
3. [Basic Concepts](#basic-concepts)
4. [Basic Implementation in C/C++](#basic-implementation-in-cc)
5. [Collision Handling Techniques](#collision-handling-techniques)
6. [Common Operations](#common-operations)
7. [Use Cases](#use-cases)
8. [Complexity Analysis](#complexity-analysis)
9. [Best Practices](#best-practices)

## Introduction

A **hash table** (or **hash map**) is a data structure that implements an associative array—a structure that maps keys to values. It uses a **hash function** to compute an index into an array of buckets or slots, from which the desired value can be found.

Hash tables are fundamental to computer science and are widely used for:
- Fast data retrieval
- Counting occurrences
- Caching
- Deduplication
- Finding relationships between elements

## How Hash Tables Work

### The Basic Process

1. **Hashing**: When you insert a key-value pair, the hash function converts the key into an index.
2. **Storing**: The value is stored at that index in the hash table.
3. **Retrieval**: To find a value, the same hash function is applied to the key.
4. **Collision Handling**: When two keys hash to the same index, a collision resolution strategy is used.

```
Key → Hash Function → Index → Bucket → Value
```

## Basic Concepts

### Key Properties

- **Load Factor**: ratio = (number of entries) / (number of buckets)
  - When load factor exceeds threshold (typically 0.75), the table is resized
  
- **Hash Function**: Should distribute keys uniformly across buckets
  - Good distribution reduces collisions
  - Should be fast to compute
  
- **Bucket**: Container that holds key-value pairs

- **Collision**: Occurs when two different keys hash to the same index

## Basic Implementation in C/C++

### Using C++ Standard Library (Recommended)

#### C++ `std::unordered_map`

The simplest and most recommended way to use hash tables in C++:

```cpp
#include <unordered_map>
#include <iostream>

using namespace std;

int main() {
    // Declare unordered_map with string keys and int values
    unordered_map<string, int> hashMap;
    
    // Insert elements
    hashMap["apple"] = 1;
    hashMap["banana"] = 2;
    hashMap["cherry"] = 3;
    
    // Access elements
    cout << "apple: " << hashMap["apple"] << endl;  // Output: apple: 1
    
    // Check if key exists
    if (hashMap.find("banana") != hashMap.end()) {
        cout << "banana found" << endl;
    }
    
    // Iterate through hash map
    for (auto& pair : hashMap) {
        cout << pair.first << " -> " << pair.second << endl;
    }
    
    // Get size
    cout << "Size: " << hashMap.size() << endl;
    
    // Erase element
    hashMap.erase("cherry");
    
    // Check load factor
    cout << "Load factor: " << hashMap.load_factor() << endl;
    cout << "Max load factor: " << hashMap.max_load_factor() << endl;
    
    return 0;
}
```

**Output:**
```
apple: 1
banana found
apple -> 1
banana -> 2
cherry -> 3
Size: 3
Load factor: 0.3
Max load factor: 1
```

#### C++ `std::map` (Ordered, uses Red-Black Tree)

When you need keys in sorted order:

```cpp
#include <map>
#include <iostream>

using namespace std;

int main() {
    // map maintains sorted order by key
    map<string, int> orderedMap;
    
    orderedMap["zebra"] = 1;
    orderedMap["apple"] = 2;
    orderedMap["banana"] = 3;
    
    // Elements are sorted by key
    for (auto& pair : orderedMap) {
        cout << pair.first << " -> " << pair.second << endl;
    }
    // Output: apple -> 2, banana -> 3, zebra -> 1
    
    return 0;
}
```

#### Simple Usage Examples

**Example 1: Count Word Frequency**
```cpp
#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<string> words = {"apple", "banana", "apple", "cherry", "banana", "apple"};
    unordered_map<string, int> frequency;
    
    for (const string& word : words) {
        frequency[word]++;
    }
    
    for (const auto& [word, count] : frequency) {
        cout << word << ": " << count << endl;
    }
    
    return 0;
}
```

**Example 2: Store Student Grades**
```cpp
#include <unordered_map>
#include <iostream>

using namespace std;

int main() {
    unordered_map<string, int> grades;
    
    // Insert
    grades.insert({"Alice", 85});
    grades["Bob"] = 92;
    grades.emplace("Charlie", 78);
    
    // Search
    if (grades.count("Bob")) {
        cout << "Bob's grade: " << grades["Bob"] << endl;
    }
    
    // Update
    grades["Alice"] = 90;
    
    // Delete
    grades.erase("Charlie");
    
    // Iterate
    for (auto& [name, grade] : grades) {
        cout << name << ": " << grade << endl;
    }
    
    return 0;
}
```

### Simple Custom Implementation

Before diving into collision handling, here's a basic hash table with a simple hash function:

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BasicHashTable {
private:
    static const int TABLE_SIZE = 10;
    vector<string> keys;
    vector<int> values;
    vector<bool> occupied;
    
    // Simple hash function
    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return abs(hash);
    }
    
public:
    BasicHashTable() : keys(TABLE_SIZE), values(TABLE_SIZE), occupied(TABLE_SIZE, false) {}
    
    // Insert
    void insert(const string& key, int value) {
        int index = hashFunction(key);
        keys[index] = key;
        values[index] = value;
        occupied[index] = true;
    }
    
    // Search
    bool search(const string& key, int& value) {
        int index = hashFunction(key);
        if (occupied[index] && keys[index] == key) {
            value = values[index];
            return true;
        }
        return false;
    }
    
    // Display
    void display() {
        cout << "Hash Table Contents:" << endl;
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (occupied[i]) {
                cout << "Index " << i << ": [" << keys[i] << " -> " << values[i] << "]" << endl;
            }
        }
    }
};

int main() {
    BasicHashTable ht;
    
    ht.insert("apple", 1);
    ht.insert("banana", 2);
    ht.insert("cherry", 3);
    
    ht.display();
    
    int value;
    if (ht.search("apple", value)) {
        cout << "Found apple: " << value << endl;
    }
    
    return 0;
}
```

**Note**: This simple implementation doesn't handle collisions well. In the next section, we'll explore proper collision handling techniques.

## Collision Handling Techniques

When two different keys hash to the same index, we have a collision. Different strategies resolve this with various trade-offs.

### 1. Chaining (Separate Chaining)

**Concept**: Each bucket stores a linked list (or other data structure) of all key-value pairs that hash to that index.

**Advantages**:
- Simple to implement
- Removal is easy
- Load factor can exceed 1.0
- Graceful degradation as load factor increases

**Disadvantages**:
- Extra memory for pointers
- Cache performance is poor (linked lists scattered in memory)

**Visualization**:
```
Index 0: apple → banana → cherry
Index 1: [empty]
Index 2: dog → zebra
Index 3: elephant
```

**C++ Implementation with Chaining**:
```cpp
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class ChainingHashTable {
private:
    static const int TABLE_SIZE = 10;
    vector<list<pair<string, int>>> table;
    
    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return abs(hash);
    }
    
public:
    ChainingHashTable() : table(TABLE_SIZE) {}
    
    // Insert
    void insert(const string& key, int value) {
        int index = hashFunction(key);
        
        // Check if key already exists
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;  // Update
                return;
            }
        }
        
        // Add new entry
        table[index].push_back({key, value});
    }
    
    // Search
    bool search(const string& key, int& value) {
        int index = hashFunction(key);
        
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                value = pair.second;
                return true;
            }
        }
        return false;
    }
    
    // Remove
    bool remove(const string& key) {
        int index = hashFunction(key);
        
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                return true;
            }
        }
        return false;
    }
    
    // Display
    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Index " << i << ": ";
            for (auto& pair : table[i]) {
                cout << "[" << pair.first << ":" << pair.second << "] ";
            }
            cout << endl;
        }
    }
};

int main() {
    ChainingHashTable ht;
    
    // Insert elements that may collide
    ht.insert("apple", 1);
    ht.insert("banana", 2);
    ht.insert("cherry", 3);
    ht.insert("date", 4);
    
    ht.display();
    
    int value;
    if (ht.search("banana", value)) {
        cout << "\nFound banana: " << value << endl;
    }
    
    ht.remove("cherry");
    cout << "\nAfter removing cherry:" << endl;
    ht.display();
    
    return 0;
}
```

### 2. Linear Probing (Open Addressing)

**Concept**: When a collision occurs, probe the next available slot sequentially.

**Formula**: `probeIndex = (hash(key) + i) % TABLE_SIZE` where i = 0, 1, 2, ...

**Advantages**:
- Better cache locality (data is contiguous)
- No extra memory for pointers
- Simple implementation

**Disadvantages**:
- Clustering problem (collisions tend to form clusters)
- Load factor must stay < 1.0
- Deletion is complex (need tombstones)

**Visualization**:
```
Initial hash positions: [2, 2, 5, 5]
After linear probing:
Index 2: apple
Index 3: banana (probed from 2)
Index 5: cherry
Index 6: date (probed from 5)
```

**C++ Implementation**:
```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class LinearProbingHashTable {
private:
    static const int TABLE_SIZE = 20;
    vector<string> keys;
    vector<int> values;
    vector<bool> occupied;
    
    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return abs(hash);
    }
    
public:
    LinearProbingHashTable() : keys(TABLE_SIZE, ""), values(TABLE_SIZE, -1), occupied(TABLE_SIZE, false) {}
    
    // Insert
    void insert(const string& key, int value) {
        int index = hashFunction(key);
        int probes = 0;
        
        while (occupied[index] && probes < TABLE_SIZE) {
            if (keys[index] == key) {
                values[index] = value;  // Update
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            probes++;
        }
        
        if (probes < TABLE_SIZE) {
            keys[index] = key;
            values[index] = value;
            occupied[index] = true;
        } else {
            cout << "Hash table is full!" << endl;
        }
    }
    
    // Search
    bool search(const string& key, int& value) {
        int index = hashFunction(key);
        int probes = 0;
        
        while (occupied[index] && probes < TABLE_SIZE) {
            if (keys[index] == key) {
                value = values[index];
                return true;
            }
            index = (index + 1) % TABLE_SIZE;
            probes++;
        }
        return false;
    }
    
    // Display
    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (occupied[i]) {
                cout << "Index " << i << ": [" << keys[i] << ":" << values[i] << "]" << endl;
            }
        }
    }
};

int main() {
    LinearProbingHashTable ht;
    
    ht.insert("apple", 1);
    ht.insert("banana", 2);
    ht.insert("cherry", 3);
    ht.insert("date", 4);
    
    ht.display();
    
    int value;
    if (ht.search("banana", value)) {
        cout << "\nFound banana: " << value << endl;
    }
    
    return 0;
}
```

### 3. Quadratic Probing

**Concept**: When a collision occurs, probe using a quadratic formula to avoid clustering.

**Formula**: `probeIndex = (hash(key) + i²) % TABLE_SIZE` where i = 0, 1, 2, ...

**Advantages**:
- Reduces primary clustering compared to linear probing
- Still good cache locality
- No extra memory needed

**Disadvantages**:
- Secondary clustering can still occur
- May not probe all slots
- Complex deletion

**Probe Sequence Example**:
```
Starting at index 5:
i=0: 5
i=1: 5+1 = 6
i=2: 5+4 = 9
i=3: 5+9 = 14
i=4: 5+16 = 21...
```

**C++ Implementation**:
```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class QuadraticProbingHashTable {
private:
    static const int TABLE_SIZE = 20;
    vector<string> keys;
    vector<int> values;
    vector<bool> occupied;
    
    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return abs(hash);
    }
    
public:
    QuadraticProbingHashTable() : keys(TABLE_SIZE, ""), values(TABLE_SIZE, -1), occupied(TABLE_SIZE, false) {}
    
    // Insert
    void insert(const string& key, int value) {
        int hash = hashFunction(key);
        int probes = 0;
        
        while (probes < TABLE_SIZE) {
            int index = (hash + probes * probes) % TABLE_SIZE;
            
            if (!occupied[index]) {
                keys[index] = key;
                values[index] = value;
                occupied[index] = true;
                return;
            } else if (keys[index] == key) {
                values[index] = value;  // Update
                return;
            }
            probes++;
        }
        
        cout << "Hash table is full!" << endl;
    }
    
    // Search
    bool search(const string& key, int& value) {
        int hash = hashFunction(key);
        int probes = 0;
        
        while (probes < TABLE_SIZE) {
            int index = (hash + probes * probes) % TABLE_SIZE;
            
            if (!occupied[index]) {
                return false;
            } else if (keys[index] == key) {
                value = values[index];
                return true;
            }
            probes++;
        }
        return false;
    }
    
    // Display
    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (occupied[i]) {
                cout << "Index " << i << ": [" << keys[i] << ":" << values[i] << "]" << endl;
            }
        }
    }
};

int main() {
    QuadraticProbingHashTable ht;
    
    ht.insert("apple", 1);
    ht.insert("banana", 2);
    ht.insert("cherry", 3);
    ht.insert("dog", 4);
    
    ht.display();
    
    int value;
    if (ht.search("dog", value)) {
        cout << "\nFound dog: " << value << endl;
    }
    
    return 0;
}
```

### 4. Double Hashing

**Concept**: Use two hash functions. If collision occurs, use the second hash function to determine the probe step size.

**Formula**: `probeIndex = (hash1(key) + i * hash2(key)) % TABLE_SIZE` where i = 0, 1, 2, ...

**Advantages**:
- Virtually eliminates clustering
- Good uniform distribution
- Only two hash function computations needed

**Disadvantages**:
- More complex to implement
- Need to ensure hash2(key) ≠ 0
- Still requires load factor < 1.0

**C++ Implementation**:
```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class DoubleHashingHashTable {
private:
    static const int TABLE_SIZE = 23;  // Prime number
    vector<string> keys;
    vector<int> values;
    vector<bool> occupied;
    
    int hashFunction1(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return abs(hash);
    }
    
    int hashFunction2(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 17 + c) % (TABLE_SIZE - 1);
        }
        return abs(hash) + 1;  // Ensure non-zero
    }
    
public:
    DoubleHashingHashTable() : keys(TABLE_SIZE, ""), values(TABLE_SIZE, -1), occupied(TABLE_SIZE, false) {}
    
    // Insert
    void insert(const string& key, int value) {
        int hash1 = hashFunction1(key);
        int hash2 = hashFunction2(key);
        int probes = 0;
        
        while (probes < TABLE_SIZE) {
            int index = (hash1 + probes * hash2) % TABLE_SIZE;
            
            if (!occupied[index]) {
                keys[index] = key;
                values[index] = value;
                occupied[index] = true;
                return;
            } else if (keys[index] == key) {
                values[index] = value;  // Update
                return;
            }
            probes++;
        }
        
        cout << "Hash table is full!" << endl;
    }
    
    // Search
    bool search(const string& key, int& value) {
        int hash1 = hashFunction1(key);
        int hash2 = hashFunction2(key);
        int probes = 0;
        
        while (probes < TABLE_SIZE) {
            int index = (hash1 + probes * hash2) % TABLE_SIZE;
            
            if (!occupied[index]) {
                return false;
            } else if (keys[index] == key) {
                value = values[index];
                return true;
            }
            probes++;
        }
        return false;
    }
    
    // Display
    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (occupied[i]) {
                cout << "Index " << i << ": [" << keys[i] << ":" << values[i] << "]" << endl;
            }
        }
    }
};

int main() {
    DoubleHashingHashTable ht;
    
    ht.insert("apple", 1);
    ht.insert("banana", 2);
    ht.insert("cherry", 3);
    ht.insert("dog", 4);
    ht.insert("elephant", 5);
    
    ht.display();
    
    int value;
    if (ht.search("elephant", value)) {
        cout << "\nFound elephant: " << value << endl;
    }
    
    return 0;
}
```

### Collision Handling Comparison

| Technique | Avg Lookup | Space | Clustering | Deletion | Cache |
|-----------|-----------|-------|-----------|----------|-------|
| Chaining | O(1+α) | O(n+m) | None | Easy | Poor |
| Linear Probing | O(1/(1-α)) | O(n) | Severe | Hard | Good |
| Quadratic Probing | O(1/(1-α)) | O(n) | Moderate | Hard | Good |
| Double Hashing | O(1/(1-α)) | O(n) | Minimal | Hard | Good |

*Note: α = load factor = n/m (entries/buckets)*

## Common Operations

### Creating and Initializing

```cpp
// C++17 and later - with initialization list
unordered_map<string, int> map1 = {
    {"key1", 1},
    {"key2", 2}
};
```

### Inserting

```cpp
// Method 1: Using operator[]
map["key"] = value;

// Method 2: Using insert()
map.insert({"key", value});

// Method 3: Using emplace()
map.emplace("key", value);
```

### Accessing

```cpp
// Safe access with find()
if (map.find(key) != map.end()) {
    int value = map[key];
}

// Unsafe access with operator[] (creates entry if not found)
int value = map[key];
```

### Updating

```cpp
map["existing_key"] = new_value;
```

### Deleting

```cpp
map.erase("key");  // Erase by key
map.erase(iterator);  // Erase by iterator
map.clear();  // Clear all entries
```

### Iteration

```cpp
// Range-based for loop
for (auto& [key, value] : map) {
    cout << key << " -> " << value << endl;
}

// Iterator-based
for (auto it = map.begin(); it != map.end(); ++it) {
    cout << it->first << " -> " << it->second << endl;
}
```

## Use Cases

### 1. Counting Occurrences
```cpp
unordered_map<int, int> count;
vector<int> nums = {1, 2, 2, 3, 3, 3};

for (int num : nums) {
    count[num]++;
}
```

### 2. Two Sum Problem
```cpp
bool twoSum(vector<int>& nums, int target) {
    unordered_set<int> seen;
    
    for (int num : nums) {
        if (seen.find(target - num) != seen.end()) {
            return true;
        }
        seen.insert(num);
    }
    return false;
}
```

### 3. Anagram Detection
```cpp
bool isAnagram(const string& s1, const string& s2) {
    if (s1.length() != s2.length()) return false;
    
    unordered_map<char, int> freq;
    for (char c : s1) freq[c]++;
    
    for (char c : s2) {
        if (freq[c] == 0) return false;
        freq[c]--;
    }
    return true;
}
```

### 4. Cache Implementation
```cpp
class LRUCache {
private:
    unordered_map<int, int> cache;
    int capacity;
    
public:
    LRUCache(int cap) : capacity(cap) {}
    
    int get(int key) {
        return cache.find(key) != cache.end() ? cache[key] : -1;
    }
    
    void put(int key, int value) {
        cache[key] = value;
        if (cache.size() > capacity) {
            cache.erase(cache.begin());  // Simplified eviction
        }
    }
};
```

## Complexity Analysis

### Time Complexity (Average Case)

| Operation | Average | Worst Case |
|-----------|---------|------------|
| Insert    | O(1)    | O(n)       |
| Search    | O(1)    | O(n)       |
| Delete    | O(1)    | O(n)       |

- **Average case**: Assumes uniform distribution of hash values and good load factor
- **Worst case**: When many collisions occur (poor hash function or high load factor)

### Space Complexity

| Metric           | Complexity |
|------------------|------------|
| Storage          | O(n)       |
| Hash Table Size  | O(n + m)   |

Where `n` is the number of entries and `m` is the number of buckets.

## Best Practices

### 1. Choose the Right Container
```cpp
// Use unordered_map when you need average O(1) lookup
unordered_map<string, int> fast;

// Use map when you need sorted order
map<string, int> sorted;
```

### 2. Check Before Accessing
```cpp
// Good practice
if (map.find(key) != map.end()) {
    int value = map[key];
}

// Avoid - creates entry if not found
int value = map[key];  // Dangerous!
```

### 3. Use Count for Existence
```cpp
if (map.count(key)) {
    // Key exists
}
```

### 4. Use at() for Exception Safety
```cpp
try {
    int value = map.at(key);  // Throws out_of_range if not found
} catch (const out_of_range& e) {
    cout << "Key not found" << endl;
}
```

### 5. Reserve Space When Possible
```cpp
unordered_map<string, int> map;
map.reserve(1000);  // Reserve space for ~1000 entries
```

### 6. Avoid Frequent Rehashing
```cpp
// Create with appropriate size
unordered_map<int, int> map(1000);  // Initial bucket count
```

### 7. Choose Hash Function Wisely
```cpp
// Custom hash function for custom types
struct CustomHash {
    size_t operator()(const string& s) const {
        hash<string> hasher;
        return hasher(s);
    }
};

unordered_map<string, int, CustomHash> map;
```

## Key Takeaways

- **Hash tables** provide fast average O(1) lookup, insertion, and deletion
- **Basic usage**: Use `std::unordered_map` for most scenarios
- **Collision resolution** is critical for maintaining performance:
  - **Chaining**: Simple, good for high load factors
  - **Linear Probing**: Good cache locality, but suffers from clustering
  - **Quadratic Probing**: Better than linear probing
  - **Double Hashing**: Best collision distribution
- **Load factor** affects performance—rehash when it gets too high
- **Hash function quality** directly impacts performance
- **Unordered maps** are preferred when order doesn't matter
- **Regular maps** should be used when you need sorted order
- Always **check for key existence** before accessing to avoid bugs

---

**References:**
- C++ Standard Library: https://en.cppreference.com/w/cpp/container
- Hash Table Wikipedia: https://en.wikipedia.org/wiki/Hash_table
- Collision Resolution: https://en.wikipedia.org/wiki/Hash_table#Collision_resolution

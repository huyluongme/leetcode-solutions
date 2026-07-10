/*
 * Problem    : 155. Min Stack
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : July 10, 2026
 * Language   : C++
 * Difficulty : Medium
 * Tags       : Stack, Design
 * Link       : https://leetcode.com/problems/min-stack
 *
 * Time       : O(1)
 * Space      : O(n)
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class MinStack {
private:
    stack<pair<int, int>> s;
public:
    MinStack() {

    }
    
    void push(int value) {
        int current_min = s.empty() ? value : s.top().second;
        if (value < current_min)
            current_min = value;
        s.push({value, current_min});
    }
    
    void pop() {
        s.pop();
    }
    
    int top() {
        return s.top().first;
    }
    
    int getMin() {
        return s.top().second;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

int main()
{
    MinStack* obj = new MinStack();
    obj->push(3);
    obj->push(5);
    obj->push(2);
    obj->push(1);
    
    cout << "Top: " << obj->top() << endl;
    cout << "Min: " << obj->getMin() << endl;
    
    obj->pop();
    
    cout << "Top: " << obj->top() << endl;
    cout << "Min: " << obj->getMin() << endl;
    
    delete obj;
    
    return 0;
}

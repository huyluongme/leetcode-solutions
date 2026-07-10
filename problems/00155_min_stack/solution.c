/*
 * Problem    : 155. Min Stack
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : July 10, 2026
 * Language   : C
 * Difficulty : Medium
 * Tags       : Stack, Design
 * Link       : https://leetcode.com/problems/min-stack
 *
 * Time       : O(1)
 * Space      : O(n)
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
    int value;
    int min;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} MinStack;

MinStack* minStackCreate() {
    MinStack* minStack = (MinStack*)malloc(sizeof(MinStack));
    minStack->top = NULL;
    return minStack;
}

void minStackPush(MinStack* obj, int value) {
    StackNode* stackNode = (StackNode*)malloc(sizeof(StackNode));
    stackNode->value = value;

    if (obj->top == NULL) {
        stackNode->min = value;
    } else {
        stackNode->min = (value < obj->top->min) ? value : obj->top->min;
    }

    stackNode->next = obj->top;
    obj->top = stackNode;
}

void minStackPop(MinStack* obj) {
    StackNode* stackNode = obj->top;
    obj->top = obj->top->next;
    free(stackNode);
}

int minStackTop(MinStack* obj) {
    return obj->top->value;
}

int minStackGetMin(MinStack* obj) {
    return obj->top->min;
}

void minStackFree(MinStack* obj) {
    while (obj->top != NULL) {
        StackNode* temp = obj->top;
        obj->top = obj->top->next;
        free(temp);
    }
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, value);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/

int main()
{
    MinStack* minStack = minStackCreate();

    minStackPush(minStack, 3);
    minStackPush(minStack, 5);
    minStackPush(minStack, 2);
    minStackPush(minStack, 1);
    
    printf("Top: %d\n", minStackTop(minStack));
    printf("Min: %d\n", minStackGetMin(minStack));
    
    minStackPop(minStack);
    
    printf("Top: %d\n", minStackTop(minStack));
    printf("Min: %d\n", minStackGetMin(minStack));
    
    minStackFree(minStack);

    return 0;
}

/*
 * Problem    : 20. Valid Parentheses
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : May 1, 2026
 * Language   : C
 * Difficulty : Easy
 * Tags       : String, Stack
 * Link       : https://leetcode.com/problems/valid-parentheses
 *
 * Time       : O(n)
 * Space      : O(n)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char* data;
    int top;
    int max_size;
} Stack;

bool isEmpty(Stack* s) {
    return s->top == -1;
}

char pop(Stack* s) {
    return s->data[s->top--];
}

void push(Stack* s, char c) {
    s->data[++(s->top)] = c;
}

bool isValid(char* s) {
    int size = strlen(s);
    Stack* stack = malloc(sizeof(Stack));

    stack->max_size = size;
    stack->top = -1;
    stack->data = malloc(size * sizeof(char));

    if (stack == NULL)
        return false;

    for (int i = 0; i < size; ++i) {
        char c = s[i];

        if (c == '(' || c == '{' || c == '[')
            push(stack, c);
        else {
            if (isEmpty(stack))
                return false;

            char top = pop(stack);

            if (c == ')' && top != '(')
                return false;

            if (c == '}' && top != '{')
                return false;

            if (c == ']' && top != '[')
                return false;
        }
    }

    return isEmpty(stack);
}

int main()
{
    char s[] = "()[]{}";

    printf("%d\n", isValid(s));

    char s2[] = "(]";
    printf("%d\n", isValid(s2));

    char s3[] = "([)]";
    printf("%d\n", isValid(s3));

    char s4[] = "{[]}";
    printf("%d\n", isValid(s4));

    char s5[] = "(((((";
    printf("%d\n", isValid(s5));

    return 0;
}

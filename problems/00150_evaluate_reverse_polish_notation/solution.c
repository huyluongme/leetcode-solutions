/*
 * Problem    : 150. Evaluate Reverse Polish Notation
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : July 11, 2026
 * Language   : C
 * Difficulty : Medium
 * Tags       : Array, Math, Stack
 * Link       : https://leetcode.com/problems/evaluate-reverse-polish-notation
 *
 * Time       : O(n)
 * Space      : O(n)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int evalRPN(char** tokens, int tokensSize)
{
    int* stack = (int*)malloc(sizeof(int) * tokensSize);

    int top = -1;

    for (int i = 0; i < tokensSize; i++) {
        char* token = tokens[i];
        if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0
            || strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
            int op2 = stack[top--];
            int op1 = stack[top--];
            if (strcmp(token, "+") == 0) {
                stack[++top] = op1 + op2;
            } else if (strcmp(token, "-") == 0) {
                stack[++top] = op1 - op2;
            } else if (strcmp(token, "*") == 0) {
                stack[++top] = op1 * op2;
            } else if (strcmp(token, "/") == 0) {
                stack[++top] = op1 / op2;
            }
        } else {
            stack[++top] = atoi(token);
        }
    }

    return stack[top];
}

int main()
{
    char *token1 = "4", *token2 = "3", *token3 = "-", *token4 = "3", *token5 = "*", *token6 = "/", *token7 = "17", *token8 = "5", *token9 = "+", *token10 = "*", *token11 = "4", *token12 = "+";
    char* tokens[] = {token1, token2, token3, token4, token5, token6, token7, token8, token9, token10, token11, token12};
    int tokensSize = 12;
    printf("%d\n", evalRPN(tokens, tokensSize));

    return 0;
}

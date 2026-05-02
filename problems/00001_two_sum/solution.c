/*
 * Problem    : 1. Two Sum
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : May 1, 2026
 * Language   : C
 * Difficulty : Easy
 * Tags       : Junior, Array, Hash Table
 * Link       : https://leetcode.com/problems/two-sum
 *
 * Time       : O(n)
 * Space      : O(n)
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int index;
    struct Node* next;
} Node;

int hashFunc(int key, int numsSize) {
    long long h = (long long)key % numsSize;

    if (h < 0)
        h += numsSize;

    return (int)h;
}

void insert(Node** table, int key, int key_index, int numsSize) {
    int bucket = hashFunc(key, numsSize);

    Node* newNode = malloc(sizeof(Node));
    newNode->key = key;
    newNode->index = key_index;
    newNode->next = table[bucket];
    table[bucket] = newNode;
}

int find(Node** table, int key, int numsSize) {
    int bucket = hashFunc(key, numsSize);

    Node* cur = table[bucket];

    while (cur) {
        if (cur->key == key)
            return cur->index;

        cur = cur->next;
    }
    
    return -1;
}

void freeTable(Node** table, int numsSize) {
    for (int i = 0; i < numsSize; ++i) {
        Node* cur = table[i];

        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }

    free(table);
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    Node** table = calloc(numsSize, sizeof(Node*));
    int* res = malloc(sizeof(int) * 2);

    *returnSize = 0;
    insert(table, nums[0], 0, numsSize);

    for (int i = 1; i < numsSize; ++i) {
        int complement = target - nums[i];
        int index = find(table, complement, numsSize);

        if (index > -1) {
            res[0] = i;
            res[1] = index;
            *returnSize = 2;
            break;
        }

        insert(table, nums[i], i, numsSize);
    }

    freeTable(table, numsSize);
    return res;
}

int main()
{
    int nums[] = {-500000000,2,4,-500000000};
    int numsSize = sizeof(nums)/sizeof(nums[0]);
    int target = -1000000000;
    int returnSize;
    int* res;

    
    res = twoSum(nums, numsSize, target, &returnSize);

    printf("[%d, %d]\n", res[0], res[1]);

    return 0;
}


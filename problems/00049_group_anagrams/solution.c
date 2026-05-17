/*
 * Problem    : 49. Group Anagrams
 * Author     : Huy Luong <huyluongme.cs@gmail.com>
 * Created    : May 17, 2026
 * Language   : C
 * Difficulty : Medium
 * Tags       : Array, Hash Table, String, Sorting
 * Link       : https://leetcode.com/problems/group-anagrams
 *
 * Time       : Average O(N * K), Worst O(N^2 * K) due to hash collisions/realloc
 * Space      : O(N + H), where H = HASH_SIZE
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASH_SIZE 10007

typedef struct Node {
    char* key;
    char** anagrams_group;
    int size;
    struct Node* next;
} Node;

Node* createNode(char* key, char* str) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->size = 1;
    newNode->anagrams_group = (char**)malloc(sizeof(char*));
    newNode->anagrams_group[0] = str;
    newNode->next = NULL;

    return newNode;
}

void addNode(Node* node, char* str) {
    node->size++;
    node->anagrams_group = (char**)realloc(node->anagrams_group, node->size * sizeof(char*));
    node->anagrams_group[node->size - 1] = str;
}

unsigned long djb2Hash(const char* str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

char* generateKey(char* str) {
    int cnt[26] = {0};
    int len = strlen(str);
    int i;

    if (len == 0) {
        char* key = (char*)malloc(sizeof(char));
        key[0] = '\0';
        return key;
    }

    for (i = 0; i < len; ++i)
        cnt[str[i] - 'a']++;

    char* key = (char*)malloc(200);
    int offset = 0;
    for (i = 0; i < 26; ++i)
        if (cnt[i])
            offset += sprintf(key + offset, "%c%d", i + 'a', cnt[i]);

    key[offset] = '\0';

    return key;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    Node* hashTable[HASH_SIZE] = {0};
    int tableSize = 0;

    for (int i = 0; i < strsSize; ++i) {
        char* key = generateKey(strs[i]);
        unsigned int id = djb2Hash(key) % HASH_SIZE;
        Node* node = hashTable[id];

        while (node && strcmp(node->key, key) != 0)
            node = node->next;

        if (!node) {
            node = createNode(key, strs[i]);
            node->next = hashTable[id];
            hashTable[id] = node;
            tableSize++;
        }
        else {
            addNode(node, strs[i]);
            free(key);
        }
    }

    char*** res = (char***)malloc(tableSize * sizeof(char**));
    *returnColumnSizes = (int*)malloc(tableSize * sizeof(int));
    int j = 0;

    for (int i = 0; i < HASH_SIZE; ++i) {
        Node* curNode = hashTable[i];

        while (curNode) {
            Node* nextNode = curNode->next;

            res[j] = curNode->anagrams_group;
            (*returnColumnSizes)[j] = curNode->size;
            j++;

            free(curNode->key);
            free(curNode);

            curNode = nextNode;
        }
    }

    *returnSize = tableSize;

    return res;
}

int main()
{
    char* strs[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
    int strsSize = sizeof(strs)/sizeof(strs[0]);
    int returnSize = 0;
    int* returnColumnSizes = NULL;

    char*** res = groupAnagrams(strs, strsSize, &returnSize, &returnColumnSizes);

    printf("[");

    for (int i = 0; i < returnSize; ++i) {
        printf("[");

        for (int j = 0; j < returnColumnSizes[i]; ++j) {
            printf("\"%s\"", res[i][j]);

            if (j < returnColumnSizes[i] - 1) {
                printf(",");
            }

        }

        printf("]");

        if (i < returnSize - 1)
            printf(",");
    }

    printf("]\n");

    for (int i = 0; i < returnSize; ++i)
        free(res[i]);

    free(res);
    free(returnColumnSizes);
    return 0;
}

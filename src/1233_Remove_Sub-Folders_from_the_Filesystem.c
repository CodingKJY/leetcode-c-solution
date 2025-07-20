#define SOLVED 1
#include "leetcode.h"

// 
// Implementation
// 
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MAX_FOLDER_SIZE 40000
int cmp(const void *str1, const void *str2) {
    return strcmp(*(const char **)str1, *(const char **)str2);
}

char** removeSubfolders(char** folder, int folderSize, int* returnSize) {
    qsort(folder, folderSize, sizeof(char *), cmp);

    char **res = malloc(MAX_FOLDER_SIZE * sizeof(char *));
    int size = 0;
    char *root = folder[0];
    int rootSize = strlen(root);

    res[size++] = root;
    for (int i = 1; i < folderSize; i++) {
        if (strncmp(root, folder[i], rootSize) != 0 || folder[i][rootSize] != '/') {
            root = folder[i];
            rootSize = strlen(root);
            res[size++] = root;
        }
    }
    *returnSize = size;
    return res;
}

// 
// Run Test
// 
typedef struct {
    int n;
    char *folder[40000];
} Testcase;

void solution(void) {
    Testcase tests[] = {
        {
            .n = 5,
            .folder = {
                "/a",
                "/a/b",
                "/c/d",
                "/c/d/e",
                "/c/f",
            },
        },
        {
            .n = 3,
            .folder = {"/a","/a/b/c","/a/b/d"},
        },
        {
            .n = 3,
            .folder = {"/a/b/c","/a/b/ca","/a/b/d"},
        },
    };

    for (int i = 0; i < ARRAY_SIZE(tests); i++) {
        char **folder;
        int size;
        folder = removeSubfolders(tests[i].folder, tests[i].n, &size);
        printf("test - %d\n", i);
        for (int j = 0; j < size; j++) {
            printf("%s\n", folder[j]);
        }
        free(folder);
    }
}

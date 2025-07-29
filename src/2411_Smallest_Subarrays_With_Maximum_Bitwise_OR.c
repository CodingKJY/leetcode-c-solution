#define SOLVED 1
#include "leetcode.h"

// 
// Implementation
// 
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* smallestSubarrays(int* nums, int numsSize, int* returnSize) {
    int *res = malloc(numsSize * sizeof(int));
    int last[32] = {0};

    for (int i = numsSize - 1; i >= 0; i--) {
        int farthest = i;
        for (int j = 0; j < 32; j++) {
            if ((nums[i] >> j) & 1)
                last[j] = i;
            else
                farthest = MAX(last[j], farthest);
        }
        res[i] = farthest - i + 1;
    }

    *returnSize = numsSize;
    return res;
}

// 
// Run Test
// 
typedef struct {
    int nums[100000];
    int numsSize;
} Testcase;

void solution(void) {
    Testcase tests[] = {
        {.nums = {1,0,2,1,3}, .numsSize = 5},  // {3,3,2,2,1}
        {.nums = {1,2}, .numsSize = 2},        // {2,1}
        {.nums = {50,127,0,23,12,37,6}, .numsSize = 7}, // {2,1,4,3,3,2,1}
        {.nums = {7}, .numsSize = 1}, // {1}
        {.nums = {1,0}, .numsSize = 2},  // {1,1}
    };

    for (int i = 0; i < ARRAY_SIZE(tests); i++) {
        int returnSize = 0;
        int *res = smallestSubarrays(tests[i].nums, tests[i].numsSize, &returnSize);
        for (int j = 0; j < returnSize; j++) {
            printf("%d ", res[j]);
        }
        printf("\n");
        if (res) {
            free(res);
        }
    }
}

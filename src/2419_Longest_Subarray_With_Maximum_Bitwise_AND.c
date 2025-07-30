#define SOLVED 1
#include "leetcode.h"

// 
// Implementation
// 
int longestSubarray(int* nums, int numsSize) {
    int result = 0;
    int count = 0;
    int max = 0;
    for (int i = 0; i < numsSize; i++) {
        if (max < nums[i]) {
            max = nums[i];
            result = count = 1;
        }
        else if (max == nums[i]) {
            count++;
        }
        else {
            result = MAX(count, result);
            count = 0;
        }
    }
    return MAX(count, result);
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
        {.nums = {1,2,3,3,2,2}, .numsSize = 6},  // 2
        {.nums = {1,2,3,4}, .numsSize = 4},      // 1
        {.nums = {4,1,2,3,4}, .numsSize = 1},    // 1
        {.nums = {311155,311155,311155,311155,311155,311155,311155,311155,201191,311155}, .numsSize = 10}, // 8
        {.nums = {378034,378034,378034}, .numsSize = 3}, // 3
        {.nums = {96317,96317,96317,96317,96317,96317,96317,96317,96317,279979}, .numsSize = 10}, // 1
    };

    for (int i = 0; i < ARRAY_SIZE(tests); i++) {
        printf("%d\n", longestSubarray(tests[i].nums, tests[i].numsSize));
    }
}

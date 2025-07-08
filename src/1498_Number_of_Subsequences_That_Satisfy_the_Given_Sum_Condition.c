#include "leetcode.h"

// 
// Implementation
// 
int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int numSubseq(int* nums, int numsSize, int target) {
    int counts = 0;
    int min_idx = 0;
    int max_idx = numsSize - 1;
    int MOD = 1000000007;

    // precompute powers
    int pow2[numsSize + 1];
    pow2[0] = 1;
    for (int i = 1; i <= numsSize; i++) {
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    }

    // sort array
    qsort(nums, numsSize, sizeof(int), cmp);
    
    while (max_idx >= min_idx) {
        if (nums[min_idx] * 2 > target) {
            break;
        }
        else if (nums[min_idx] + nums[max_idx] <= target) {
            counts = (counts + pow2[max_idx - min_idx]) % MOD;
            min_idx++;
        }
        else {
            max_idx--;
        }
    }
    
    return counts;
}

// 
// Run Test
// 
typedef struct {
    int nums[100000];
    int size;
    int target;
} Testcase;

void solution(void) {
    Testcase tests[] = {
        {.nums = {3,5,6,7}, .size = 4, .target = 9},
        {.nums = {3,3,6,8}, .size = 4, .target = 10},
        {.nums = {2,3,3,4,6,7}, .size = 4, .target = 12},
    };

    for (int i = 0; i < sizeof(tests)/sizeof(Testcase); i++) {
        printf("%d\n", numSubseq(tests[i].nums, tests[i].size, tests[i].target));
    }
}

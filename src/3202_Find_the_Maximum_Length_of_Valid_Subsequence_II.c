#define SOLVED 1
#include "leetcode.h"

// Hint 1
//      Fix the value of (subs[0] + subs[1]) % k from the k possible values. Let it be val.
// Hint 2
//      Let dp[i] store the maximum length of a subsequence with its last element x such that x % k == i.
// Hint 3
//      Answer for a subsequence ending at index y is dp[(k + val - (y % k)) % k] + 1.

// 
// Implementation
// 
int maximumLength(int* nums, int numsSize, int k) {
    int max = 0;

    for (int val = 0; val < k; val++) {
        int dp[k];
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < numsSize; i++) {
            int ri = nums[i] % k;
            int rj = (k + val - ri) % k;

            dp[ri] = MAX(dp[ri], dp[rj] + 1);
            max = MAX(max, dp[ri]);
        }
    }
    return max;
}

// 
// Run Test
// 
typedef struct {
    int k;
    int size;
    int nums[1000];
} Testcase;

void solution(void) {
    Testcase tests[] = {
        {.k = 2, .size = 5, .nums = {1,2,3,4,5}},   // 5
        {.k = 3, .size = 6, .nums = {1,4,2,3,1,4}}, // 4
    };

    for (int i = 0; i < ARRAY_SIZE(tests); i++) {
        printf("%d\n", maximumLength(tests[i].nums, tests[i].size, tests[i].k));
    }
}

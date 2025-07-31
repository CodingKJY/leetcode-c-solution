#define SOLVED 0
#include "leetcode.h"

// 
// Implementation
// 
int subarrayBitwiseORs(int* arr, int arrSize) {
    int subArrNum = 0;


    
    return subArrNum;
}

// 
// Run Test
// 
typedef struct {
    int arr[50000];
    int arrSize;
} Testcase;

void solution(void) {
    Testcase tests[] = {
        {.arr = {0}, .arrSize = 1},      // 1
        {.arr = {1,1,2}, .arrSize = 3},  // 3
        {.arr = {1,2,4}, .arrSize = 3},  // 6
    };

    for (int i = 0; i < ARRAY_SIZE(tests); i++) {
        printf("%d\n", subarrayBitwiseORs(tests[i].arr, tests[i].arrSize));
    }
}

#define SOLVED 0
#include "leetcode.h"

// 
// Implementation
// 
int maxFreeTime(int eventTime, int* startTime, int startTimeSize, int* endTime, int endTimeSize) {
    int maxFreeTime = 0;
    int left_gap, main_gap, right_gap;
    int _left_gap, _main_gap, _right_gap;
    int size = startTimeSize;

    left_gap = startTime[0];
    main_gap = startTime[1] - endTime[0];
    right_gap = size == 2 ? eventTime - endTime[size - 1] : startTime[2] - endTime[1];
    for (int i = 2; i < size; i += 2) {
        
    }

    return maxFreeTime;
}

// 
// Run Test
// 
typedef struct {
    int eventTime;
    int eventSize;
    int startTime[100000];
    int endTime[100000];
} Testcase;

void solution(void) {
    Testcase tests[] = {
        {  // 2
            .eventTime = 5,
            .eventSize = 2,
            .startTime = {1,3},
            .endTime   = {2,5},
        },
        {  // 7
            .eventTime = 10,
            .eventSize = 3,
            .startTime = {0,7,9},
            .endTime   = {1,8,10},
        },
        {  // 6
            .eventTime = 10,
            .eventSize = 4,
            .startTime = {0,3,7,9},
            .endTime   = {1,4,8,10},
        },
        {  // 0
            .eventTime = 5,
            .eventSize = 5,
            .startTime = {0,1,2,3,4},
            .endTime   = {1,2,3,4,5},
        },
    };

    for (int i = 0; i < ARRAY_SIZE(tests); i++) {
        printf("%d\n", maxFreeTime(tests[i].eventTime, tests[i].startTime, tests[i].eventSize, tests[i].endTime, tests[i].eventSize));
    }
}

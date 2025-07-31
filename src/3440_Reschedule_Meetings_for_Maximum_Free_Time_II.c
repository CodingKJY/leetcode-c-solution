#define SOLVED 1
#include "leetcode.h"

// 
// Implementation
// 
int maxFreeTime(int eventTime, int* startTime, int startTimeSize, int* endTime, int endTimeSize) {
    int maxFreeTime = 0;
    int size = startTimeSize;
    int gaps[size + 1];

    gaps[0] = startTime[0];
    gaps[size] = eventTime - endTime[size - 1];
    for (int i = 1; i < size; i++) {
        gaps[i] = startTime[i] - endTime[i - 1];
    }

    int prefixMax[size + 1];
    prefixMax[0] = gaps[0];
    for (int i = 1; i < size + 1; i++) {
        prefixMax[i] = MAX(gaps[i], prefixMax[i - 1]);
    }

    int suffixMax[size + 1];
    suffixMax[size] = gaps[size];
    for (int i = size - 1; i >= 0; i--) {
        suffixMax[i] = MAX(gaps[i], suffixMax[i + 1]);
    }

    int meetingTime;
    int freeTime;
    // try left bound
    meetingTime = endTime[0] - startTime[0];
    freeTime = suffixMax[2] >= meetingTime ? gaps[0] + gaps[1] + meetingTime : gaps[0] + gaps[1];
    maxFreeTime = MAX(maxFreeTime, freeTime);

    // try right bound
    meetingTime = endTime[size - 1] - startTime[size - 1];
    freeTime = prefixMax[size - 2] >= meetingTime ? gaps[size - 1] + gaps[size] + meetingTime : gaps[size - 1] + gaps[size];
    maxFreeTime = MAX(maxFreeTime, freeTime);

    // try internal
    for (int i = 1; i < size - 1; i++) {
        meetingTime = endTime[i] - startTime[i];
        if (suffixMax[i + 2] >= meetingTime || prefixMax[i - 1] >= meetingTime)
            freeTime = gaps[i] + gaps[i + 1] + meetingTime;
        else
            freeTime = gaps[i] + gaps[i + 1];
        maxFreeTime = MAX(maxFreeTime, freeTime);
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
        {  // 81
            .eventTime = 178,
            .eventSize = 4,
            .startTime = {3,20,98,118},
            .endTime   = {17,39,111,141},
        },
        {  // 21
            .eventTime = 62,
            .eventSize = 3,
            .startTime = {14,21,40},
            .endTime   = {16,36,59},
        },
        {  // 23
            .eventTime = 59,
            .eventSize = 5,
            .startTime = {6,21,34,50,56},
            .endTime   = {11,25,50,56,59},
        },
    };

    for (int i = 0; i < ARRAY_SIZE(tests); i++) {
        printf("%d\n", maxFreeTime(tests[i].eventTime, tests[i].startTime, tests[i].eventSize, tests[i].endTime, tests[i].eventSize));
    }
}

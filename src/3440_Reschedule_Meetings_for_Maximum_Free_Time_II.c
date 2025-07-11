#define SOLVED 0
#include "leetcode.h"

// 
// Implementation
// 
int maxFreeTime(int eventTime, int* startTime, int startTimeSize, int* endTime, int endTimeSize) {
    return 0;
}

// 
// Run Test
// 
typedef struct {
    int start;
    int end;
} Event;
#define EVENT(start, end) (Event){start,end}
#define MAX_EVENTS 100000

typedef struct {
    int eventTime;
    int n;
    Event events[MAX_EVENTS];
} Events_Series;

typedef struct {
    int eventTime;
    int n;
    int *startTime;
    int *endTime;
} Testcase;

void solution(void) {
    Events_Series series[] = {
        {  // 2
            .n = 2,
            .events = {
                EVENT(1,2),
                EVENT(3,5),
            },
            .eventTime = 5,
        },
        {  // 7
            .n = 3,
            .events = {
                EVENT(0,1),
                EVENT(7,8),
                EVENT(9,10),
            },
            .eventTime = 10,
        },
        {  // 6
            .n = 4,
            .events = {
                EVENT(0,1),
                EVENT(3,4),
                EVENT(7,8),
                EVENT(9,10),
            },
            .eventTime = 10,
        },
        {  // 0
            .n = 5,
            .events = {
                EVENT(0,1),
                EVENT(1,2),
                EVENT(2,3),
                EVENT(3,4),
                EVENT(4,5),
            },
            .eventTime = 5,
        },
    };

    for (int i = 0; i < ARRAY_SIZE(series); i++) {
        Testcase test;
        test.n = series[i].n;
        test.eventTime = series[i].eventTime;
        test.startTime = malloc(test.n * sizeof(int));
        test.endTime = malloc(test.n * sizeof(int));
        for (int j = 0; j < test.n; j++) {
            test.startTime[j] = series[i].events[j].start;
            test.endTime[j] = series[i].events[j].end;
        }
        printf("%d\n", maxFreeTime(test.eventTime, test.startTime, test.n, test.endTime, test.n));
        if (test.startTime) free(test.startTime);
        if (test.endTime) free(test.endTime);
        test.startTime = NULL;
        test.endTime = NULL;
    }
}

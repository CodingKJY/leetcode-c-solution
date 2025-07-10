#include "leetcode.h"

// 
// Implementation
// 
int maxFreeTime(int eventTime, int k, int* startTime, int startTimeSize, int* endTime, int endTimeSize) {
    int event_idx;
    int gaps_num = 0;
    int max_gaps_num = startTimeSize + 1;
    int gaps[max_gaps_num];
    int max_iter = MIN(k + 1, max_gaps_num);
    int max_free_time = 0;

    for (event_idx = 0; event_idx < startTimeSize + 1 && gaps_num < max_iter; event_idx++) {
        int gap_size;
        if (event_idx == 0) {
            gap_size = startTime[event_idx] - 0;
        }
        else if (event_idx == startTimeSize) {
            gap_size = eventTime - endTime[endTimeSize - 1];
        }
        else {
            gap_size = startTime[event_idx] - endTime[event_idx - 1];
        }
        gaps[gaps_num] = gap_size;
        max_free_time += gaps[gaps_num];
        gaps_num++;
    }

    if (gaps_num == max_gaps_num)
        return max_free_time;

    for (int tmp = max_free_time; event_idx < startTimeSize + 1; event_idx++) {
        int gap_size;
        if (event_idx == startTimeSize) {
            gap_size = eventTime - endTime[endTimeSize - 1];
        }
        else {
            gap_size = startTime[event_idx] - endTime[event_idx - 1];
        }
        if (gaps_num < max_gaps_num) {
            gaps[gaps_num] = gap_size;
            gaps_num++;
        }

        tmp = tmp - gaps[gaps_num - 1 - (k + 1)] + gaps[gaps_num - 1];
        if (tmp > max_free_time) {
            max_free_time = tmp;
        }
    }
    return max_free_time;
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
    int k;
    int n;
    int eventTime;
    Event events[MAX_EVENTS];
} Events_Series;

typedef struct {
    int k;
    int n;
    int eventTime;
    int *startTime;
    int *endTime;
} Testcase;

void solution(void) {
    Events_Series series[] = {
        {  // 7
            .k = 1,
            .n = 2,
            .events = {
                EVENT(0,1),
                EVENT(2,4),
                EVENT(9,10),
            },
            .eventTime = 10,
        },
        {  // 0
            .k = 2,
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
        { // 7
            .k = 1,
            .n = 3,
            .events = {
                EVENT(7,10),
                EVENT(10,14),
                EVENT(16,18),
            },
        }
    };

    for (int i = 0; i < ARRAY_SIZE(series); i++) {
        Testcase test;
        test.k = series[i].k;
        test.n = series[i].n;
        test.eventTime = series[i].eventTime;
        test.startTime = malloc(test.n * sizeof(int));
        test.endTime = malloc(test.n * sizeof(int));
        for (int j = 0; j < test.n; j++) {
            test.startTime[j] = series[i].events[j].start;
            test.endTime[j] = series[i].events[j].end;
        }
        printf("%d\n", maxFreeTime(test.eventTime, test.k, test.startTime, test.n, test.endTime, test.n));
        if (test.startTime) free(test.startTime);
        if (test.endTime) free(test.endTime);
        test.startTime = NULL;
        test.endTime = NULL;
    }
}

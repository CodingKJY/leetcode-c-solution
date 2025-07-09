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
    int eventTime;
    int k;
    int n;
    int *startTime;
    int *endTime;
} Testcase;

void solution(void) {
    Testcase test;
    int events[][2] = {
        // {0,1},
        // {2,4},
        // {9,10},

        // {0,1},
        // {1,2},
        // {2,3},
        // {3,4},
        // {4,5},

        {7,10},
        {10,14},
        {16,18},
    };
    int eventTime[] = {
        // 10,
        // 5,
        21
    };
    int k[] = {
        // 1,
        // 2,
        1
    };

    test.eventTime = eventTime[0];
    test.k = k[0];
    test.n = ARRAY_SIZE(events);
    test.startTime = malloc(test.n * sizeof(int));
    test.endTime = malloc(test.n * sizeof(int));
    for (int i = 0; i < test.n; i++) {
        test.startTime[i] = events[i][0];
        test.endTime[i] = events[i][1];
    }

    printf("%d\n", maxFreeTime(test.eventTime, test.k, test.startTime, test.n, test.endTime, test.n));

    if (test.startTime) free(test.startTime);
    if (test.endTime) free(test.endTime);
}

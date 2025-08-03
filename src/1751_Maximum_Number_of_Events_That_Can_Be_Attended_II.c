#define SOLVED 0
#include "leetcode.h"

// 
// Implementation
// 
typedef struct {
    int start;
    int end;
    int value;
} Sched;

int binary_search(int **events, int left, int right, int k) {
    int idx = -1;

    return idx;
}

int cmp(const void *a, const void *b) {
    int ret = **(int **)a - **(int **)b;
    return ret ? ret : *(*(int **)a + 1) - *(*(int **)b + 1);
}

int maxValue(int** events, int eventsSize, int* eventsColSize, int k) {
    qsort(events, eventsSize, sizeof(int *), cmp);

    // traversal all events
    for (int i = 0; i < eventsSize; i++) {
        // 
    }
}

// 
// Run Test
// 
typedef struct {
    int **events;
    int rsize;
    int csize;
} Testcase;

void solution(void) {
    Testcase tests[] = {
        
    };

    for (int i = 0; i < sizeof(tests)/sizeof(Testcase); i++) {
        
    }
}

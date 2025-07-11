#define SOLVED 0
#include "leetcode.h"

// 
// Implementation
// 
int mostBooked(int n, int** meetings, int meetingsSize, int* meetingsColSize) {
    return 0;
}

// 
// Run Test
// 
typedef struct {
    int start;
    int end;
} Meeting;
#define Meeting(start, end) (Meeting){start,end}
#define MAX_SIZE 100000

typedef struct {
    int n;
    int size;
    Meeting meetings[MAX_SIZE];
} Meetings_Series;

typedef struct {
    int n;
    int meetingsSize;
    int meetingsColSize;
    int **meetings;
} Testcase;

void solution(void) {
    Meetings_Series series[] = {
        {  // 0
            .n = 2,
            .size = 4,
            .meetings = {
                Meeting(0,10),
                Meeting(1,5),
                Meeting(2,7),
                Meeting(3,4),
            },
        },
        {  // 1
            .n = 3,
            .size = 5,
            .meetings = {
                Meeting(1,20),
                Meeting(2,10),
                Meeting(3,5),
                Meeting(4,9),
                Meeting(6,8),
            },
        },
    };

    for (int i = 0; i < ARRAY_SIZE(series); i++) {
        Testcase test;
        test.n = series[i].n;
        test.meetingsSize = series[i].size;
        test.meetingsColSize = 2;
        test.meetings = malloc(test.meetingsSize * sizeof(int *));
        for (int j = 0; j < test.meetingsSize; j++) {
            test.meetings[j] = malloc(test.meetingsColSize * sizeof(int));
            test.meetings[j][0] = series[i].meetings[j].start;
            test.meetings[j][1] = series[i].meetings[j].end;
        }
        printf("%d\n", mostBooked(test.n, test.meetings, test.meetingsSize, &test.meetingsColSize));

        for (int j = 0; j < test.meetingsSize; j++) {
            if (test.meetings[j])
                free(test.meetings[j]);
        }
        if (test.meetings)
            free(test.meetings);
    }
}
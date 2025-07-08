#include "leetcode.h"

// 
// Implementation
// 
int possibleStringCount(char* word) {
    int counts = 1;
    char c = *word;
    while (*(++word)) {
        if (c != *word) {
            c = *word;
        }
        else {
            counts++;
        }
    }
    return counts;
}

// 
// Run Test
// 
typedef struct {
    char *word;
} Testcase;

void solution(void) {
    Testcase tests[] = {
        "aabbccdd",
        "aaaaabbc",
        "abbbcddd",
    };

    for (int i = 0; i < sizeof(tests)/sizeof(Testcase); i++) {
        printf("word = %s counts = %d\n", tests[i].word, possibleStringCount(tests[i].word));
    }
}
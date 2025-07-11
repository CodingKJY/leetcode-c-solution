#define SOLVED 1
#include "leetcode.h"

// 
// Implementation
// 
unsigned int kthNum(int k) {
    unsigned int p = log2(k);
    unsigned int off = k - pow(2, p);
    
    if (off == 0) {
        return p % 26;
    }
    return (kthNum(off) + 1) % 26;
}

char kthCharacter(int k) {
    return kthNum(k) + 97;
}

// 
// Run Test
// 
typedef struct {
    int k;
} Testcase;

void solution(void) {
    Testcase tests[] = {
        1,
        2,
        3,
        8,
        155,
    };

    for (int i = 0; i < sizeof(tests)/sizeof(Testcase); i++) {
        printf("k = %d c = %c\n", tests[i].k, kthCharacter(tests[i].k));
    }
}
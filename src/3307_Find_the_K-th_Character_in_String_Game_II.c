#include "leetcode.h"

// 
// Implementation
// 
char kthNum(long long k, int* operations, int operationsSize) {
    if (k == 1)
        return 0;

    long long p = log2(k);
    long long off = k - pow(2, p);

    if (off == 0 && operations[p-1] == 0)
        return kthNum(p == 1 ? p : (long long)pow(2, p - 1), operations, operationsSize) % 26;
        
    if (off == 0 && operations[p-1] == 1)
        return (kthNum(p == 1 ? p : (long long)pow(2, p - 1), operations, operationsSize) + 1) % 26;
        
    if (off != 0 && operations[p] == 0)
        return kthNum(p == 1 ? p : off, operations, operationsSize) % 26;

    return (kthNum(p == 1 ? p : off, operations, operationsSize) + 1) % 26;
}

char kthCharacter(long long k, int* operations, int operationsSize) {
    return kthNum(k, operations, operationsSize) + 97;
}

// 
// Run Test
// 
typedef struct {
    int k;
} Testcase;

void solution(void) {
    int operations[] = {
        0, 0, 1, 1
    };

    Testcase tests[] = {
        1,
        2,
        3,
        8,
        155,
    };

    for (int i = 0; i < sizeof(tests)/sizeof(Testcase); i++) {
        printf("k = %d c = %c\n", tests[i].k, kthCharacter(tests[i].k, operations, sizeof(operations)/sizeof(int)));
    }
}

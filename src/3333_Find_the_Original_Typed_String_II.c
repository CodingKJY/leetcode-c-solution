#define SOLVED 1
#include "leetcode.h"

// 
// Implementation
// 
#define MOD 1000000007

int getAtMostCount(int *dups, int n, int k) {
    int poly[k + 1];
    int counts;
    
    memset(poly, 0, sizeof(poly));
    poly[0] = 1;
    for (int i = 0; i < n; i++) {
        int tmp[k + 1];
        int sum = 0;
        
        memcpy(tmp, poly, sizeof(poly));
        counts = 0;
        for (int j = 0; j < k + 1; j++) {
            if (j == 0)
                sum = tmp[0];
            else
                sum = (sum + tmp[j]) % MOD;
            if (j > dups[i])
                sum = (sum - tmp[j-dups[i]-1] + MOD) % MOD;
            poly[j] = sum;
            counts = (counts + sum) % MOD;
        }
    }
    return counts;
}

int possibleStringCount(char* word, int k) {
    int dups_max = strlen(word);
    int dups_size = 0;
    int dups[dups_max];
    int dist = 0;
    long long total = 1;
    
    memset(dups, 0, dups_max * sizeof(int));
    while (1) {
        if (*word == '\0')
            break;
        if (word[1] == word[0]) {
            dups[dups_size]++;
        }
        else if (dups[dups_size]) {
            total = (total * (dups[dups_size] + 1)) % MOD;
            dups_size++;
            dist++;
        }
        else {
            dist++;
        }
        word++;
    }

    int at_most = (k <= dist) ? 0 : getAtMostCount(dups, dups_size, k - dist - 1);
    return (total - at_most + MOD) % MOD;
}

// 
// Run Test
// 
typedef struct {
    char *word;
    int k;
} Testcase;

void solution(void) {
    Testcase tests[] = {
        {"aabbccdd", 4},
        {"aabbccdd", 6},
        {"aabbccdd", 8},
    };

    for (int i = 0; i < sizeof(tests)/sizeof(Testcase); i++) {
        printf("word = %s k = %d counts = %d\n", tests[i].word, tests[i].k, possibleStringCount(tests[i].word, tests[i].k));
    }
}
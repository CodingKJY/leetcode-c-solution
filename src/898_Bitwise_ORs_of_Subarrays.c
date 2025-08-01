#define SOLVED 1
#include "leetcode.h"

// 
// Implementation
// 
typedef struct {
    int val;
    UT_hash_handle hh;
} HINT32;

typedef struct {
    HINT32 *elts;
    int counts;
} Set;

void setAdd(Set *set, int val) {
    HINT32 *elt = NULL;
    HASH_FIND(hh, set->elts, &val, sizeof(int), elt);
    if (!elt) {
        elt = malloc(sizeof(HINT32));
        elt->val = val;
        HASH_ADD_KEYPTR(hh, set->elts, &(elt->val), sizeof(int), elt);
        set->counts++;
    }
}

void setFree(Set *set) {
    HINT32 *elt, *tmp;
    HASH_ITER(hh, set->elts, elt, tmp) {
        HASH_DELETE(hh, set->elts, elt);
        free(elt);
    }
}

int subarrayBitwiseORs(int* arr, int arrSize) {
    int counts;
    Set set = {0};
    Set prev = {0};

    for (int i = 0; i < arrSize; i++) {
        Set cur = {0};
        HINT32 *elt, *tmp;
    
        setAdd(&cur, arr[i]);
        HASH_ITER(hh, prev.elts, elt, tmp) {
            int val = arr[i] | elt->val;
            setAdd(&cur, val);
        }

        HASH_ITER(hh, cur.elts, elt, tmp) {
            setAdd(&set, elt->val);
        }

        setFree(&prev);
        prev.elts = cur.elts;
        prev.counts = cur.counts;
    }
    counts = set.counts;
    setFree(&prev);
    setFree(&set);
    return counts;
}

// 
// Run Test
// 
typedef struct {
    int arr[50000];
    int arrSize;
} Testcase;

void solution(void) {
    Testcase tests[] = {
        {.arr = {0}, .arrSize = 1},      // 1
        {.arr = {1,1,2}, .arrSize = 3},  // 3
        {.arr = {1,2,4}, .arrSize = 3},  // 6
    };

    for (int i = 0; i < ARRAY_SIZE(tests); i++) {
        printf("%d\n", subarrayBitwiseORs(tests[i].arr, tests[i].arrSize));
    }
}

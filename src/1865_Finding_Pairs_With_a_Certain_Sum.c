#include "leetcode.h"

// 
// Implementation
// 
typedef struct {
    int val;
    int counts;
    UT_hash_handle hh;
} HashINT;

HashINT *HashINTCreate(int *nums, int size) {
    HashINT *ht = NULL;
    for (int i = 0; i < size; i++) {
        HashINT *num = NULL;
        HASH_FIND_INT(ht, &nums[i], num);
        if (!num) {
            num = (HashINT *)malloc(sizeof(HashINT));
            num->val = nums[i];
            num->counts = 1;
            HASH_ADD_INT(ht, val, num);
        }
        else {
            num->counts++;
        }
    }
    return ht;
}

void HashINTFree(HashINT *ht) {
    HashINT *cur, *tmp;
    HASH_ITER(hh, ht, cur, tmp) {
        HASH_DEL(ht, cur);
        free(cur);
    }
}

typedef struct {
    HashINT *h_nums1;
    HashINT *h_nums2;
    int *nums2;
    int nums2Size;
} FindSumPairs;

FindSumPairs* findSumPairsCreate(int* nums1, int nums1Size, int* nums2, int nums2Size);
void findSumPairsFree(FindSumPairs* obj);

FindSumPairs* findSumPairsCreate(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    FindSumPairs *obj = calloc(1, sizeof(FindSumPairs));
    if (!obj)
        return NULL;

    obj->nums2 = (int *)malloc(nums2Size * sizeof(int));
    if (!obj->nums2)
        goto Failed;
    
    obj->h_nums1 = HashINTCreate(nums1, nums1Size);
    obj->h_nums2 = HashINTCreate(nums2, nums2Size);
    memcpy(obj->nums2, nums2, nums2Size * sizeof(int));
    obj->nums2Size = nums2Size;
    return obj;
Failed:
    findSumPairsFree(obj);
    return NULL;  
}

void findSumPairsAdd(FindSumPairs* obj, int index, int val) {
    if (!obj)
        return;
    HashINT *num = NULL;
    int old_value = obj->nums2[index];
    int new_value = obj->nums2[index] + val;
    
    HASH_FIND_INT(obj->h_nums2, &old_value, num);
    if (num) {
        num->counts--;
    }
    num = NULL;
    HASH_FIND_INT(obj->h_nums2, &new_value, num);
    if (num) {
        num->counts++;
    }
    else {
        num = (HashINT *)malloc(sizeof(HashINT));
        num->val = new_value;
        num->counts = 1;
        HASH_ADD_INT(obj->h_nums2, val, num);
    }
    obj->nums2[index] = new_value;
}

int findSumPairsCount(FindSumPairs* obj, int tot) {
    if (!obj)
        return 0;

    int nums2Size = obj->nums2Size;
    HashINT *h_nums1 = obj->h_nums1;
    HashINT *h_nums2 = obj->h_nums2;
    int counts = 0;
    
    if (!h_nums2)
        return 0;

    HashINT *cur, *tmp;
    HASH_ITER(hh, h_nums1, cur, tmp) {
        HashINT *num = NULL;
        int target = tot - cur->val;
        HASH_FIND_INT(h_nums2, &target, num);
        if (num) {
            counts += num->counts * cur->counts;
        }
    }
    return counts;
}

void findSumPairsFree(FindSumPairs* obj) {
    if (!obj)
        return;
    if (obj->nums2)
        free(obj->nums2);
    if (obj->h_nums1)
        HashINTFree(obj->h_nums1);
    if (obj->h_nums2)
        HashINTFree(obj->h_nums2);
    free(obj);
}

// 
// Run Test
// 
typedef enum {
    add,
    count,
} Cmd;

typedef struct {
    Cmd cmd;
    union {
        int tot;
        struct {
            int idx;
            int val;
        };
    };
} Testcase;

void do_cmd(FindSumPairs *obj, Testcase test) {
    switch (test.cmd) {
        case add:
            findSumPairsAdd(obj, test.idx, test.val);
            printf("null\n");
            break;
        case count:
            printf("%d\n", findSumPairsCount(obj, test.tot));
            break;
        default:
            break;
    }
}

void solution(void) {
    int nums1[] = {1, 1, 2, 2, 2, 3};
    int nums2[] = {1, 4, 5, 2, 5, 4};

    Testcase tests[] = {
        {count, 7},
        {add, .idx = 3, .val = 2},
        {count, 8},
        {count, 4},
        {add, .idx = 0, .val = 1},
        {add, .idx = 1, .val = 1},
        {count, 7},
    };

    FindSumPairs *obj = findSumPairsCreate(nums1, sizeof(nums1)/sizeof(int), nums2, sizeof(nums2)/sizeof(int));
    printf("null\n");
    for (int i = 0; i < sizeof(tests)/sizeof(Testcase); i++) {
        do_cmd(obj, tests[i]);
    }
    findSumPairsFree(obj);
}

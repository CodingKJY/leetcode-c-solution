#define SOLVED 0
#include "leetcode.h"

// 
// Implementation
// 
int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    int **pascal = malloc(numRows * sizeof(int *));
    int *colSizes = malloc(numRows * sizeof(int));

    for (int i = 0; i < numRows; i++) {
        colSizes[i] = i + 1;
        pascal[i] = malloc(colSizes[i] * sizeof(int));
        if (i == 0) {
            pascal[0][0] = 1;
            continue;
        }
        for (int j = 0; j < colSizes[i]; j++) {
            if (j == 0 || j == colSizes[i] - 1)
                pascal[i][j] = 1;
            else
                pascal[i][j] = pascal[i-1][j-1] + pascal[i-1][j];
        }
    }

    *returnColumnSizes = colSizes;
    *returnSize = numRows;
    return pascal;
}

// 
// Run Test
// 
typedef struct {
    int k;
} Testcase;

void solution(void) {
    Testcase tests[] = {
        {.k = 5},
        {.k = 1},
    };

    for (int i = 0; i < ARRAY_SIZE(tests); i++) {
        int returnSize = 0;
        int *returnColSize;
        int **result = generate(tests[i].k, &returnSize, &returnColSize);

        printf("Pascal N=%d\n", tests[i].k);
        for (int i = 0; i < returnSize; i++) {
            for (int j = 0; j < returnColSize[i]; j++) {
                printf("%d ", result[i][j]);
            }
            puts("");
        }
        free(returnColSize);
        free(result);
    }
}

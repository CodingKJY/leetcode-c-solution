#define SOLVED 1
#include "leetcode.h"

// 
// Implementation
// 
bool isValid(char* word) {
    if (strlen(word) < 3)
        return false;
    char valid = 0;
    while (*word) {
        int c = tolower(*(word++));
        if (isalpha(c))
            valid |= 1 << (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
        else if (!isdigit(c))
            return false;
    }
    return valid == 3;
}

// 
// Run Test
// 
void solution(void) {
    char *tests[] = {
        // "234Adas",
        // "b3",
        // "a3$e",
        // "aya",
        "UuE6"
    };

    for (int i = 0; i < ARRAY_SIZE(tests); i++) {
        printf("%s\n", isValid(tests[i]) ? "true" : "false");
    }
}

#define SOLVED 1
#include "leetcode.h"

// 
// Implementation
// 
typedef struct {
    char data[100000];
    int top;
} Stack;

char pop(Stack *stack) {
    if (stack->top >= 0) {
        int c = stack->data[stack->top--];
        return c;
    }
    return 0;
}

void push(Stack *stack, char c) {
    int top = stack->top + 1;
    stack->data[top] = c;
    stack->top = top;
}

int is_empty(Stack *stack) {
    return stack->top < 0;
}

int maximumGain(char *s, int x, int y) {
    int gain = 0;
    int len = strlen(s);
    Stack stack = {.top = -1};
    Stack _stack = {.top = -1};
    char prefix = x > y ? 'a' : 'b';
    char suffix = x > y ? 'b' : 'a';
    while (len--) {
        char c = *s;
        if (c == 'a' || c == 'b') {
            if (c == suffix && (!is_empty(&stack) && stack.data[stack.top] == prefix)) {
                gain += x > y ? x : y;
                pop(&stack);
            }
            else {
                push(&stack, c);
            }
        }
        else {
            while (!is_empty(&stack)) {
                char _c = pop(&stack);
                if (_c == suffix && (!is_empty(&_stack) && _stack.data[_stack.top] == prefix)) {
                    gain += x > y ? y : x;
                    pop(&_stack);
                }
                else {
                    push(&_stack, _c);
                }
            }
            while (!is_empty(&_stack))
                pop(&_stack);
        }
        s++;
    }

    while (!is_empty(&stack)) {
        char _c = pop(&stack);
        if (_c == suffix && (!is_empty(&_stack) && _stack.data[_stack.top] == prefix)) {
            gain += x > y ? y : x;
            pop(&_stack);
        }
        else {
            push(&_stack, _c);
        }
    }
    while (!is_empty(&_stack))
        pop(&_stack);
    return gain;
}

// 
// Run Test
// 
typedef struct {
    char s[100000];
    int x;
    int y;
} TestCase;

void solution(void) {
    TestCase tests[] = {
        {.s = "cdbcbbaaabab", .x = 4, .y = 5},   // 19
        {.s = "aabbaaxybbaabb", .x = 5, .y = 4}, // 20
        {
            .s = "aabbabkbbbfvybssbtaobaaaabataaadabbbmakgabbaoapbbbbobaabvqhbbzbbkapabaavbbeghacabamdpaaqbqabbjbababmbakbaabajabasaabbwabrbbaabbafubayaazbbbaababbaaha",
            .x = 1926,
            .y = 4320,
        }, // 112374
    };

    for (int i = 0; i < ARRAY_SIZE(tests); i++) {
        printf("%d\n", maximumGain(tests[i].s, tests[i].x, tests[i].y));
    }
}

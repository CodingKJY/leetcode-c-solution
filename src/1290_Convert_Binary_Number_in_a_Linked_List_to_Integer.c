#define SOLVED 1
#include "leetcode.h"

// 
// Implementation
// 
struct ListNode {
    int val;
    struct ListNode *next;
};

int getDecimalValue(struct ListNode* head) {
    int res = 0;
    do {
        res = (res << 1) + head->val;
    } while ((head = head->next) && head);
    return res;
}
// 
// Run Test
// 
void add(struct ListNode **head, int val) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    if (!node) return;
    node->val = val;
    if (*head)
        node->next = *head;
    else
        node->next = NULL;
    *head = node;
}

void create(int *vals, int size, struct ListNode **head) {
    for (int i = 0; i < size; i++) {
        add(head, vals[i]);
    }
}

void release(struct ListNode **head) {
    struct ListNode *tmp = *head;
    while (tmp) {
        *head = (*head)->next;
        free(tmp);
        tmp = *head;
    }
}

void solution(void) {
    int vals[] = {1,0,0,1};
    struct ListNode *head = NULL;
    create(vals, ARRAY_SIZE(vals), &head);
    printf("%d\n", getDecimalValue(head));
    release(&head);
}

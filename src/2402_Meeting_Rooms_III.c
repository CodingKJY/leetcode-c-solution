#define SOLVED 0
#include "leetcode.h"

// 
// Implementation
// 
#define MAX_SIZE 100
typedef struct {
    int id;
    int booked;
    long long int last_day;
} Room;

typedef struct {
    Room data[MAX_SIZE];
    int size;
} MinHeap;

typedef struct {
    Room data[MAX_SIZE];
    int top;
} Stack;

void swap(Room *a, Room *b) {
    Room tmp = *a;
    memcpy(a, b, sizeof(Room));
    memcpy(b, &tmp, sizeof(Room));
}

Room heap_peek(MinHeap *heap) {
    return heap->size ? heap->data[0] : (Room){0};
}

void heap_push(MinHeap *heap, Room *room) {
    if (heap->size >= MAX_SIZE) 
        return;

    int i = heap->size++;
    memcpy(&heap->data[i], room, sizeof(Room));

    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap->data[i].last_day > heap->data[parent].last_day)
            break;
        if (heap->data[i].last_day < heap->data[parent].last_day || heap->data[i].id < heap->data[parent].id) {
            swap(&heap->data[parent], &heap->data[i]);
        }
        i = parent;
    }
}

Room heap_pop(MinHeap *heap) {
    if (heap->size == 0) 
        return (Room){0};

    Room min = heap->data[0];
    (heap->size)--;
    memcpy(&heap->data[0], &heap->data[heap->size], sizeof(Room));

    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size && heap->data[left].last_day < heap->data[smallest].last_day)
            smallest = left;
        if (right < heap->size && heap->data[right].last_day < heap->data[smallest].last_day)
            smallest = right;
        if (smallest == i)
            break;
        swap(&heap->data[i], &heap->data[smallest]);
        i = smallest;
    }
    return min;
}

Stack stack_init(void) {
    return (Stack) {
        .top = -1
    };
}

int push(Stack *stack, Room *room) {
    if (stack->top >= MAX_SIZE - 1)
        return 0;
    memcpy(&stack->data[++stack->top], room, sizeof(Room));
    return 1;
}

Room pop(Stack *stack) {
    if (stack->top == -1)
        return (Room){0};
    return stack->data[stack->top--];
}

int cmp(const void *a, const void *b) {
    return **(int **)a - **(int **)b;
}

int mostBooked(int n, int** meetings, int meetingsSize, int* meetingsColSize) {
    qsort(meetings, meetingsSize, sizeof(int *), cmp);
    
    MinHeap heap = {0};
    Room most = {0};
    int room_idx = 0;

    for (int i = 0; i < meetingsSize; i++) {
        if (heap.size == 0) {
            Room room = {
                .id = room_idx++,
                .booked = 1,
                .last_day = meetings[0][1],
            };
            heap_push(&heap, &room);
            continue;
        }

        Room top = heap_peek(&heap);
        Stack stack = stack_init();
        // open new room
        if (meetings[i][0] < top.last_day && room_idx < n) {
            Room room = {
                .id = room_idx++,
                .booked = 1,
                .last_day = meetings[i][1],
            };
            heap_push(&heap, &room);
        }
        // delay meeting if no free room
        else if (meetings[i][0] < top.last_day && room_idx >= n) {
            Room select = heap_pop(&heap);
            while (heap_peek(&heap).last_day && heap_peek(&heap).last_day == select.last_day) {
                Room room = heap_pop(&heap);
                if (room.id < select.id) {
                    push(&stack, &select);
                    select = room;
                }
                else
                    push(&stack, &room);
            }
            select.booked++;
            select.last_day += meetings[i][1] - meetings[i][0];
            heap_push(&heap, &select);

            if (most.booked < select.booked)
                memcpy(&most, &select, sizeof(Room));
            else if (select.booked == most.booked && select.id < most.id)
                memcpy(&most, &select, sizeof(Room));
        }
        // find free room
        else if (meetings[i][0] >= top.last_day) {
            Room select = heap_pop(&heap);
            while (heap_peek(&heap).last_day && meetings[i][0] >= heap_peek(&heap).last_day) {
                Room room = heap_pop(&heap);
                if (room.id < select.id) {
                    push(&stack, &select);
                    select = room;
                }
                else
                    push(&stack, &room);
            }
            select.booked++;
            select.last_day = meetings[i][1];
            heap_push(&heap, &select);

            if (most.booked < select.booked)
                memcpy(&most, &select, sizeof(Room));
            else if (select.booked == most.booked && select.id < most.id)
                memcpy(&most, &select, sizeof(Room));
        }

        while (stack.top != -1) {
            Room room = pop(&stack);
            heap_push(&heap, &room);
        }
    }
    return most.id;
}

// 
// Run Test
// 
typedef struct {
    int start;
    int end;
} Meeting;
#define Meeting(start, end) (Meeting){start,end}

typedef struct {
    int n;
    int size;
    Meeting meetings[MAX_SIZE];
} Meetings_Series;

typedef struct {
    int n;
    int meetingsSize;
    int meetingsColSize;
    int **meetings;
} Testcase;

void solution(void) {
    Meetings_Series series[] = {
        {  // 0
            .n = 2,
            .size = 4,
            .meetings = {
                Meeting(0,10),
                Meeting(1,5),
                Meeting(2,7),
                Meeting(3,4),
            },
        },
        {  // 1
            .n = 3,
            .size = 5,
            .meetings = {
                Meeting(1,20),
                Meeting(2,10),
                Meeting(3,5),
                Meeting(4,9),
                Meeting(6,8),
            },
        },
        {  // 0
            .n = 2,
            .size = 4,
            .meetings = {
                Meeting(0,10),
                Meeting(1,2),
                Meeting(12,14),
                Meeting(13,15),
            }
        },
        {  // 0
            .n = 2,
            .size = 4,
            .meetings = {
                Meeting(0,10),
                Meeting(1,2),
                Meeting(12,20),
                Meeting(15,16),
            }
        },
        {  // 1
            .n = 3,
            .size = 5,
            .meetings = {
                Meeting(0,10),
                Meeting(1,9),
                Meeting(2,8),
                Meeting(3,7),
                Meeting(4,6),
            }
        },
        {  // 0
            .n = 3,
            .size = 3,
            .meetings = {
                Meeting(13,20),
                Meeting(5,17),
                Meeting(17,19),
            }
        },
        {  // 1
            .n = 3,
            .size = 6,
            .meetings = {
                Meeting(1,27),
                Meeting(29,49),
                Meeting(47,49),
                Meeting(41,43),
                Meeting(15,36),
                Meeting(11,15),
            }
        }
    };

    for (int i = 0; i < ARRAY_SIZE(series); i++) {
        Testcase test;
        test.n = series[i].n;
        test.meetingsSize = series[i].size;
        test.meetingsColSize = 2;
        test.meetings = malloc(test.meetingsSize * sizeof(int *));
        for (int j = 0; j < test.meetingsSize; j++) {
            test.meetings[j] = malloc(test.meetingsColSize * sizeof(int));
            test.meetings[j][0] = series[i].meetings[j].start;
            test.meetings[j][1] = series[i].meetings[j].end;
            // printf("%d %d\n", test.meetings[j][0], test.meetings[j][1]);
        }
        printf("%d\n", mostBooked(test.n, test.meetings, test.meetingsSize, &test.meetingsColSize));

        for (int j = 0; j < test.meetingsSize; j++) {
            if (test.meetings[j])
                free(test.meetings[j]);
        }
        if (test.meetings)
            free(test.meetings);
    }
}
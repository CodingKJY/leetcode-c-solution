#define SOLVED 1
#include "leetcode.h" 

// 
// Implementations
// 
typedef struct {
    int start;
    int end;
} Sched;

void swap(Sched *a, Sched *b) {
    Sched tmp = *a;
    a->start = b->start;
    b->start = tmp.start;
    a->end = b->end;
    b->end = tmp.end;
}

typedef struct {
    Sched data[100000];
    int size;
} MinHeap;

Sched heap_peek(MinHeap *heap) {
    return heap->size ? heap->data[0] : (Sched){0};
}

void heap_push(MinHeap *heap, int start, int end) {
    if (heap->size >= 100000) 
        return;

    int i = heap->size++;
    heap->data[i].start = start;
    heap->data[i].end = end;

    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->data[parent].end <= heap->data[i].end)
            break;
        swap(&heap->data[parent], &heap->data[i]);
        i = parent;
    }
}

Sched heap_pop(MinHeap *heap) {
    if (heap->size == 0) 
        return (Sched){0};

    Sched min = heap->data[0];
    (heap->size)--;
    heap->data[0].start = heap->data[heap->size].start;
    heap->data[0].end = heap->data[heap->size].end;

    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size && heap->data[left].end < heap->data[smallest].end)
            smallest = left;
        if (right < heap->size && heap->data[right].end < heap->data[smallest].end)
            smallest = right;
        if (smallest == i)
            break;
        swap(&heap->data[i], &heap->data[smallest]);
        i = smallest;
    }
    return min;
}

int cmp(const void *a, const void *b) {
    int ret = **(int **)a - **(int **)b;
    return ret ? ret : *(*(int **)a + 1) - *(*(int **)b + 1);
}

int maxEvents(int** events, int eventsSize, int* eventsColSize) {
    qsort(events, eventsSize, sizeof(int *), cmp);

    MinHeap expired = { 0 };
    int event_idx = 0;
    int attends = 0;
    for (int today = **(events + event_idx); today <= 100000; today++) {
        Sched event;
        if (event_idx >= eventsSize && !heap_peek(&expired).end) 
            break;
        // schedule
        while (event_idx < eventsSize && today == **(events + event_idx)) {
            heap_push(&expired,  **(events + event_idx), *(*(events + event_idx) + 1));
            // printf("scheduled [%d %d]\n", **(events + event_idx), *(*(events + event_idx) + 1));
            event_idx++;
        }
        // remove 
        while (heap_peek(&expired).end && heap_peek(&expired).end < today) {
            event = heap_pop(&expired);
            // printf("expired [%d %d]\n", event.start, event.end);
        }
        // attend event
        event = heap_pop(&expired);
        if (event.start) {
            attends++;
            // printf("attend [%d %d]\n", event.start, event.end);
        }
    }
    return attends;   
}

// 
// Run Test
// 
typedef struct {
    int **events;
    int rsize;
    int csize;
} Testcase;

void solution(void) {
    int _events[][2] = { // 5
        {7,11},{7,11},{7,11},{9,10},{9,11}
    };

    Testcase test;
    test.rsize = sizeof(_events)/(2 * sizeof(int));
    test.csize = 2;
    test.events = malloc(test.rsize * sizeof(int *));
    for (int i = 0; i < test.rsize; i++) {
        test.events[i] = malloc(2 * sizeof(int));
        memcpy(test.events[i], _events[i], 2 * sizeof(int));
    }
    printf("%d\n", maxEvents(test.events, test.rsize, &test.csize));
    
    for (int i = 0; i < test.rsize; i++) {
        free(test.events[i]);
    }
    free(test.events);
}

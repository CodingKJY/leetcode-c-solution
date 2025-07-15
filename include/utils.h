#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include "uthash.h"
#include "utlist.h"

#define ARRAY_SIZE(arr) sizeof(arr)/sizeof(arr[0])
#define MIN(x, y) { x <= y ? x : y }
#define MAX(x, y) { x >= y ? x : y }

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

#define MAX_HEAP_CAPACITY 100000
typedef struct {
    void *data;
    size_t len;  // len of data array
    size_t size; // size of data
    size_t capacity;
    int (*cmp)(void *, void *);
} Heap;

static inline Heap HEAP_INIT(size_t size, int (*cmp)(void *, void *)) {
    Heap heap;
    heap.data = malloc(MAX_HEAP_CAPACITY * size);
    if (!heap.data)
        return (Heap){0};
    heap.len = 0;
    heap.size = size;
    heap.capacity = MAX_HEAP_CAPACITY;
    heap.cmp = cmp;
    return heap;
};

static inline void HEAP_RELEASE(Heap *heap) {
    if (heap->data) free(heap->data);
}

typedef struct {
    int (*PUSH)(Heap *heap, void *data);
    int (*POP)(Heap *heap, void *res);
    void (*PEEK)(Heap *heap, void *res);
    int (*IS_EMPTY)(Heap *heap);
} Heap_op;
extern Heap_op HEAP;

#endif /* __UTILS_H__ */
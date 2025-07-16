#include "utils.h"

static void
swap(void *a, void *b, size_t size)
{
    void *tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

static void *
heap_get(Heap *heap, size_t idx)
{
    return (unsigned char *)heap->data + idx * heap->size;
}

static void
heap_buttom_up(Heap *heap, size_t idx)
{
    if (idx == 0) return;
    
    size_t parent = (idx - 1) / 2;
    if (heap->cmp(heap_get(heap, idx), heap_get(heap, parent))) {
        swap(heap_get(heap, idx), heap_get(heap, parent), heap->size);
        heap_buttom_up(heap, parent);
    }
}

static void
heap_top_down(Heap *heap, size_t idx)
{
    size_t left = 2 * idx + 1;
    size_t right = 2 * idx + 2;
    size_t largest = idx;
    
    if (left < heap->len && heap->cmp(heap_get(heap, left), heap_get(heap, largest))) {
        largest = left;
    }
    if (right < heap->len && heap->cmp(heap_get(heap, right), heap_get(heap, largest))) {
        largest = right;
    }
    if (largest != idx) {
        swap(heap_get(heap, idx), heap_get(heap, largest), heap->size);
        heap_top_down(heap, largest);
    }
}

static int
HEAP_PUSH(Heap *heap, void *data)
{
    if (heap->len >= heap->capacity) 
        return -1;

    int i = heap->len++;
    memcpy(heap_get(heap, i), data, heap->size);
    heap_buttom_up(heap, i);
    return 0;
}

static int
HEAP_POP(Heap *heap, void *res)
{
    if (heap->len == 0) 
        return -1;
    if (res)
        memcpy(res, heap_get(heap, 0), heap->size);
    memcpy(heap_get(heap, 0), heap_get(heap, heap->len - 1), heap->size);
    heap->len -= 1;
    heap_top_down(heap, 0);
    return 0;
}

static void
HEAP_PEEK(Heap *heap, void *res)
{
    if (heap->len == 0) {
        memset(res, 0, heap->size);
        return;
    }
    memcpy(res, heap_get(heap, 0), heap->size);
}

static int
HEAP_IS_EMPTY(Heap *heap)
{
    return !heap->len;
}

static Heap HEAP_INIT(size_t size, int (*cmp)(void *, void *)) {
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

static void HEAP_RELEASE(Heap *heap) {
    if (heap->data) free(heap->data);
}

Heap_op HEAP = {
    .INIT = HEAP_INIT,
    .FREE = HEAP_RELEASE,
    .POP = HEAP_POP,
    .PUSH = HEAP_PUSH,
    .PEEK = HEAP_PEEK,
    .IS_EMPTY = HEAP_IS_EMPTY,
};

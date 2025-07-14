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
buttom_up(Heap *heap, size_t idx)
{
    if (idx == 0) return;
    
    size_t parent = (idx - 1) / 2;
    if (heap->cmp(heap_get(heap, idx), heap_get(heap, parent))) {
        swap(heap_get(heap, idx), heap_get(heap, parent), heap->size);
        buttom_up(heap, parent);
    }
}

static void
top_down(Heap *heap, size_t idx)
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
        top_down(heap, largest);
    }
}

static int
_PUSH(Heap *heap, void *data)
{
    if (heap->len >= heap->capacity) 
        return -1;

    int i = heap->len++;
    memcpy(heap_get(heap, i), data, heap->size);
    buttom_up(heap, i);
    return 0;
}

static int
_POP(Heap *heap, void *res)
{
    if (heap->len == 0) 
        return -1;

    memcpy(res, heap_get(heap, 0), heap->size);
    memcpy(heap_get(heap, 0), heap_get(heap, heap->len - 1), heap->size);
    heap->len -= 1;
    top_down(heap, 0);
    return 0;
}

static void
_PEEK(Heap *heap, void *res)
{
    if (heap->len == 0) {
        memset(res, 0, heap->size);
        return;
    }
    memcpy(res, heap_get(heap, 0), heap->size);
}

static int
_IS_EMPTY(Heap *heap)
{
    return !heap->len;
}

Heap_op HEAP = {
    .POP = _POP,
    .PUSH = _PUSH,
    .PEEK = _PEEK,
    .IS_EMPTY = _IS_EMPTY,
};

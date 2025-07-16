# Leetcode Solution in C

### Working on
- [ ] 1751
- [ ] 3440

### Usage
Check solved problems
```bash
make
```

Run test
```bash
make [problem-id]
```

### Add Solution
1. Generate template by `make temp PROB="<number>. <problem_name>"`
2. Implement `void solution(void)`

### Utils

#### Heap usage

- `HEAP.INIT(size_t size, int (*cmp)(void *, void *))`
- `HEAP.FREE(Heap *heap)`
- `HEAP.PUSH(Heap *heap, void *data)`
- `HEAP.POP(Heap *heap, void *res)`
- `HEAP.PEEK(Heap *heap, void *res)`
- `HEAP.IS_EMPTY(Heap *heap)`

```c
typedef struct {
    int start;
    int end;
} Event;

int cmp(void *a, void*b) {
    return ((Event *)a)->start <= ((Event *)b)->start;
}

int main() {
    Heap min_heap = HEAP.INIT(sizeof(Event), cmp);
    Event events[] = {
        {4,8},
        {3,6},
        {1,2},
        {2,5},
        {7,9},
    };

    for (int i = 0; i < ARRAY_SIZE(events); i++) {
        HEAP.PUSH(&heap, &events[i]);
    }

    Event e;
    HEAP.POP(&heap, &e);
    printf("%d %d\n", e.start, e.end);
    
    HEAP.FREE(&heap);
    return 0;
}

```




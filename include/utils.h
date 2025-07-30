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
#define MIN(x, y) x <= y ? x : y
#define MAX(x, y) x >= y ? x : y

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

// Network byte order
typedef uint32_t __be32;

__be32 in_aton(const char *str);

#endif /* __UTILS_H__ */
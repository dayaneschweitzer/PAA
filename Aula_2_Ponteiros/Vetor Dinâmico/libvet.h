#ifndef LIBVET_H
#define LIBVET_H

#include <stdlib.h>

typedef struct {
    int *array;
    size_t size;
    size_t capacity;
} DynamicIntArray;

void initDynamicIntArray(DynamicIntArray *vec, size_t initial_capacity);
void pushBack(DynamicIntArray *vec, int value);
void freeDynamicIntArray(DynamicIntArray *vec);

#endif /* LIBVET_H */
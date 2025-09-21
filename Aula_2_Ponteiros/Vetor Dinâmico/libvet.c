#include "libvet.h"
#include <stdio.h>
#include <stdlib.h>

void initDynamicIntArray(DynamicIntArray *vec, size_t initial_capacity) {
    if (!vec) {
        fprintf(stderr, "Erro: ponteiro vec nulo em initDynamicIntArray.\n");
        exit(EXIT_FAILURE);
    }

    if (initial_capacity == 0) {
        // garante capacidade mínima 1
        initial_capacity = 1;
    }

    vec->array = (int *)malloc(initial_capacity * sizeof(int));
    if (!vec->array) {
        fprintf(stderr, "Erro: falha ao alocar memoria inicial (%zu ints).\n", initial_capacity);
        exit(EXIT_FAILURE);
    }

    vec->size = 0;
    vec->capacity = initial_capacity;
}

void pushBack(DynamicIntArray *vec, int value) {
    if (!vec || !vec->array) {
        fprintf(stderr, "Erro: vetor nao inicializado em pushBack.\n");
        exit(EXIT_FAILURE);
    }

    if (vec->size == vec->capacity) {
        size_t new_capacity = (vec->capacity == 0) ? 1 : (vec->capacity * 2);
        int *new_array = (int *)realloc(vec->array, new_capacity * sizeof(int));
        if (!new_array) {
            fprintf(stderr, "Erro: falha ao realocar memoria para %zu ints.\n", new_capacity);
            // vec>array permanece válido; mas conforme especificação, encerramos o programa
            exit(EXIT_FAILURE);
        }
        vec->array = new_array;
        vec->capacity = new_capacity;
    }

    vec->array[vec->size++] = value;
}

void freeDynamicIntArray(DynamicIntArray *vec) {
    if (!vec) return;
    free(vec->array);
    vec->array = NULL;
    vec->size = 0;
    vec->capacity = 0;
}

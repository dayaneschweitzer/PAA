#include "stack_pub.h"
#include "stack_pri.h"
#include <stdlib.h>
#include <string.h>

/* Verificação interna de integridade */
static int _valid(pStack p) {
    return (p != NULL &&
            p->buffer != NULL &&
            p->size > 0 &&
            p->sizedata > 0 &&
            p->top >= 0 &&
            p->top <= p->size);
}

int stack(ppStack pp, int size, int sizedata) {
    if (pp == NULL || size <= 0 || sizedata <= 0) return FAIL;
    if (*pp != NULL) return FAIL; /* evita sobrescrever pilha já alocada */

    pStack p = (pStack) malloc(sizeof(*p));
    if (!p) return FAIL;

    p->buffer = malloc((size_t)size * (size_t)sizedata);
    if (!p->buffer) {
        free(p);
        return FAIL;
    }

    p->size     = size;
    p->sizedata = sizedata;
    p->top      = 0;

    *pp = p;
    return SUCCESS;
}

int unstack(ppStack pp) {
    if (pp == NULL || *pp == NULL) return FAIL;
    pStack p = *pp;

    if (p->buffer) {
        free(p->buffer);
        p->buffer = NULL;
    }
    free(p);
    *pp = NULL;
    return SUCCESS;
}

int push(pStack p, void *element) {
    if (!_valid(p) || element == NULL) return FAIL;
    if (p->top >= p->size) return FAIL; /* pilha cheia */

    memcpy((char*)p->buffer + ((size_t)p->top * (size_t)p->sizedata),
           element,
           (size_t)p->sizedata);
    p->top++;
    return SUCCESS;
}

int pop(pStack p, void *element) {
    if (!_valid(p) || element == NULL) return FAIL;
    if (p->top <= 0) return FAIL; /* pilha vazia */

    p->top--;
    memcpy(element,
           (char*)p->buffer + ((size_t)p->top * (size_t)p->sizedata),
           (size_t)p->sizedata);
    return SUCCESS;
}

int cleanStack(pStack p) {
    if (!_valid(p)) return FAIL;
    memset(p->buffer, 0, (size_t)p->size * (size_t)p->sizedata);
    p->top = 0;
    return SUCCESS;
}

int top(pStack p, void *out) {
    if (!_valid(p) || out == NULL) return FAIL;
    if (p->top <= 0) return FAIL; /* pilha vazia */

    memcpy(out,
           (char*)p->buffer + ((size_t)(p->top - 1) * (size_t)p->sizedata),
           (size_t)p->sizedata);
    return SUCCESS;
}

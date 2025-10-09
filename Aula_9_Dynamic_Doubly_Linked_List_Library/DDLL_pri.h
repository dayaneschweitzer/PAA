#ifndef DDLL_PRI_H
#define DDLL_PRI_H

#include <stdlib.h>
#include <string.h>
#include "DDLL_pub.h"

/* Nó da lista duplamente encadeada */
typedef struct DDLLNode {
    struct DDLLNode *prev;
    struct DDLLNode *next;
    unsigned char data[]; /* buffer flexível para dados genéricos */
} DDLLNode;

/* Nó descritor da lista */
struct DDLL {
    DDLLNode *head;
    DDLLNode *tail;
    int size;       /* quantidade de elementos */
    int sizedata;   /* tamanho (em bytes) de cada elemento */
};

/* Helpers "privados" */
static DDLLNode *ddll_new_node(int sizedata, const void *element) {
    DDLLNode *n = (DDLLNode*) malloc(sizeof(DDLLNode) + (size_t)sizedata);
    if (!n) return NULL;
    n->prev = n->next = NULL;
    if (element && sizedata > 0) memcpy(n->data, element, (size_t)sizedata);
    return n;
}

static DDLLNode *ddll_node_at(struct DDLL *l, int idx) {
    if (!l || idx < 0 || idx >= l->size) return NULL;
    /* Caminho otimizado: do começo ou do fim */
    if (idx <= l->size / 2) {
        DDLLNode *cur = l->head;
        for (int i = 0; i < idx; ++i) cur = cur->next;
        return cur;
    } else {
        DDLLNode *cur = l->tail;
        for (int i = l->size - 1; i > idx; --i) cur = cur->prev;
        return cur;
    }
}

#endif /* DDLL_PRI_H */

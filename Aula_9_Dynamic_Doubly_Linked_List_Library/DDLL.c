#include <stdio.h>
#include "DDLL_pri.h"

/* ========= Criação / Destruição ========= */

int cDDLL(ppDDLL pp, int sizedata) {
    if (!pp || sizedata <= 0) return FAIL;
    struct DDLL *l = (struct DDLL*) malloc(sizeof(struct DDLL));
    if (!l) return FAIL;
    l->head = l->tail = NULL;
    l->size = 0;
    l->sizedata = sizedata;
    *pp = (pDDLL) l;
    return SUCCESS;
}

int cleanDDLL(pDDLL p) {
    if (!p) return FAIL;
    struct DDLL *l = (struct DDLL*) p;
    DDLLNode *cur = l->head;
    while (cur) {
        DDLLNode *nx = cur->next;
        free(cur);
        cur = nx;
    }
    l->head = l->tail = NULL;
    l->size = 0;
    return SUCCESS;
}

int dDDLL(ppDDLL pp) {
    if (!pp || !*pp) return FAIL;
    struct DDLL *l = (struct DDLL*) *pp;
    cleanDDLL((pDDLL) l);
    free(l);
    *pp = NULL;
    return SUCCESS;
}

/* ========= Inserções ========= */

int iBegin(pDDLL p, void *element) {
    if (!p) return FAIL;
    struct DDLL *l = (struct DDLL*) p;
    DDLLNode *n = ddll_new_node(l->sizedata, element);
    if (!n) return FAIL;

    n->next = l->head;
    n->prev = NULL;
    if (l->head) l->head->prev = n; else l->tail = n; /* lista estava vazia */
    l->head = n;
    l->size++;
    return SUCCESS;
}

int iEnd(pDDLL p, void *element) {
    if (!p) return FAIL;
    struct DDLL *l = (struct DDLL*) p;
    DDLLNode *n = ddll_new_node(l->sizedata, element);
    if (!n) return FAIL;

    n->prev = l->tail;
    n->next = NULL;
    if (l->tail) l->tail->next = n; else l->head = n; /* lista vazia */
    l->tail = n;
    l->size++;
    return SUCCESS;
}

int iPosition(pDDLL p, int N, void *element) {
    if (!p) return FAIL;
    struct DDLL *l = (struct DDLL*) p;
    if (N < 0 || N > l->size) return FAIL; /* válido: 0..size */

    if (N == 0) return iBegin(p, element);
    if (N == l->size) return iEnd(p, element);

    DDLLNode *after = ddll_node_at(l, N);
    if (!after) return FAIL; /* por segurança */

    DDLLNode *n = ddll_new_node(l->sizedata, element);
    if (!n) return FAIL;

    DDLLNode *before = after->prev;
    /* ligações: before <-> n <-> after */
    n->prev = before;
    n->next = after;
    before->next = n;
    after->prev = n;

    l->size++;
    return SUCCESS;
}

/* ========= Remoções ========= */

int rBegin(pDDLL p, void *element) {
    if (!p) return FAIL;
    struct DDLL *l = (struct DDLL*) p;
    if (l->size == 0) return FAIL;

    DDLLNode *n = l->head;
    if (element) memcpy(element, n->data, (size_t)l->sizedata);

    l->head = n->next;
    if (l->head) l->head->prev = NULL; else l->tail = NULL;
    free(n);
    l->size--;
    return SUCCESS;
}

int rEnd(pDDLL p, void *element) {
    if (!p) return FAIL;
    struct DDLL *l = (struct DDLL*) p;
    if (l->size == 0) return FAIL;

    DDLLNode *n = l->tail;
    if (element) memcpy(element, n->data, (size_t)l->sizedata);

    l->tail = n->prev;
    if (l->tail) l->tail->next = NULL; else l->head = NULL;
    free(n);
    l->size--;
    return SUCCESS;
}

int rPosition(pDDLL p, int N, void *element) {
    if (!p) return FAIL;
    struct DDLL *l = (struct DDLL*) p;
    if (N < 0 || N >= l->size) return FAIL;

    if (N == 0) return rBegin(p, element);
    if (N == l->size - 1) return rEnd(p, element);

    DDLLNode *n = ddll_node_at(l, N);
    if (!n) return FAIL;

    if (element) memcpy(element, n->data, (size_t)l->sizedata);

    DDLLNode *before = n->prev;
    DDLLNode *after  = n->next;
    before->next = after;
    after->prev  = before;
    free(n);
    l->size--;
    return SUCCESS;
}

/* ========= Buscas (leitura sem remover) ========= */

int sBegin(pDDLL p, void *element) {
    if (!p) return FAIL;
    struct DDLL *l = (struct DDLL*) p;
    if (l->size == 0) return FAIL;
    if (element) memcpy(element, l->head->data, (size_t)l->sizedata);
    return SUCCESS;
}

int sEnd(pDDLL p, void *element) {
    if (!p) return FAIL;
    struct DDLL *l = (struct DDLL*) p;
    if (l->size == 0) return FAIL;
    if (element) memcpy(element, l->tail->data, (size_t)l->sizedata);
    return SUCCESS;
}

int sPosition(pDDLL p, int N, void *element) {
    if (!p) return FAIL;
    struct DDLL *l = (struct DDLL*) p;
    if (N < 0 || N >= l->size) return FAIL;
    DDLLNode *n = ddll_node_at(l, N);
    if (!n) return FAIL;
    if (element) memcpy(element, n->data, (size_t)l->sizedata);
    return SUCCESS;
}

/* ========= Utilidades ========= */

int empty(pDDLL p) {
    if (!p) return FAIL; /* tratar lista inexistente como falha */
    struct DDLL *l = (struct DDLL*) p;
    return (l->size == 0) ? 0 : 1; /* 0 = vazia, 1 = NÃO vazia */
}

int countElements(pDDLL p) {
    if (!p) return 0;
    struct DDLL *l = (struct DDLL*) p;
    return l->size;
}

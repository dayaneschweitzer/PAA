#include "Stack_DDLL_pri.h"

/*
 * Implementação da pilha usando a DDLL fornecida pelo sistema.
 * A pilha é modelada como um wrapper contendo um ponteiro para o descritor da DDLL
 * e o tamanho do dado armazenado.
 */

int stack(ppStack pp, int sizedata) {
    if (!pp || sizedata <= 0) return FAIL;

    /* aloca a estrutura da pilha */
    *pp = (pStack) malloc(sizeof(**pp));
    if (!*pp) return FAIL;

    /* cria a DDLL interna com o mesmo sizedata */
    (*pp)->list = NULL;
    (*pp)->sizedata = sizedata;
    if (cDDLL(&((*pp)->list), sizedata) == FAIL) {
        free(*pp);
        *pp = NULL;
        return FAIL;
    }
    return SUCCESS;
}

int unstack(ppStack pp) {
    if (!pp || !*pp) return FAIL;

    /* destrói a DDLL interna */
    if (dDDLL(&((*pp)->list)) == FAIL) {
        free(*pp);
        *pp = NULL;
        return FAIL;
    }

    free(*pp);
    *pp = NULL;
    return SUCCESS;
}

int push(pStack p, void *element) {
    if (!p || !p->list || !element) return FAIL;

    /* empilha no final para que pop remova do topo (tail) */
    if (iEnd(p->list, element) == FAIL) return FAIL;
    return SUCCESS;
}

int pop(pStack p, void *element) {
    if (!p || !p->list || !element) return FAIL;

    /* remove do final (topo da pilha) */
    if (rEnd(p->list, element) == FAIL) return FAIL;
    return SUCCESS;
}

int cleanStack(pStack p) {
    if (!p || !p->list) return FAIL;
    return cleanDDLL(p->list);
}

int top(pStack p, void *top) {
    if (!p || !p->list || !top) return FAIL;

    /* consulta o último elemento sem removê-lo */
    if (sEnd(p->list, top) == FAIL) return FAIL;
    return SUCCESS;
}

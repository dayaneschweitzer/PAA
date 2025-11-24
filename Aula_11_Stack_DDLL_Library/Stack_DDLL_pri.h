#ifndef STACK_DDLL_PRI_H
#define STACK_DDLL_PRI_H

#include <stdlib.h>
#include <string.h>

#include "Stack_DDLL_pub.h"
#include "DDLL_pub.h"

/*
 * Parte PRIVADA da Stack_DDLL (não expor em headers públicos).
 *
 * Decisões de projeto:
 * - A pilha é um wrapper sobre a DDLL fornecida pelo sistema.
 * - O "topo" da pilha será o FIM (tail) da DDLL:
 *     push -> iEnd
 *     pop  -> rEnd
 *     top  -> sEnd
 * - Manter 'sizedata' para validar chamadas e documentar o tamanho esperado.
 *
 * Invariantes:
 * - p != NULL implica p->list != NULL após 'stack' bem-sucedido.
 * - A DDLL obedece: (size == 0) <=> head == tail == NULL.
 */

struct Stack {
    pDDLL list;     /* descritor da lista duplamente encadeada (DDLL) */
    int sizedata;   /* tamanho, em bytes, do dado armazenado */
};

/* --------------------------- Helpers "privados" --------------------------- */
/* Retorna 1 se a pilha está vazia, 0 caso contrário, FAIL em erro. */
static inline int stack_is_empty(pStack p) {
    if (!p || !p->list) return FAIL;
    return empty(p->list);
}

/* Quantidade de elementos na pilha ou FAIL em erro. */
static inline int stack_count(pStack p) {
    if (!p || !p->list) return FAIL;
    return countElements(p->list);
}

#endif /* STACK_DDLL_PRI_H */
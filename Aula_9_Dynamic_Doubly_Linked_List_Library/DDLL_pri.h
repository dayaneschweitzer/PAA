#ifndef DDLL_PRI_H
#define DDLL_PRI_H

#include <stdlib.h>
#include <string.h>
#include "DDLL_pub.h"

/*
 * Parte PRIVADA da DDLL (não expor em headers públicos).
 *
 * Decisões de projeto:
 * - Nó com "data[]" (VLA/flexible array member) para tornar a lista GENÉRICA:
 *   o conteúdo do elemento é copiado para dentro do nó (memcpy), então o
 *   chamador não precisa manter o buffer original vivo.
 * - Descritor guarda head/tail/size/sizedata.
 * - Helpers estáticos "ddll_new_node" e "ddll_node_at" encapsulam detalhes
 *   de alocação e navegação (com otimização de caminho).
 */

/* -------------------- Nó da lista duplamente encadeada -------------------- */
/*
 * Layout:
 *   prev  -> ponteiro para nó anterior
 *   next  -> ponteiro para próximo nó
 *   data[]-> buffer flexível com 'sizedata' bytes (definido na criação da lista)
 *
 * Observação:
 * - "unsigned char data[]" é um flexible array member, padrão em C99+.
 * - Como o nó armazena os bytes do elemento, a DDLL é realmente genérica.
 */
typedef struct DDLLNode {
    struct DDLLNode *prev;
    struct DDLLNode *next;
    unsigned char data[]; /* buffer flexível para dados genéricos */
} DDLLNode;

/* ------------------------- Descritor (metadados) -------------------------- */
/*
 * Invariantes:
 * - size >= 0
 * - (size == 0) => head == NULL && tail == NULL
 * - (size >  0) => head != NULL && tail != NULL
 * - head->prev == NULL e tail->next == NULL
 * - Todos os nós entre head e tail estão bidirecionalmente ligados.
 */
struct DDLL {
    DDLLNode *head;
    DDLLNode *tail;
    int size;       /* quantidade de elementos */
    int sizedata;   /* tamanho (em bytes) de cada elemento */
};

/* --------------------------- Helpers "privados" --------------------------- */
/*
 * ddll_new_node
 * - Aloca um nó com espaço extra para 'sizedata' bytes.
 * - Copia o conteúdo apontado por 'element' (se não for NULL).
 * Custo: O(sizedata) devido ao memcpy; demais operações O(1).
 * Retorna: ponteiro para o nó criado ou NULL em falha.
 * Observação: prev/next iniciam como NULL (o encadeamento é feito por quem chama).
 */
static DDLLNode *ddll_new_node(int sizedata, const void *element) {
    DDLLNode *n = (DDLLNode*) malloc(sizeof(DDLLNode) + (size_t)sizedata);
    if (!n) return NULL;
    n->prev = n->next = NULL;
    if (element && sizedata > 0) memcpy(n->data, element, (size_t)sizedata);
    return n;
}

/*
 * ddll_node_at
 * - Devolve o ponteiro para o nó na posição 'idx' (base 0).
 * - Caminho otimizado: começa pelo head se idx <= size/2; senão começa pelo tail.
 *   Isso minimiza o número de passos para listas grandes.
 * Pré-condições: 0 <= idx < size (do contrário, retorna NULL).
 * Custo: O(min(idx, size-1-idx)).
 */
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

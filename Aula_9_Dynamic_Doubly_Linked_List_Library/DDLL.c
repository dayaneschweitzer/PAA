#include <stdio.h>
#include "DDLL_pri.h"

/* ========= Criação / Destruição ========= */

/**
 * cDDLL
 * Cria a lista (descritor) e inicializa campos.
 * @param pp: ponteiro para ponteiro da lista (será escrito aqui)
 * @param sizedata: tamanho do tipo armazenado (ex.: sizeof(int))
 * @return SUCCESS (0) ou FAIL (1)
 * Contratos:
 *  - sizedata > 0
 *  - *pp passa a apontar para uma lista válida (head/tail=NULL, size=0)
 */
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

/**
 * cleanDDLL
 * Remove todos os nós e zera head/tail/size (mantém o descritor).
 * @return SUCCESS/FAIL
 * Observação: não invalida o descritor; use dDDLL para destruir tudo.
 */
int cleanDDLL(pDDLL p) {
    if (!p) return FAIL;
    struct DDLL *l = (struct DDLL*) p;
    DDLLNode *cur = l->head;
    while (cur) {
        DDLLNode *nx = cur->next;
        free(cur);            // libera nó atual
        cur = nx;             // avança
    }
    l->head = l->tail = NULL; // lista vazia
    l->size = 0;
    return SUCCESS;
}

/**
 * dDDLL
 * Libera todos os nós (cleanDDLL) e o descritor; zera o ponteiro.
 * @return SUCCESS/FAIL
 * Pós-condição: *pp = NULL
 */
int dDDLL(ppDDLL pp) {
    if (!pp || !*pp) return FAIL;
    struct DDLL *l = (struct DDLL*) *pp;
    cleanDDLL((pDDLL) l);
    free(l);
    *pp = NULL;
    return SUCCESS;
}

/* ========= Inserções ========= */

/**
 * iBegin
 * Insere no início. O conteúdo apontado por 'element' é copiado
 * (tamanho: sizedata).
 * Custo: O(1).
 */
int iBegin(pDDLL p, void *element) {
    if (!p) return FAIL;
    struct DDLL *l = (struct DDLL*) p;
    DDLLNode *n = ddll_new_node(l->sizedata, element);
    if (!n) return FAIL;

    n->next = l->head;
    n->prev = NULL;
    if (l->head) l->head->prev = n; else l->tail = n; // lista estava vazia
    l->head = n;
    l->size++;
    return SUCCESS;
}

/**
 * iEnd
 * Insere no fim. Custo: O(1).
 */
int iEnd(pDDLL p, void *element) {
    if (!p) return FAIL;
    struct DDLL *l = (struct DDLL*) p;
    DDLLNode *n = ddll_new_node(l->sizedata, element);
    if (!n) return FAIL;

    n->prev = l->tail;
    n->next = NULL;
    if (l->tail) l->tail->next = n; else l->head = n; // lista vazia
    l->tail = n;
    l->size++;
    return SUCCESS;
}

/**
 * iPosition
 * Insere na posição N (base 0). Válido: 0..size.
 *  - N == 0  => iBegin
 *  - N == size => iEnd
 *  - meio => antes do nó atualmente em N
 * Custo: O(min(N, size-N)) pela navegação otimizada.
 */
int iPosition(pDDLL p, int N, void *element) {
    if (!p) return FAIL;
    struct DDLL *l = (struct DDLL*) p;
    if (N < 0 || N > l->size) return FAIL; // válido: 0..size

    if (N == 0) return iBegin(p, element);
    if (N == l->size) return iEnd(p, element);

    DDLLNode *after = ddll_node_at(l, N); // nó que ficará DEPOIS do novo
    if (!after) return FAIL;              // sanidade

    DDLLNode *n = ddll_new_node(l->sizedata, element);
    if (!n) return FAIL;

    DDLLNode *before = after->prev;
    // ligações: before <-> n <-> after
    n->prev = before;
    n->next = after;
    before->next = n;
    after->prev = n;

    l->size++;
    return SUCCESS;
}

/* ========= Remoções ========= */

/**
 * rBegin
 * Remove primeiro nó; se 'element' != NULL, copia o dado removido.
 * Custo: O(1).
 */
int rBegin(pDDLL p, void *element) {
    if (!p) return FAIL;
    struct DDLL *l = (struct DDLL*) p;
    if (l->size == 0) return FAIL;

    DDLLNode *n = l->head;
    if (element) memcpy(element, n->data, (size_t)l->sizedata);

    l->head = n->next;
    if (l->head) l->head->prev = NULL; else l->tail = NULL; // ficou vazia?
    free(n);
    l->size--;
    return SUCCESS;
}

/**
 * rEnd
 * Remove último nó. Custo: O(1).
 */
int rEnd(pDDLL p, void *element) {
    if (!p) return FAIL;
    struct DDLL *l = (struct DDLL*) p;
    if (l->size == 0) return FAIL;

    DDLLNode *n = l->tail;
    if (element) memcpy(element, n->data, (size_t)l->sizedata);

    l->tail = n->prev;
    if (l->tail) l->tail->next = NULL; else l->head = NULL; // ficou vazia?
    free(n);
    l->size--;
    return SUCCESS;
}

/**
 * rPosition
 * Remove o nó da posição N (base 0). Válido: 0..size-1.
 * Custo: O(min(N, size-N)).
 */
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

/**
 * sBegin / sEnd / sPosition
 * Apenas lê o dado (sem remoção). Copia para 'element' se não for NULL.
 * sPosition: N em [0, size-1]. Custo: O(1) para extremos, O(min(N, size-N)) no meio.
 */
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

/**
 * empty
 * Retorna 0 se VAZIA e 1 se NÃO vazia (conforme enunciado).
 * Observação: esse contrato é incomum; documente-o no relatório.
 */
int empty(pDDLL p) {
    if (!p) return FAIL;                 // lista inexistente -> FAIL
    struct DDLL *l = (struct DDLL*) p;
    return (l->size == 0) ? 0 : 1;       // 0 = vazia, 1 = não vazia
}

/**
 * countElements
 * Retorna a quantidade de elementos.
 */
int countElements(pDDLL p) {
    if (!p) return 0;
    struct DDLL *l = (struct DDLL*) p;
    return l->size;
}

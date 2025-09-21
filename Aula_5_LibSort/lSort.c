#include <stdlib.h>
#include <string.h>
#include "lSort_pub.h"
#include "lSort_pri.h"   

int cSort(ppSort pp, int sizedata) {
    if (pp == NULL || sizedata <= 0) return FAIL;  // Verifica argumentos inválidos

    *pp = (pSort) malloc(sizeof(struct lSort));    // Aloca a estrutura principal
    if (*pp == NULL) return FAIL;                  // Verifica falha na alocação

    (*pp)->head = NULL;                            // Inicializa a lista vazia
    (*pp)->size = 0;                               // Começa com zero elementos
    (*pp)->data_size = sizedata;                   // Armazena o tamanho do tipo de dado

    return SUCCESS;
}

int dSort(ppSort pp) {
    if (pp == NULL || *pp == NULL) return FAIL;    // Verifica se ponteiros são válidos

    Node *curr = (*pp)->head;                      // Começa do primeiro nó da lista
    while (curr) {                                 // Percorre toda a lista
        Node *temp = curr;                         // Salva o nó atual
        curr = curr->next;                         // Avança para o próximo
        free(temp->data);                          // Libera a memória dos dados
        free(temp);                                // Libera o nó
    }

    free(*pp);                                     // Libera a estrutura principal
    *pp = NULL;                                    // Evita dangling pointer

    return SUCCESS;
}

int iSort(pSort p, void *new, int (*cmp)(void *p1, void *p2)) {
    if (p == NULL || new == NULL || cmp == NULL) return FAIL;  // Verificação de argumentos

    Node *new_node = (Node *) malloc(sizeof(Node));            // Aloca novo nó
    if (new_node == NULL) return FAIL;

    new_node->data = malloc(p->data_size);                     // Aloca espaço para os dados
    if (new_node->data == NULL) {
        free(new_node);
        return FAIL;
    }

    memcpy(new_node->data, new, p->data_size);                 // Copia os dados para o novo nó
    new_node->next = NULL;

    // Percorre a lista para encontrar a posição correta
    Node **curr = &(p->head);
    while (*curr && cmp((*curr)->data, new) < 0) {
        curr = &((*curr)->next);  // Avança até achar o ponto certo (comparação)
    }

    // Insere o novo nó na posição correta (ordem crescente)
    new_node->next = *curr;
    *curr = new_node;

    p->size++;  // Atualiza o tamanho da lista

    return SUCCESS;
}

int printSort(pSort p, void (*process)(void *p)) {
    if (p == NULL || process == NULL) return FAIL;  // Verifica argumentos válidos

    Node *curr = p->head;                           // Começa do início da lista
    while (curr) {
        process(curr->data);                        // Aplica função ao dado
        curr = curr->next;                          // Avança para o próximo
    }

    return SUCCESS;
}
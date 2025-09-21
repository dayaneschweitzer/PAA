#include <stdlib.h>       // Para malloc, free
#include <string.h>       // Para memcpy
#include "queue_pri.h"
#include "queue_pub.h"

#define SUCCESS 0
#define FAIL 1

// Cria e inicializa uma fila estática circular
int cQueue(ppQueue pf, int size, int sizedata) {
    if (pf == NULL || sizedata <= 0) return FAIL;   // Verifica se os parâmetros são válidos

    *pf = (pQueue) malloc(sizeof(queue)); // Aloca memória para a estrutura da fila
    if (*pf == NULL) return FAIL;        // Verifica falha na alocação

    (*pf)->data = malloc(size * sizedata);  // Aloca memória para o array genérico que vai armazenar os dados
    if ((*pf)->data == NULL) {
        free(*pf);                              // Libera a estrutura, se falhar a alocação do array
        return FAIL;
    }
    // Define os parâmetros da estrutura
    (*pf)->capacity = size;  // Capacidade máxima da fila
    (*pf)->data_size = sizedata;  // Tamanho de cada dado (ex: sizeof(int))
    (*pf)->front = 0;             // Início da fila
    (*pf)->rear = 0;              // Final da fila
    (*pf)->size = 0;              // Começa com 0 elementos
    (*pf)->cmp = NULL;            // A função de comparação ainda não foi definida

    return SUCCESS;
}

// Libera toda a memória alocada da fila
int dQueue(ppQueue pf) {
    if (pf == NULL || *pf == NULL) return FAIL;  // Verifica se o ponteiro é válido

    free((*pf)->data);  // Libera o array de dados
    free(*pf);          // Libera a estrutura da fila

    *pf = NULL;         // Define o ponteiro como NULL para evitar uso indevido

    return SUCCESS;
}

// Enfileira um novo elemento na fila
int enqueue(pQueue f, void *element) {
    if (f == NULL || element == NULL) return FAIL;  // Verifica argumentos

    if ((f->rear + 1) % f->capacity == f->front) {
        return FAIL;  // Fila cheia
    }

    memcpy(f->data + (f->rear * f->data_size), element, f->data_size);  // Copia os dados

    f->rear = (f->rear + 1) % f->capacity;  // Move o índice de inserção
    f->size++;  // Aumenta o tamanho atual da fila

    return SUCCESS;
}

// Remove o elemento da frente da fila e copia para 'element'
int unqueue(pQueue f, void *element) {
    if (f == NULL || element == NULL) return FAIL;  // Verifica ponteiros

    if (f->front == f->rear) return FAIL;  // Fila vazia

    memcpy(element, f->data + (f->front * f->data_size), f->data_size);  // Copia o dado para quem chamou

    f->front = (f->front + 1) % f->capacity;  // Move o início da fila
    f->size--;  // Diminui o tamanho atual da fila

    return SUCCESS;
}

// Verifica se o primeiro elemento da fila é igual ao fornecido
int firstEqual(pQueue f, void *element) {
    if (f == NULL || element == NULL || f->cmp == NULL) return FAIL;  // Verificações

    if (f->front == f->rear) return FAIL;  // Fila vazia

    void *first_elem = f->data + (f->front * f->data_size);  // Posição do primeiro elemento

    if (f->cmp(first_elem, element) == 0) {  // Compara com a função do usuário
        return SUCCESS;
    }

    return FAIL;
}

// Define a função de comparação que será usada pela fila
int setcmp(pQueue f, int (*cmp)(void *p1, void *p2)) {
    if (f == NULL || cmp == NULL) return FAIL;

    f->cmp = cmp;  // Atribui a função de comparação fornecida

    return SUCCESS;
}

// Remove todos os elementos da fila, mantendo sua estrutura
int cleanQueue(pQueue f) {
    if (f == NULL || f->data == NULL) return FAIL; //Verifica se a fila foi corretamente alocada e está válida.
    //Resetando os índices e o contador de tamanho
    f->front = 0; // voltam ao início
    f->rear = 0; // voltam ao início
    f->size = 0; //zera - a fila está vazia.

    return SUCCESS;
}

// Retorna o número atual de elementos na fila
int sizeQueue(pQueue f) {
    if (f == NULL) return FAIL; //Verifica se a fila foi corretamente alocada. Se não, retorna erro.

    return f->size; //Retorna a quantidade de elementos presentes na fila, que está sendo atualizada pelas funções queue e unqueue.
}



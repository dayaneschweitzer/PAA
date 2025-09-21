#ifndef _QUEUE_PRI_H_
#define _QUEUE_PRI_H_

typedef struct queue {
    void *data;                // Vetor genérico (armazenará os elementos)
    int front;                 // Índice do início da fila
    int rear;                  // Índice do final da fila
    int size;                  // Número atual de elementos
    int capacity;              // Capacidade máxima da fila
    int data_size;             // Tamanho (em bytes) de cada elemento
    int (*cmp)(void*, void*);  // Ponteiro para função de comparação
} queue;

#endif
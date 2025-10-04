#ifndef QUEUE_PRI_H
#define QUEUE_PRI_H

#include "queue_pub.h"

// Estrutura interna da fila
struct Queue {
    void *data;         // Dados armazenados
    int size;           // Tamanho máximo da fila
    int sizedata;       // Tamanho de cada elemento
    int in, out;        // Índices de inserção e remoção
    int count;          // Total de elementos enfileirados
    int *accounting;    // Quantas vezes cada posição foi ocupada
    int *occupied;      // Indica se a posição está ocupada (1) ou não (0)
};

#endif 
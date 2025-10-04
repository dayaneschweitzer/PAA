#ifndef STACK_PRI_H
#define STACK_PRI_H

#include <stddef.h>

/* Implementação privada da pilha (não exportar esta struct no .h público) */
struct PE {
    void *buffer;   /* bloco contínuo com os dados */
    int size;       /* capacidade máxima (nº de elementos) */
    int sizedata;   /* tamanho (em bytes) de cada elemento */
    int top;        /* quantidade de elementos atualmente na pilha */
};

#endif /* STACK_PRI_H */
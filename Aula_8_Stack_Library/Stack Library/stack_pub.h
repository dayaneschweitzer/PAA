#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAIL 1

typedef struct PE *pStack, **ppStack;

// "Construtor": aloca memória e inicializa as variáveis
int stack(ppStack pp, int size, int sizedata);
// "Destrutor": libera memória da estrutura
int unstack(ppStack pp);

// **** "Operações de manipulação" ****
// Empilha um elemento 
int push(pStack p, void *element);
// Desempilha um elemento
int pop(pStack p, void *element);
// Remove todos os dados da pilha mantendo o descritor alocado.
int cleanStack(pStack p);

// **** "Operações de acesso" ****
// Retorna uma cópia do dado do topo
int top(pStack p, void *top);
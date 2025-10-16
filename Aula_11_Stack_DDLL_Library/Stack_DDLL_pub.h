#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAIL 1

/* TDAPilha_publico.h */

typedef struct Stack *pStack, **ppStack;

int stack(ppStack pp, int sizedata);
int unstack(ppStack pp);

int push(pStack p, void *element);
int pop(pStack p, void *element);

int cleanStack(pStack p);
int top(pStack p, void *top);
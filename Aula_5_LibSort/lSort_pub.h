#ifndef _SORT_INTERFACE_H_
#define _SORT_INTERFACE_H_

#define SUCCESS 0
#define FAIL 1

typedef struct lSort *pSort, **ppSort;

int cSort(ppSort pp, int sizedata);
int dSort(ppSort pp);
int iSort(pSort p, void *new, int (* cmp)(void *p1, void *p2));
int printSort(pSort pa, void (* process)(void *p));

#endif
#ifndef _QUEUE_PUB_H_
#define _QUEUE_PUB_H_

#define SUCCESS 0
#define FAIL 1

typedef struct queue *pQueue, **ppQueue;

int cQueue(ppQueue pf, int size, int sizedata);
int dQueue(ppQueue pf);
int enqueue(pQueue f, void *element);
int unqueue(pQueue f, void *element);
int firstEqual(pQueue f, void *element);
int setcmp(pQueue f, int (* cmp)(void *p1, void *p2));
int cleanQueue(pQueue f);
int sizeQueue(pQueue f);

#endif
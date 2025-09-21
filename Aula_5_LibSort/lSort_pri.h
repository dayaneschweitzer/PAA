#ifndef _SORT_PRI_H_
#define _SORT_PRI_H_

typedef struct node {
    void *data;
    struct node *next;
}

typedef struct lSort {
    Node *head;       
    int size; 
    int data_size;
} lSort;

#endif
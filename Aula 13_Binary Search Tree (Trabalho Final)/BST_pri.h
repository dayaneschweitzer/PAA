/* BST_pri.h */
#ifndef _BST_PRI_H_
#define _BST_PRI_H_

#include "BST_pub.h"

/* Nó da árvore (agora com altura para AVL) */
typedef struct BSTNode {
    void *data;
    struct BSTNode *left;
    struct BSTNode *right;
    int height;          /* necessário para balanceamento AVL */
} BSTNode;

/* Estrutura principal da BST */
struct BST {
    BSTNode *root;
    int sizedata;        /* tamanho dos dados armazenados em cada nó */
};

#endif


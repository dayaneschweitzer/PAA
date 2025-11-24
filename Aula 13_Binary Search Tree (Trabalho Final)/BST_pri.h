/* BST_pri.h */
#ifndef _BST_PRI_H_
#define _BST_PRI_H_

#include "BST_pub.h"

typedef struct BSTNode {
    void *data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

struct BST {
    BSTNode *root;
    int sizedata;
};

#endif


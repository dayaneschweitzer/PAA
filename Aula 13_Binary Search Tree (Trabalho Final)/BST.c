/* BST.c */
#include "BST_pri.h"
#include <stdlib.h>
#include <string.h>

static BSTNode *createNode(pBST tree, void *data) {
    if (!tree || !data) return NULL;

    BSTNode *node = (BSTNode *) malloc(sizeof(BSTNode));
    if (!node) return NULL;

    node->data = malloc(tree->sizedata);
    if (!node->data) {
        free(node);
        return NULL;
    }

    memcpy(node->data, data, tree->sizedata);
    node->left = node->right = NULL;
    return node;
}

static void freeSubtree(BSTNode *node) {
    if (!node) return;

    freeSubtree(node->left);
    freeSubtree(node->right);

    free(node->data);
    free(node);
}

static BSTNode *findMin(BSTNode *node) {
    if (!node) return NULL;
    while (node->left) {
        node = node->left;
    }
    return node;
}

static BSTNode *insertNode(pBST tree, BSTNode *node,
                           void *data,
                           int (*cmp)(void *, void *),
                           int *pResult) {
    if (!cmp || !pResult) return node;

    if (!node) {
        BSTNode *newNode = createNode(tree, data);
        if (!newNode) {
            *pResult = FAIL;
            return NULL;
        }
        *pResult = SUCCESS;
        return newNode;
    }

    int c = cmp(data, node->data);

    if (c == 0) {
        /* não insere duplicado */
        *pResult = FAIL;
    } else if (c < 0) {
        node->left = insertNode(tree, node->left, data, cmp, pResult);
    } else { /* c > 0 */
        node->right = insertNode(tree, node->right, data, cmp, pResult);
    }

    return node;
}

static BSTNode *removeNode(pBST tree, BSTNode *node,
                           void *item,
                           int (*cmp)(void *, void *),
                           int *pResult) {
    if (!cmp || !pResult) return node;

    if (!node) {
        *pResult = FAIL;  /* não achou */
        return NULL;
    }

    int c = cmp(item, node->data);

    if (c < 0) {
        node->left = removeNode(tree, node->left, item, cmp, pResult);
    } else if (c > 0) {
        node->right = removeNode(tree, node->right, item, cmp, pResult);
    } else {

        *pResult = SUCCESS;

        if (!node->left && !node->right) {
            free(node->data);
            free(node);
            return NULL;
        }
        else if (!node->left) {
            BSTNode *temp = node->right;
            free(node->data);
            free(node);
            return temp;
        }
        else if (!node->right) {
            BSTNode *temp = node->left;
            free(node->data);
            free(node);
            return temp;
        }
        else {
            BSTNode *minRight = findMin(node->right);
            /* copia os dados do sucessor para este nó */
            memcpy(node->data, minRight->data, tree->sizedata);
            /* remove o sucessor na subárvore direita */
            node->right = removeNode(tree, node->right, node->data, cmp, pResult);
        }
    }
    return node;
}

static BSTNode *findNode(BSTNode *node, void *item,
                         int (*cmp)(void *, void *)) {
    if (!node || !cmp) return NULL;

    int c = cmp(item, node->data);

    if (c == 0) return node;
    else if (c < 0) return findNode(node->left, item, cmp);
    else return findNode(node->right, item, cmp);
}

static void inorder(BSTNode *node, void (*process)(void *)) {
    if (!node || !process) return;
    inorder(node->left, process);
    process(node->data);
    inorder(node->right, process);
}

static void preorder(BSTNode *node, void (*process)(void *)) {
    if (!node || !process) return;
    process(node->data);
    preorder(node->left, process);
    preorder(node->right, process);
}

static void postorder(BSTNode *node, void (*process)(void *)) {
    if (!node || !process) return;
    postorder(node->left, process);
    postorder(node->right, process);
    process(node->data);
}

int cBST(ppBST pp, int sizedata) {
    if (!pp || sizedata <= 0) return FAIL;

    pBST tree = (pBST) malloc(sizeof(*tree));
    if (!tree) return FAIL;

    tree->root = NULL;
    tree->sizedata = sizedata;

    *pp = tree;
    return SUCCESS;
}

int dBST(ppBST pp) {
    if (!pp || !*pp) return FAIL;

    pBST tree = *pp;
    freeSubtree(tree->root);
    tree->root = NULL;

    free(tree);
    *pp = NULL;

    return SUCCESS;
}

int cleanBST(pBST p) {
    if (!p) return FAIL;

    freeSubtree(p->root);
    p->root = NULL;

    return SUCCESS;
}

int iBST(pBST p, void *newdata, int (*cmp)(void *, void *)) {
    if (!p || !newdata || !cmp) return FAIL;

    int result = FAIL;
    p->root = insertNode(p, p->root, newdata, cmp, &result);
    return result;
}

int rBST(pBST p, void *item, int (*cmp)(void *, void *)) {
    if (!p || !item || !cmp) return FAIL;

    int result = FAIL;
    p->root = removeNode(p, p->root, item, cmp, &result);
    return result;
}

int sBST(pBST p, void *item, int (*cmp)(void *, void *)) {
    if (!p || !item || !cmp) return FAIL;

    BSTNode *node = findNode(p->root, item, cmp);
    if (node) return SUCCESS;
    return FAIL;
}

int emptyBST(pBST p) {
    if (!p || p->root == NULL)
        return SUCCESS;  /* árvore vazia */
    return FAIL;         /* árvore não vazia */
}

int orderPath(pBST pa, void (*process)(void *p)) {
    if (!pa || !process) return FAIL;
    inorder(pa->root, process);
    return SUCCESS;
}

int preorderPath(pBST pa, void (*process)(void *p)) {
    if (!pa || !process) return FAIL;
    preorder(pa->root, process);
    return SUCCESS;
}

int postorderPath(pBST pa, void (*process)(void *p)) {
    if (!pa || !process) return FAIL;
    postorder(pa->root, process);
    return SUCCESS;
}

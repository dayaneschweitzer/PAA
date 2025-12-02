/* BST.c */
#include "BST_pri.h"
#include <stdlib.h>
#include <string.h>

/* ========== Funções auxiliares gerais (AVL) ========== */

static int heightNode(BSTNode *n) {
    return n ? n->height : 0;
}

static int maxInt(int a, int b) {
    return (a > b) ? a : b;
}

static int getBalance(BSTNode *n) {
    if (!n) return 0;
    return heightNode(n->left) - heightNode(n->right);
}

/* Rotação simples à direita */
static BSTNode *rightRotate(BSTNode *y) {
    BSTNode *x = y->left;
    BSTNode *T2 = x->right;

    /* Rotação */
    x->right = y;
    y->left = T2;

    /* Atualiza alturas */
    y->height = 1 + maxInt(heightNode(y->left), heightNode(y->right));
    x->height = 1 + maxInt(heightNode(x->left), heightNode(x->right));

    /* Novo root da subárvore */
    return x;
}

/* Rotação simples à esquerda */
static BSTNode *leftRotate(BSTNode *x) {
    BSTNode *y = x->right;
    BSTNode *T2 = y->left;

    /* Rotação */
    y->left = x;
    x->right = T2;

    /* Atualiza alturas */
    x->height = 1 + maxInt(heightNode(x->left), heightNode(x->right));
    y->height = 1 + maxInt(heightNode(y->left), heightNode(y->right));

    /* Novo root da subárvore */
    return y;
}

/* ========== Funções auxiliares de nó ========== */

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
    node->height = 1; /* nó novo sempre começa com altura 1 */

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

/* ========== Inserção AVL ========== */

static BSTNode *insertNode(pBST tree, BSTNode *node,
                           void *data,
                           int (*cmp)(void *, void *),
                           int *pResult) {
    if (!cmp || !pResult) return node;

    /* Inserção BST padrão */
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
        return node;
    } else if (c < 0) {
        node->left = insertNode(tree, node->left, data, cmp, pResult);
    } else { /* c > 0 */
        node->right = insertNode(tree, node->right, data, cmp, pResult);
    }

    /* Atualiza altura deste nó */
    node->height = 1 + maxInt(heightNode(node->left), heightNode(node->right));

    /* Verifica fator de balanceamento */
    int balance = getBalance(node);

    /* Casos AVL */

    /* Caso LL (esquerda-esquerda) */
    if (balance > 1 && cmp(data, node->left->data) < 0) {
        return rightRotate(node);
    }

    /* Caso RR (direita-direita) */
    if (balance < -1 && cmp(data, node->right->data) > 0) {
        return leftRotate(node);
    }

    /* Caso LR (esquerda-direita) */
    if (balance > 1 && cmp(data, node->left->data) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    /* Caso RL (direita-esquerda) */
    if (balance < -1 && cmp(data, node->right->data) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* Nó já balanceado */
    return node;
}

/* ========== Remoção AVL ========== */

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
        /* Encontrou o nó a remover */
        *pResult = SUCCESS;

        /* Caso 1: nó folha */
        if (!node->left && !node->right) {
            free(node->data);
            free(node);
            return NULL;
        }
        /* Caso 2: só filho direito */
        else if (!node->left) {
            BSTNode *temp = node->right;
            free(node->data);
            free(node);
            return temp;
        }
        /* Caso 3: só filho esquerdo */
        else if (!node->right) {
            BSTNode *temp = node->left;
            free(node->data);
            free(node);
            return temp;
        }
        /* Caso 4: dois filhos */
        else {
            BSTNode *minRight = findMin(node->right);
            /* copia os dados do sucessor in-order para este nó */
            memcpy(node->data, minRight->data, tree->sizedata);
            /* remove o sucessor na subárvore direita */
            node->right = removeNode(tree, node->right, node->data, cmp, pResult);
        }
    }

    /* Se a árvore ficou vazia nesse ramo */
    if (!node) return NULL;

    /* Atualiza altura */
    node->height = 1 + maxInt(heightNode(node->left), heightNode(node->right));

    /* Verifica balanceamento */
    int balance = getBalance(node);

    /* Caso LL */
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }

    /* Caso LR */
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    /* Caso RR */
    if (balance < -1 && getBalance(node->right) <= 0) {
        return leftRotate(node);
    }

    /* Caso RL */
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

/* ========== Busca e percursos ========== */

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

/* ========== Interface pública (BST_pub.h) ========== */

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

/* SUCCESS se a árvore estiver vazia, FAIL se não estiver */
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


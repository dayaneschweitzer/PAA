/* main.c */
/* Arquivo EXEMPLO DE Aplicacao */
/* MODIFIQUEM-o, CORRIJAM-o!  (já corrigido abaixo) */

#include "main.h"

/* Função de comparação para inteiros */
int comparaDados(void *p1, void *p2) {
    int a = *(int *)p1;
    int b = *(int *)p2;

    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

/* Função de processamento usada no percurso (imprime o inteiro) */
void imprimeDado(void *p) {
    int v = *(int *)p;
    printf(" %d", v);
}

int main(int argc, char *argv[]) {

    pBST arvore = NULL;
    int novo;

    /* cria BST para armazenar inteiros */
    if (cBST(&arvore, sizeof(int)) != SUCCESS) {
        fprintf(stderr, "Erro ao criar BST\n");
        return 1;
    }

    /* leitura dos valores da entrada padrão (stdin) */
    while (1) {
        if (fscanf(stdin, "%d", &novo) != 1) {
            /* Fim da leitura */
            break;
        }

        printf("{%d}", novo);

        if (iBST(arvore, &novo, comparaDados) == SUCCESS) {
            printf("(%d)", novo);
        } else {
            printf("Erro na insercao");
        }
    }

    printf("\nPercurso em-ordem (orderPath):");
    orderPath(arvore, imprimeDado);
    printf("\n");

    /* libera memória da árvore */
    dBST(&arvore);

    return 0;
}

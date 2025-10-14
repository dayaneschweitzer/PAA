/* Arquivo EXEMPLO DE APLICACAO */
// MODIFIQUEM-no, CORRIJAM-no!
#include "main.h"

int main(void) {
    pDDLL lista = NULL;
    int *arg = NULL;
    int rlines = 0;

    /* lê a quantidade de elementos */
    if (fscanf(stdin, "%d", &rlines) != 1 || rlines <= 0) {
        fprintf(stderr, "FAIL: entrada invalida para quantidade.\n");
        return 1;
    }

    /* aloca buffer para os inteiros de entrada */
    arg = (int*) malloc(sizeof(int) * (size_t)rlines);
    if (!arg) {
        fprintf(stderr, "FAIL: falta de memoria.\n");
        return 1;
    }

    /* cria a lista de ints */
    if (cDDLL(&lista, sizeof(int)) != SUCCESS) {
        fprintf(stderr, "FAIL: erro ao criar a lista.\n");
        free(arg);
        return 1;
    } else {
        printf("OK  : Lista criada com SUCESSO.\n");
    }

    /* le e insere cada elemento no fim */
    for (int i = 0; i < rlines; i++) {
        if (fscanf(stdin, "%d", &arg[i]) != 1) {
            fprintf(stderr, "FAIL: erro lendo elemento %d.\n", i + 1);
            dDDLL(&lista);
            free(arg);
            return 1;
        }
        if (iEnd(lista, &arg[i]) == SUCCESS) {
            printf("OK  : inserido com SUCESSO (%d).\n", arg[i]);
        } else {
            printf("FAIL: falha na insercao (%d).\n", arg[i]);
        }
    }

    /* opcional: mostra contagem */
    printf("INFO: total de elementos = %d\n", countElements(lista));

    /* destroi lista e libera vetor */
    if (dDDLL(&lista) == SUCCESS) {
        printf("OK  : Lista destruida com SUCESSO.\n");
    } else {
        printf("FAIL: Falha na destruicao da lista.\n");
    }

    free(arg);
    return 0;
}

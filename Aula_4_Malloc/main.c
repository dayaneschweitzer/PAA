#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "invert_array.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <tamanho_vetor>\n", argv[0]);
        return 1;
    }

    int tamanho = atoi(argv[1]);

    // Aloca o vetor dinamicamente
    int *vetor = alocarVetor(tamanho);

    if (vetor == NULL) {
        printf("Erro: Não foi possível alocar memória para o vetor.\n");
        return 1;
    }

    // Preenche o vetor com valores aleatórios
    preencherVetor(vetor, tamanho);

    // Imprime o vetor original
    imprimirVetor(vetor, tamanho);

    // Inverte os elementos do vetor
    inverterVetor(vetor, tamanho);

    // Imprime o vetor invertido
    imprimirVetor(vetor, tamanho);

    // Libera a memória alocada para o vetor
    free(vetor);

    return 0;
}

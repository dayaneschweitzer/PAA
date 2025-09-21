#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "invert_array.h"

// Função para alocar dinamicamente um vetor de inteiros
int *alocarVetor(int tamanho) {
    return (int *) malloc(tamanho * sizeof(int));
}

// Função para preencher o vetor com valores aleatórios
void preencherVetor(int *vetor, int tamanho) {
    srand(time(NULL)); // inicializa a semente
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = rand() % 100; // números entre 0 e 99
    }
}

// Função para imprimir o vetor
void imprimirVetor(int *vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

// Função para inverter os elementos do vetor
void inverterVetor(int *vetor, int tamanho) {
    int i = 0, j = tamanho - 1;
    while (i < j) {
        int temp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = temp;
        i++;
        j--;
    }
}
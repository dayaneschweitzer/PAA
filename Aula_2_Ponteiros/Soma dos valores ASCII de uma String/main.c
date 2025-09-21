#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sum_ascii.h"

int main() {
    char *str = NULL; // Inicializa o ponteiro para a string como NULL
    char buffer[100]; // Buffer temporário para leitura da entrada
    size_t size = 0;  // Tamanho atual da string
    size_t capacity = 0; // Capacidade atual do buffer

    printf("Digite uma string (digite '.' para finalizar):\n");

    // Loop para ler a entrada do usuário até que ele digite '.'
    while (1) {
        // Lê uma linha de entrada
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Erro ao ler a entrada.\n");
            free(str); // Libera a memória alocada para a string
            return 1;
        }

        // Verifica se a entrada é '.'
        if (strcmp(buffer, ".\n") == 0) {
            break;
        }

        // Verifica se a capacidade atual é suficiente para armazenar a entrada
        size_t input_length = strlen(buffer);
        if (size + input_length > capacity) {
            // Se não houver espaço suficiente, realoca memória
            capacity = size + input_length;
            char *temp = realloc(str, capacity);
            if (!temp) {
                printf("Erro ao alocar memória.\n");
                free(str); // Libera a memória alocada para a string
                return 1;
            }
            str = temp;
        }

        // Copia a entrada para o final da string
        strcpy(str + size, buffer);
        size += input_length;
    }

    // Remove o último caractere de nova linha, se houver
    if (size > 0 && str[size - 1] == '\n') {
        str[size - 1] = '\0';
        size--;
    }

    // Calcula a soma dos valores ASCII da string
    int sum = sum_ascii(str);

    // Imprime o resultado
    printf("Soma dos valores ASCII da string digitada: %d\n", sum);

    // Libera a memória alocada para a string
    free(str);

    return 0;
}

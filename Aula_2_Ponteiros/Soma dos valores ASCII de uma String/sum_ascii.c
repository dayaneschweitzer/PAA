#include "sum_ascii.h"

int sum_ascii(const char *str) {
    int sum = 0; // inicializa a soma

    // percorre cada caractere da string at� o terminador '\0'
    for (int i = 0; str[i] != '\0'; i++) {
        sum += (unsigned char) str[i];
    }

    return sum; // retorna a soma calculada
}

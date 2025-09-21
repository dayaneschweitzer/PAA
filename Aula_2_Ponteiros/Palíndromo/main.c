#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "palindromo.h"

int main(int argc, char **argv) {
    char palavra[100];
    strcpy(palavra, argv[1]);
    if (verificarPalindromo(palavra)) {
        printf("Palindromo!\n");
    } else {
        printf("Não é um palíndromo.\n");
    }
    return 0;
}
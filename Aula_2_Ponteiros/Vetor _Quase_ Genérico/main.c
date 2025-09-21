#include <stdio.h>
#include <stdlib.h>
#include "generic_functions.h"
#define MAX_SIZE 50

int main() {
    struct GenericData genericArray[MAX_SIZE];
    int dataSize = 0;

    printf("Digite até 5 dados genéricos (inteiros, float ou string), um por linha:\n");
    while (dataSize < MAX_SIZE) {
        if (readGenericData(genericArray, &dataSize) != 0)
            break;
    }

    printf("\nDados inseridos:\n");
    printGenericData(genericArray, dataSize);

    // Liberar memória alocada para strings
    for (int i = 0; i < dataSize; i++) {
        if (genericArray[i].type == 2)
            free(genericArray[i].data.stringValue);
    }

    return 0;
}
#include <stdio.h>
#include "libvet.h"

int main() {
    DynamicIntArray vec;
    size_t initial_capacity = 10;

    initDynamicIntArray(&vec, initial_capacity);

    int value;
    printf("Digite os elementos do vetor (digite -1 para finalizar):\n");

    while (1) {
        printf("Elemento: ");
        scanf("%d", &value);
        if (value == -1) {
            break;
        }
        pushBack(&vec, value);
    }

    printf("Elementos do vetor: ");
    for (size_t i = 0; i < vec.size; i++) {
        printf("%d ", vec.array[i]);
    }
    printf("\n");

    freeDynamicIntArray(&vec);

    return 0;
}

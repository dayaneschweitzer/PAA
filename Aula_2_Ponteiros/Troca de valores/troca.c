#include "troca.h"

void trocar(int *a, int *b) {
    int temp = *a;  // guarda o valor de *a
    *a = *b;        // coloca em *a o valor de *b
    *b = temp;      // coloca em *b o valor salvo
}

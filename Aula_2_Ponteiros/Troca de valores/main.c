#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "troca.h"

int main(int argc, char **argv) {
    int x = 0, y = 0;
    x = atoi(argv[1]);
    y = atoi(argv[2]);
    printf("Antes da troca: x = %d, y = %d\n", x, y);
    trocar(&x, &y);
    printf("Depois da troca: x = %d, y = %d\n", x, y);
    return 0;
}
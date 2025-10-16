#include "main.h"

int main(int argc, char *argv[]) {
    int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
    long long int product = INT_MIN;
    int sum = INT_MIN;
    ppsMax ps = NULL;
    // Variável para armazenar o tempo inicial e final
    clock_t inicio, fim;
    double tempo_gasto;


    if (argc < 2) {
        printf("Uso: %s <arquivo>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    int *arr = NULL;
    int size = 0, capacity = 0;

    // Leitura dinâmica do arquivo
    int num;
    while (fscanf(file, "%d", &num) == 1) {
        if (size >= capacity) {
            capacity = capacity ? capacity * 2 : 1;
            arr = realloc(arr, capacity * sizeof(int));
        }
        arr[size++] = num;
    }
    fclose(file);

    // Marca o tempo inicial
    inicio = clock();
    if (cpsMax(&ps)) {
        return FAIL;
    }

    if ((getmax1(ps, arr, size, &max1)) || 
         (getmax2(ps, arr, size, &max2)) || 
         (getmax3(ps, arr, size, &max3))) {
        return FAIL;
    } 
    printf("Os números são: %d, %d, %d\n", max1, max2, max3);

    if (max_product(ps, arr, size, &product)){
        return FAIL;
    }    
    printf("O produto máximo de três maiores números é: %lld\n", product);

    if (max_sum(ps, arr, size, &sum)) {
        return FAIL;
    }
    printf("A soma é: %d\n", sum);

    if (dpsMax(&ps)) {
        return FAIL;
    }
    free(arr);

    // Marca o tempo final
    fim = clock();
    // Calcula o tempo gasto em segundos
    tempo_gasto = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    // Imprime o tempo gasto
    printf("Tempo de execução: %f segundos\n", tempo_gasto);
    return 0;
}
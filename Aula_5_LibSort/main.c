#include "main.h"

#define SUCCESS 0
#define FAIL 1


void myprint(void *p) {
    printf("%lf ", *((double *)p));
}

int comparaDados(void *dado1, void *dado2) {
    double n1 = *((double *)dado1);
    double n2 = *((double *)dado2);
    return n1 - n2;
}


int main(int argc, char*argv[]){
    pSort ptr=NULL;
    double novo=9;
    double i=0;
    char fim[100] = "FIM";

    if((cSort(&ptr, sizeof(int)))==FAIL) {
        printf("Erro na criacao da arvore\n");
        exit(1);
    }

    while (1) {
        if (!fscanf(stdin, "%d", &novo)) {
            break;
        }
        if((iSort(ptr, &novo, comparaDados)) == SUCCESS){
            printf ("(%lf)", novo);
        }
        else {
            printf("(Erro:%lf)", novo);
        }
    }

    printf("\nImpressao dos elementos em ordem: ");
    printSort(ptr, myprint);

    dSort(&ptr);
    return 0;
}
	
    return 0;
}

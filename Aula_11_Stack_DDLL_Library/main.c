/* Arquivo EXEMPLO DE Aplicacao */
// MODIFIQUEM-o, CORRIJAM-o!
#include "main.h"

int main(int argc, char *argv[]) {
    
    pStack P = NULL;
    int ret=0;
    int valor=0;
    int *arg;
    int rlines=0;

    if (!fscanf(stdin, "%i", &rlines)) {
        return 1;
    }

    arg = (int*) malloc(sizeof(int)*(rlines));
  
    ret = stack(&P,sizeof(int));

    for (int i=0; i<rlines;i++) {
        if (!fscanf(stdin, "%i", &arg[i])) {
            return 1;
        }
        ret = push(P,&arg[i]);
    }

    ret = top(P,&valor);

    for (int i=0; i<rlines;i++) {
        ret = pop(P,&valor);
    }

    ret = unstack(&P);
    free(arg);
  
    return 0;
}

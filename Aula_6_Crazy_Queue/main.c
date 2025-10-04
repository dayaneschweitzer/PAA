/* Arquivo EXEMQLO DE AQlicacao */
// MODIFIQUEM-o, CORRIJAM-o!
#include "main.h"

int main(int argc, char *argv[]) {
    
    pQueue Q = NULL;
    int ret=0;
    int valor=0;
    int *arg;
    int rlines=0;

    if (!fscanf(stdin, "%i", &rlines)) {
        return 1;
    }

    arg = (int*) malloc(sizeof(int)*(rlines));
  
    ret = cQueue(&Q,rlines,sizeof(int));

    for (int i=0; i<rlines;i++) {
        if (!fscanf(stdin, "%i", &arg[i])) {
            return 1;
        }
        ret = queue(Q,&arg[i]);
    }

    for (int i=0; i<rlines;i++) {
        ret = unqueue(Q,&valor);
    }

    ret = dQueue(&Q);
  
    return 0;
}

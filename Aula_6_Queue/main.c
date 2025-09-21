#include "main.h"
#include "queue_pub.h"

int comparaInt(void *dado1, void *dado2) {
    int n1 = *((int *)dado1);
    int n2 = *((int *)dado2);
    if (n1 < n2) return -1;
    if (n1 > n2) return 1;
    return 0;
}


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
    if (setcmp(Q, comparaInt) == FAIL) {
        printf ("ERRO no setcmp!");
    }
    
    for (int i=0; i<rlines;i++) {
        if (!fscanf(stdin, "%i", &arg[i])) {
            return 1;
        }
        ret = enqueue(Q,&arg[i]);
    }

    if (firstEqual(Q, &valor) == SUCCESS) {
        printf ("Primeiro Elemento é igual a %i.", valor);
    }

    for (int i=0; i<rlines;i++) {
        ret = unqueue(Q,&valor);
    }

    ret = dQueue(&Q);
  
    return 0;
}
#include <stdio.h>

int main(void) {
    float valor;        // 1) variável que guarda o número digitado
    float *p = NULL;    // 2) ponteiro para float (ainda não aponta para nada útil)

    printf("Digite um valor float: ");
    if (scanf("%f", &valor) != 1) {     // lê usando o endereço de 'valor'
        printf("Entrada invalida.\n");
        return 1;
    }

    p = &valor;         // 3) 'p' recebe o ENDEREÇO de 'valor'

    *p = *p + 10.0f;    // 4) altera o CONTEUDO apontado por 'p' (equivale a 'valor += 10')

    printf("Novo valor: %.2f\n", valor); // 5) imprime com 2 casas decimais
    return 0;
}
//Variável valor: ocupa alguns bytes na memória (stack) e tem um endereço (ex.: 0x61ff08).

//Operador & (address of): obtém esse endereço.
//&valor → “onde valor está guardado”.

//Ponteiro p: é uma variável cujo conteúdo é um endereço.
//Quando fazemos p = &valor;, dizemos “p aponta para valor”.

//Operador * (dereference): acessa o conteúdo do endereço guardado no ponteiro.
//*p é “o mesmo dado que está em valor”.

//Assim, *p = *p + 10.0f; modifica a própria variável valor por meio do ponteiro.
//Por isso, ao imprimir valor, o número já está 10 unidades maior.

//Em termos de memória:
//p → (contém) endereço de valor → (contém) número lido.
//*p segue a seta e altera o número guardado lá.

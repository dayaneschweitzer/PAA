#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de dados
typedef struct {
    int id;
    float valor;
} Dados;

/*
 * operacaoEstrutura
 * Recebe um ponteiro genérico (void *) que deve apontar para um objeto do tipo Dados.
 * A função converte (cast) para Dados* e multiplica o campo 'valor' por 2,
 * alterando diretamente a estrutura original (passagem por referência).
 */
void operacaoEstrutura(void *estrutura) {
    if (estrutura == NULL) return;
    Dados *ptr = (Dados *)estrutura;  // cast do ponteiro genérico
    ptr->valor *= 2.0f;               // atualiza o campo 'valor' na própria estrutura
}

int main(void) {
    // Alocação dinâmica da estrutura
    Dados *ptr_dados = (Dados *)malloc(sizeof(Dados));
    if (!ptr_dados) {
        fprintf(stderr, "Erro: falha ao alocar memoria para Dados.\n");
        return 1;
    }

    // Preenchendo a estrutura com dados
    ptr_dados->id = 1;
    ptr_dados->valor = 10.5f;

    // Chamando a função para operar na estrutura (passando como void *)
    operacaoEstrutura((void *)ptr_dados);

    // Exibindo os dados modificados da estrutura
    printf("ID: %d, Valor: %.2f\n", ptr_dados->id, ptr_dados->valor);

    // Liberando a memória alocada
    free(ptr_dados);
    return 0;
}

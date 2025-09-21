#include "primes.h"
#include <math.h>

// Verifica se um número é primo
int is_prime(int num) { //Declara a função is_prime que recebe um número inteiro e devolve 1 (verdadeiro) se for primo ou 0 (falso) se não for.
    if (num <= 1) return 0;      // números <= 1 não são primos
    if (num == 2) return 1;      // 2 é primo
    if (num % 2 == 0) return 0;  // Se o número é par (num % 2 == 0) e maior que 2, não pode ser primo.

    // Testa divisores ímpares até a raiz quadrada
    for (int i = 3; i * i <= num; i += 2) { //Começamos com i = 3 e vamos aumentando de 2 em 2 (testando só os ímpares).
        if (num % i == 0) { //se num for divisível por i, então encontramos um divisor > não é primo.
            return 0; // achou um divisor > não é primo
        }
    }
    return 1; // nenhum divisor encontrado > é primo
}

// Retorna o próximo primo após 'current'
int next_prime(int current) { //Declara a função next_prime que vai encontrar o próximo primo após current.
    int next = current + 1; //A variável next começa com o valor imediatamente maior que current.
    while (!is_prime(next)) { //Enquanto next não for primo (!is_prime(next)), aumenta next.
        next++; //Faz o programa avançar pelos próximos números até encontrar o primeiro primo.
    }
    return next; //Quando o laço parar, significa que next é primo.
}

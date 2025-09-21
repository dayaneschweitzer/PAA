#include "primes.h"
#include <math.h>

// Verifica se um n�mero � primo
int is_prime(int num) { //Declara a fun��o is_prime que recebe um n�mero inteiro e devolve 1 (verdadeiro) se for primo ou 0 (falso) se n�o for.
    if (num <= 1) return 0;      // n�meros <= 1 n�o s�o primos
    if (num == 2) return 1;      // 2 � primo
    if (num % 2 == 0) return 0;  // Se o n�mero � par (num % 2 == 0) e maior que 2, n�o pode ser primo.

    // Testa divisores �mpares at� a raiz quadrada
    for (int i = 3; i * i <= num; i += 2) { //Come�amos com i = 3 e vamos aumentando de 2 em 2 (testando s� os �mpares).
        if (num % i == 0) { //se num for divis�vel por i, ent�o encontramos um divisor > n�o � primo.
            return 0; // achou um divisor > n�o � primo
        }
    }
    return 1; // nenhum divisor encontrado > � primo
}

// Retorna o pr�ximo primo ap�s 'current'
int next_prime(int current) { //Declara a fun��o next_prime que vai encontrar o pr�ximo primo ap�s current.
    int next = current + 1; //A vari�vel next come�a com o valor imediatamente maior que current.
    while (!is_prime(next)) { //Enquanto next n�o for primo (!is_prime(next)), aumenta next.
        next++; //Faz o programa avan�ar pelos pr�ximos n�meros at� encontrar o primeiro primo.
    }
    return next; //Quando o la�o parar, significa que next � primo.
}

#include <ctype.h>
#include <string.h>
#include "palindromo.h"

bool verificarPalindromo(const char *str) {
    if (!str) return false;

    size_t i = 0, j = strlen(str);
    if (j == 0) return true;
    j--;

    while (i < j) {
        while (i < j && !isalnum((unsigned char)str[i])) i++;
        while (i < j && !isalnum((unsigned char)str[j])) j--;

        if (tolower((unsigned char)str[i]) != tolower((unsigned char)str[j]))
            return false;

        i++;
        j--;
    }
    return true;
}

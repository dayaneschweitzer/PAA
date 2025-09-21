#include "generic_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 5  // limite do enunciado

// trim simples: remove \n final e espaços nas pontas
static void trim(char *s) {
    size_t n = strlen(s);
    while (n && (s[n-1] == '\n' || s[n-1] == '\r' || isspace((unsigned char)s[n-1]))) { s[--n] = '\0'; }
    size_t i = 0;
    while (s[i] && isspace((unsigned char)s[i])) i++;
    if (i) memmove(s, s + i, strlen(s + i) + 1);
}

static int is_int_literal(const char *s) {
    // aceita sinais +/-, dígitos; rejeita se tiver '.', 'e', 'E'
    if (*s == '+' || *s == '-') s++;
    if (!*s) return 0;
    for (const char *p = s; *p; p++) {
        if (*p == '.' || *p == 'e' || *p == 'E') return 0;
        if (!isdigit((unsigned char)*p)) return 0;
    }
    return 1;
}

static int has_float_markers(const char *s) {
    // considera float se houver '.' ou expoente (e/E)
    for (const char *p = s; *p; p++) {
        if (*p == '.' || *p == 'e' || *p == 'E') return 1;
    }
    return 0;
}

int readGenericData(struct GenericData *data, int *dataSize) {
    if (*dataSize >= MAX_SIZE) {
        printf("Chegou ao tamanho máximo do vetor.\n");
        return 3; // acima do limite
    }

    char buf[256];
    if (!fgets(buf, sizeof(buf), stdin)) {
        return 1; // erro genérico de leitura
    }

    trim(buf);
    if (buf[0] == '.' && buf[1] == '\0') {
        return 2; // interrupção
    }
    if (buf[0] == '\0') {
        // linha vazia trate como erro genérico
        return 1;
    }

    // Detecta tipo e armazena
    struct GenericData *slot = &data[*dataSize];

    if (is_int_literal(buf)) {
        long v = strtol(buf, NULL, 10);
        slot->type = 0;
        slot->data.intValue = (int)v;
    } else if (has_float_markers(buf)) {
        // tenta converter para float (double e depois cast)
        char *end = NULL;
        double dv = strtod(buf, &end);
        // se conversão falhar, trata como string
        if (end && *end == '\0') {
            slot->type = 1;
            slot->data.floatValue = (float)dv;
        } else {
            slot->type = 2;
            size_t len = strlen(buf) + 1;
            slot->data.stringValue = (char*)malloc(len);
            if (!slot->data.stringValue) return 1;
            memcpy(slot->data.stringValue, buf, len);
        }
    } else {
        // string
        slot->type = 2;
        size_t len = strlen(buf) + 1;
        slot->data.stringValue = (char*)malloc(len);
        if (!slot->data.stringValue) return 1;
        memcpy(slot->data.stringValue, buf, len);
    }

    (*dataSize)++;
    // se, após inserir, atingiu o limite, da próxima vez readGenericData imprimirá a msg
    return 0; // sucesso
}

int printGenericData(struct GenericData *data, int dataSize) {
    if (!data || dataSize < 0) return 1;

    for (int i = 0; i < dataSize; i++) {
        switch (data[i].type) {
            case 0: // int
                printf("int %d", data[i].data.intValue);
                break;
            case 1: // float
                // %g imprime de forma compacta (ex.: 1.4)
                printf("float %g", data[i].data.floatValue);
                break;
            case 2: // string
                printf("string %s", data[i].data.stringValue);
                break;
            default:
                return 1;
        }
        if (i + 1 < dataSize) putchar(' ');
    }
    putchar('\n');
    return 0;
}

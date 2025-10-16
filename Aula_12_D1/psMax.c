#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "psMax_pub.h"
#include "psMax_pri.h"

/* ----------------- Helpers internos ----------------- */

/* 
  Percorre o vetor uma única vez para:
   - encontrar os 3 maiores valores: max1 >= max2 >= max3
   - encontrar os 2 menores valores: min1 <= min2
  Retorna SUCCESS/FAIL.
*/
static int scan_top3_bottom2(const int *arr, int size,
                             int *max1, int *max2, int *max3,
                             int *min1, int *min2) {
    if (!arr || size < 3 || !max1 || !max2 || !max3 || !min1 || !min2)
        return FAIL;

    int m1 = INT_MIN, m2 = INT_MIN, m3 = INT_MIN;
    int n1 = INT_MAX, n2 = INT_MAX;

    for (int i = 0; i < size; i++) {
        int x = arr[i];

        /* Atualiza 3 maiores */
        if (x > m1) {           // x novo maior: empurra m1->m2, m2->m3
            m3 = m2;
            m2 = m1;
            m1 = x;
        } else if (x > m2) {    // x fica como segundo maior
            m3 = m2;
            m2 = x;
        } else if (x > m3) {    // x fica como terceiro maior
            m3 = x;
        }

        /* Atualiza 2 menores */
        if (x < n1) {           // x novo menor: empurra n1->n2
            n2 = n1;
            n1 = x;
        } else if (x < n2) {    // x fica como segundo menor
            n2 = x;
        }
    }

    *max1 = m1; *max2 = m2; *max3 = m3;
    *min1 = n1; *min2 = n2;
    return SUCCESS;
}

/* ----------------- API pública ----------------- */

int cpsMax(pppsMax ps) {
    if (!ps) return FAIL;
    *ps = (ppsMax)malloc(sizeof(**ps));
    if (!*ps) return FAIL;
    (*ps)->_unused = 0;
    return SUCCESS;
}

int dpsMax(pppsMax ps) {
    if (!ps || !*ps) return FAIL;
    free(*ps);
    *ps = NULL;
    return SUCCESS;
}

int getmax1(ppsMax ps, int *arr, int size, int *max1) {
    (void)ps; 
    int m1, m2, m3, n1, n2;
    if (scan_top3_bottom2(arr, size, &m1, &m2, &m3, &n1, &n2) != SUCCESS)
        return FAIL;
    *max1 = m1;
    return SUCCESS;
}

int getmax2(ppsMax ps, int *arr, int size, int *max2) {
    (void)ps;
    int m1, m2, m3, n1, n2;
    if (scan_top3_bottom2(arr, size, &m1, &m2, &m3, &n1, &n2) != SUCCESS)
        return FAIL;
    *max2 = m2;
    return SUCCESS;
}

int getmax3(ppsMax ps, int *arr, int size, int *max3) {
    (void)ps;
    int m1, m2, m3, n1, n2;
    if (scan_top3_bottom2(arr, size, &m1, &m2, &m3, &n1, &n2) != SUCCESS)
        return FAIL;
    *max3 = m3;
    return SUCCESS;
}

int max_product(ppsMax ps, int *arr, int size, long long int *product) {
    (void)ps;
    if (!product) return FAIL;

    int m1, m2, m3, n1, n2;
    if (scan_top3_bottom2(arr, size, &m1, &m2, &m3, &n1, &n2) != SUCCESS)
        return FAIL;

    /* 
      Candidatos ao produto máximo:
        - top3: m1*m2*m3
        - dois menores (negativos grandes) * maior: m1*n1*n2
    */
    long long p1 = (long long)m1 * (long long)m2 * (long long)m3;
    long long p2 = (long long)m1 * (long long)n1 * (long long)n2;

    *product = (p1 > p2) ? p1 : p2;
    return SUCCESS;
}

int max_sum(ppsMax ps, int *arr, int size, int *sum) {
    (void)ps;
    if (!sum) return FAIL;

    int m1, m2, m3, n1, n2;
    if (scan_top3_bottom2(arr, size, &m1, &m2, &m3, &n1, &n2) != SUCCESS)
        return FAIL;

    /* Soma máxima é a soma dos 3 maiores */
    *sum = m1 + m2 + m3;
    return SUCCESS;
}

#include "pandigital_multiples.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_char (const void *a, const void *b) {
   return ( *(char *)a - *(char *)b );
}

char *pandigital_multiple(int n)
{
    char *products = calloc(BUFFSIZE, sizeof(char));
    for(int i = 1;; i++) {
        char temp[BUFFSIZE] = { 0 };
        sprintf(temp, "%d", n * i);
        strcat(products, temp);
        if (strlen(products) >= 9) break;
    }
    if (strlen(products) > 9) {
        free(products);
        return NULL;
    }

    char temp[BUFFSIZE] = { 0 };
    strcpy(temp, products);
    qsort(temp, 9, sizeof(char), compare_char);
    if (strcmp(temp, "123456789")) {
        free(products);
        return NULL;
    }
    return products;
}

int main(void) {
    for (int i = 1; i < 10000; i++) {
        char *pm = pandigital_multiple(i);
        if (pm) {
            printf("%4d is a pandigital multiple:  %s\n", i, pm);
            free(pm);
        }
    }
    return 0;
}
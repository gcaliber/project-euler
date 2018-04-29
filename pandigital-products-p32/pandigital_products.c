#include "pandigital_products.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void find_combinations_recur(const char *str, char *acc, int *entry_count, char **result)
{
    if (!strcmp(str, "")) {
        result[(*entry_count)++] = acc;
        return;
    }
    
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        char *new_acc = calloc(strlen(acc) + 1, sizeof(char));
        strcpy(new_acc, acc);
        strncat(new_acc, &str[i], 1);
        
        char rest[len];
        memset(rest, 0, len);
        strncpy(rest, str, i);
        strncat(rest, &str[i + 1], len - i - 1);
        find_combinations_recur(rest, new_acc, entry_count, result);
    }
}

void find_combinations(const char *str, char **result)
{
    int len = strlen(str);

    int entry_count = 0;
    char acc[len + 1];
    for (int i = 0; i <= len; i++) {
        acc[i] = '\0';
    }
    find_combinations_recur(str, acc, &entry_count, result);

    // for (int i = 0; i < entry_count; i++) {
    //     printf("%s\n", result[i]);
    // }
}

int pandigital_products(const char *digits, product_t **solutions)
{
    int comb_count = 1;
    for (int i = 1; i <= strlen(digits); i++) {
        comb_count *= i;
    }
    char **combinations = malloc(comb_count * sizeof(char *));

    find_combinations(digits, combinations);

    int solution_count = 0;
    *solutions = malloc(MIN_PRODUCTS * sizeof(product_t));
    for (int i = 0; i < comb_count; i++) {
        char multiplicand_str[3];
        strncpy(multiplicand_str, combinations[i], 2);
        char multiplier_str[4];
        strncpy(multiplier_str, &combinations[i][2], 3);
        
        char *ptr;
        product_t p;
        p.multiplicand = strtol(multiplicand_str, &ptr, 10);
        p.multiplier = strtol(multiplier_str, &ptr, 10);
        p.product = strtol(&combinations[i][5], &ptr, 10);
        if (p.multiplicand * p.multiplier == p.product) {
            *solutions[solution_count++] = p;
        }
    }
    return solution_count;
}

int main(int argc, char **argv) {
    product_t *solutions = NULL;
    int solution_count = pandigital_products(argv[1], &solutions);
    return 0;
}
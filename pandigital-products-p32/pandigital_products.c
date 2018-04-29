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
    free(acc);
}

void find_combinations(const char *str, char **result)
{
    int len = strlen(str);

    int entry_count = 0;
    char *acc = calloc(len + 1, sizeof(char));
    for (int i = 0; i <= len; i++) {
        acc[i] = '\0';
    }
    find_combinations_recur(str, acc, &entry_count, result);
}

void pandigital(const char *digits, product_t *solutions, int *solution_count)
{
    for (int i = 1; i <= 2; i++) {
        char multiplicand_str[3] = { 0 };
        char multiplier_str[5] = { 0 };
        strncpy(multiplicand_str, digits, i);
        strncpy(multiplier_str, &digits[i], 5 - i);
        
        char *ptr;
        product_t *p = &solutions[*solution_count];
        p->multiplicand = strtol(multiplicand_str, &ptr, 10);
        p->multiplier = strtol(multiplier_str, &ptr, 10);
        p->product = strtol(&digits[5], &ptr, 10);

        // printf("Checking: %d * %d = %d\n", p->multiplicand, p->multiplier, p->product);
        
        if (p->multiplicand * p->multiplier == p->product) {
            (*solution_count)++;
        }
    }
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
    *solutions = malloc(MAX_PRODUCTS * sizeof(product_t));
    product_t *s = *solutions;
    for (int i = 0; i < comb_count; i++) {
        pandigital(combinations[i], s, &solution_count);
    }
    return solution_count;
}

void add_unique(int product, int* products) {
    static int count = 0;
    for (int i = 0; i < count; i++) {
        if (product == products[i]) return;
    }
    products[count++] = product;
}

int main(void) {
    product_t *solutions = NULL;
    int solution_count = pandigital_products("123456789", &solutions);

    int products[solution_count];
    memset(products, 0, solution_count * sizeof(int));
    for (int i = 0; i < solution_count; i++) {
        printf("%d * %d = %d\n", solutions[i].multiplicand, solutions[i].multiplier, solutions[i].product);
        add_unique(solutions[i].product, products);
    }
    int sum = 0;
    for (int i = 0; i < solution_count; i++) {
        sum += products[i];
    }
    printf("Sum of unique products is %d\n", sum);

    return 0;
}
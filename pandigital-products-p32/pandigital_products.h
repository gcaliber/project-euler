#ifndef PANDIGITAL_PRODUCTS_H
#define PANDIGITAL_PRODUCTS_H

typedef struct node {
    char c[2];
    struct node *children;
    int child_count;
} node_t;

typedef struct {
    int multiplicand;
    int multiplier;
    int product;
} product_t;

int pandigital_products(const char *digits, product_t **solutions);

#endif
#ifndef PANDIGITAL_PRODUCTS_H
#define PANDIGITAL_PRODUCTS_H

#define MAX_PRODUCTS 100

typedef struct {
    int multiplicand;
    int multiplier;
    int product;
} product_t;

int pandigital_products(const char *digits, product_t **solutions);

#endif